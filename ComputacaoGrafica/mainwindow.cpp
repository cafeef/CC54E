#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTimer> // Para as animações

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->TelaDesenho, &TelaDeDesenho::zoomRequisitado, this, &MainWindow::lidarComZoom);

    // --- Etapa 1: Criar a Window como um Objeto ---
    ObjetoVirtual windowObj;
    windowObj.nome = "#WINDOW_CAMERA";
    windowObj.tipo = TipoObjeto::Mesh3D; // É um "objeto"
    // Os vértices e faces ficam vazios, pois ela não será desenhada.
    // O estado inicial é definido pelas suas propriedades de câmera:
    windowObj.camera_centro = Ponto(0, 0, 500); // Posição Z afastada
    windowObj.camera_zoom = 1.0; // Zoom inicial padrão

    displayFile.append(windowObj);
    indiceDaWindow = displayFile.size() - 1; // Guarda o índice

    // --- CARREGAR OS POKÉMONS ---
    // !!! MUDE ESTES CAMINHOS PARA ONDE VOCÊ GUARDOU OS SEUS FICHEIROS .obj !!!
    //QString caminhoPokebola = ":/Pokemons/Pokeball_Obj.obj";
    //QString caminhoPsyduck = ":/Pokemons/psyduck.obj";
    QString caminhoUmbreonLowPoly = ":/Pokemons/UmbreonLowPoly.obj";
    QString caminhoCharizard = ":/Pokemons/charizard.obj";
    QString caminhoPikachu = ":/Pokemons/pikachu.obj";

    //ObjetoVirtual pokebola = carregarObjetoOBJ(caminhoPokebola, "Pokebola", Qt::red);
    ObjetoVirtual umbreonlow = carregarObjetoOBJ(caminhoUmbreonLowPoly, "Umbreon Low", Qt::white);
    ObjetoVirtual pikachu = carregarObjetoOBJ(caminhoPikachu, "Pikachu", Qt::yellow);
    ObjetoVirtual charizard = carregarObjetoOBJ(caminhoCharizard, "Charizard", QColorConstants::Svg::orange);

    // --- Posicionar os Pokémons na cena 3D ---
    // (Ajuste estes valores depois de executar pela primeira vez)
    charizard.escalonarEixo(0.3, 0.3, 0.3);
    charizard.transladar(-5, 0, 0);
    charizard.rotacionarEixoX(90);
    pikachu.escalonarEixo(1.1, 1.1, 1.1);
    pikachu.transladar(5, -1, 0);


    //displayFile.append(pokebola);
    displayFile.append(umbreonlow);
    displayFile.append(charizard);
    displayFile.append(pikachu);
    // ------------------------------------

    // Conecta o display file à tela
    ui->TelaDesenho->setDisplayFile(&displayFile);
    ui->TelaDesenho->setIndiceDaWindow(indiceDaWindow); // Diz à tela onde está a câmera

    ajustarWindowParaCena(); // Ajusta o zoom e centro da câmera

    // Preenche a ComboBox com os nomes dos objetos
    atualizarComboBoxDeObjetos();
}

MainWindow::~MainWindow() {
    delete ui;
}

// --- Esta é a sua nova função de "Enquadrar Cena" ---
void MainWindow::ajustarWindowParaCena() {
    if (indiceDaWindow == -1 || displayFile.size() <= 1) return;

    // --- Etapa 1: Encontrar o Bounding Box 3D de todos os objetos ---
    // (O seu código para isto, que já está no seu ficheiro, está perfeito)
    double minX = std::numeric_limits<double>::max(); double minY = minX; double minZ = minX;
    double maxX = std::numeric_limits<double>::lowest(); double maxY = maxX; double maxZ = maxX;
    bool algumPontoEncontrado = false;

    for (int i = 0; i < displayFile.size(); ++i) {
        if (i == indiceDaWindow) continue; // Pula a câmera
        for (const Ponto &v : displayFile[i].vertices) {
            if (v.x() < minX) minX = v.x();
            if (v.x() > maxX) maxX = v.x();
            if (v.y() < minY) minY = v.y();
            if (v.y() > maxY) maxY = v.y();
            if (v.z() < minZ) minZ = v.z();
            if (v.z() > maxZ) maxZ = v.z();
            algumPontoEncontrado = true;
        }
    }
    if (!algumPontoEncontrado) return;

    // --- Etapa 2: Calcular centro e tamanho da cena ---
    Ponto centroCena((minX + maxX) / 2.0, (minY + maxY) / 2.0, (minZ + maxZ) / 2.0);
    double larguraCena = maxX - minX;
    double alturaCena = maxY - minY;

    // --- Etapa 3: Pegar a área da viewport ---
    double vp_largura = ui->TelaDesenho->width() - 2 * ui->TelaDesenho->MARGEM_VIEWPORT;
    double vp_altura = ui->TelaDesenho->height() - 2 * ui->TelaDesenho->MARGEM_VIEWPORT;
    if (vp_largura < 1 || vp_altura < 1) return;
    double aspect = vp_largura / vp_altura;

    // --- Etapa 4: Calcular o ajuste correto (A LÓGICA NOVA) ---
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    if (ui->radioOrtogonal->isChecked()) {
        // --- AJUSTE ORTOGONAL ---
        // (Calcula o 'camera_zoom' necessário)

        // Descobre o "raio" de visão necessário em X e Y
        double r_necessario_x = larguraCena / 2.0;
        double r_necessario_y = (alturaCena / 2.0) * aspect; // Ajusta pela proporção

        // O raio de visão final é o maior dos dois, com uma margem
        double r_necessario = std::max(r_necessario_x, r_necessario_y) * 1.1;
        if (r_necessario < 1e-6) r_necessario = 1.0;

        double novo_zoom = 1.0 / r_necessario;
        double z_camera = centroCena.z() + std::max(larguraCena, alturaCena) + 100; // Recuado

        windowObj.camera_centro = Ponto(centroCena.x(), centroCena.y(), z_camera);
        windowObj.camera_zoom = novo_zoom;

    } else {
        // --- AJUSTE PERSPECTIVA ---
        // (Calcula a distância Z ('camera_centro.z') necessária)

        double fovGraus = 60.0; // O mesmo FOV da sua função de renderização
        double fovRad = fovGraus * M_PI / 180.0;

        // Encontra o maior "raio" da cena (altura ou largura)
        double raioCena = std::max(larguraCena, alturaCena) / 2.0;

        // Usa trigonometria (tan(FOV/2) = Raio / Distância)
        double distancia = raioCena / tan(fovRad / 2.0);

        // Afasta a câmera para esta distância, mais uma margem de 10%
        double z_camera = centroCena.z() + distancia * 1.1;

        windowObj.camera_centro = Ponto(centroCena.x(), centroCena.y(), z_camera);
        windowObj.camera_zoom = 1.0; // Zoom não é usado diretamente em perspectiva
    }
}

// --- Carregador de .obj ---
ObjetoVirtual MainWindow::carregarObjetoOBJ(const QString& caminhoArquivo, const QString& nomeObjeto, QColor cor) {
    ObjetoVirtual objeto;
    objeto.nome = nomeObjeto;
    objeto.cor = cor;
    objeto.tipo = TipoObjeto::Mesh3D;

    QFile arquivo(caminhoArquivo);
    if (!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "ERRO: Não foi possível abrir o arquivo OBJ:" << caminhoArquivo;
        return objeto;
    }

    QVector<Ponto> vertices_temp; // Armazena vértices na ordem do arquivo

    QTextStream in(&arquivo);
    while (!in.atEnd()) {
        QString linha = in.readLine().trimmed();
        QStringList partes = linha.split(' ', Qt::SkipEmptyParts);
        if (partes.isEmpty()) continue;

        if (partes[0] == "v") { // Vértice
            if (partes.size() >= 4) {
                vertices_temp.append(Ponto(partes[1].toDouble(), partes[2].toDouble(), partes[3].toDouble()));
            }
        } else if (partes[0] == "f") { // Face
            if (partes.size() >= 4) {
                Face face;
                for (int i = 1; i < partes.size(); ++i) {
                    QStringList indicesStr = partes[i].split('/');
                    int indiceVertice = indicesStr[0].toInt();
                    face.indicesVertices.append(indiceVertice - 1); // .obj é 1-based
                }
                objeto.faces.append(face);
            }
        }
    }
    arquivo.close();

    // Copia os vértices para o objeto final
    // (Alguns .obj definem vértices que não são usados, mas esta é a forma mais simples)
    objeto.vertices = vertices_temp;

    qInfo() << "Objeto" << nomeObjeto << "carregado com" << objeto.vertices.size() << "vértices e" << objeto.faces.size() << "faces.";
    return objeto;
}

void MainWindow::atualizarComboBoxDeObjetos() {
    ui->objectSelectorComboBox->clear();
    for (const ObjetoVirtual &objeto : displayFile) {
        ui->objectSelectorComboBox->addItem(objeto.nome);
    }
}

void MainWindow::on_panUpButton_clicked() {
    if (indiceDaWindow == -1) return;
    // Modifica a propriedade camera_centro (Resolve o "deslize")
    displayFile[indiceDaWindow].camera_centro.setY(displayFile[indiceDaWindow].camera_centro.y() + 10);
    ui->TelaDesenho->update();
}

void MainWindow::on_panDownButton_clicked() {
    if (indiceDaWindow == -1) return;
    displayFile[indiceDaWindow].camera_centro.setY(displayFile[indiceDaWindow].camera_centro.y() - 10);
    ui->TelaDesenho->update();
}

void MainWindow::on_panLeftButton_clicked() {
    if (indiceDaWindow == -1) return;
    displayFile[indiceDaWindow].camera_centro.setX(displayFile[indiceDaWindow].camera_centro.x() - 10);
    ui->TelaDesenho->update();
}

void MainWindow::on_panRightButton_clicked() {
    if (indiceDaWindow == -1) return;
    displayFile[indiceDaWindow].camera_centro.setX(displayFile[indiceDaWindow].camera_centro.x() + 10);
    ui->TelaDesenho->update();
}

void MainWindow::on_zoomInButton_clicked() {
    if (indiceDaWindow == -1) return;

    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    if (ui->radioOrtogonal->isChecked()) {
        // Zoom Ortogonal: Chama escalonarEixo() na câmera
        windowObj.escalonarEixo(1.1, 1.1, 1.1);
    } else {
        // Zoom em Perspectiva: Chama transladar() em Z na câmera
        // (Com os limites de segurança que implementámos)
        double zAtual = windowObj.camera_centro.z();
        double zNovo = zAtual - 10.0; // Mover para a frente
        double zMinimo = 2.0;

        if (zNovo >= zMinimo) {
            windowObj.transladar(0, 0, -10.0);
        } else {
            windowObj.camera_centro.setZ(zMinimo); // Prende no limite
        }
    }
    ui->TelaDesenho->update();
}

void MainWindow::on_zoomOutButton_clicked() {
    if (indiceDaWindow == -1) return;

    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    if (ui->radioOrtogonal->isChecked()) {
        // Zoom Ortogonal: Chama escalonarEixo() na câmera
        windowObj.escalonarEixo(0.9, 0.9, 0.9);
    } else {
        // Zoom em Perspectiva: Chama transladar() em Z na câmera
        // (Com os limites de segurança)
        double zAtual = windowObj.camera_centro.z();
        double zNovo = zAtual + 10.0; // Mover para trás
        double zMaximo = 1000.0;

        if (zNovo <= zMaximo) {
            windowObj.transladar(0, 0, 10.0);
        } else {
            windowObj.camera_centro.setZ(zMaximo); // Prende no limite
        }
    }
    ui->TelaDesenho->update();
}

// --- SLOTS DE TRANSFORMAÇÃO DE OBJETO (3D) ---
// Estes botões transformam o objeto selecionado

void MainWindow::on_translateButton_clicked() {
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice < 0) return;

    double dx = ui->translateXSpinBox->value();
    double dy = ui->translateYSpinBox->value();

    // Lê o valor do novo SpinBox para Z
    double dz = ui->translateZSpinBox->value();

    displayFile[indice].transladar(dx, dy, dz);
    ui->TelaDesenho->update();
}

void MainWindow::on_rotationEixoButton_clicked()
{
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice == -1) indice = indiceDaWindow; // Se nada estiver selecionado, gira a Câmera

    // 1. Pega os ângulos dos SpinBoxes de objeto (os _1)
    double anguloX = ui->rotationXSpinBox->value();
    double anguloY = ui->rotationYSpinBox->value();
    double anguloZ = ui->rotationZSpinBox->value();

    if (indice == indiceDaWindow) {
        // --- LÓGICA DA CÂMERA (Girar no lugar) ---
        displayFile[indiceDaWindow].camera_rotX += anguloX;
        displayFile[indiceDaWindow].camera_rotY += anguloY;
        displayFile[indiceDaWindow].camera_rotZ += anguloZ;
    } else {
        // --- LÓGICA DO OBJETO (Girar no próprio eixo) ---
        // (Chama as funções limpas do objetovirtual.cpp)
        if (anguloX != 0.0) displayFile[indice].rotacionarEixoX(anguloX);
        if (anguloY != 0.0) displayFile[indice].rotacionarEixoY(anguloY);
        if (anguloZ != 0.0) displayFile[indice].rotacionarEixoZ(anguloZ);
    }

    ui->TelaDesenho->update();
}

/**
 * Slot para "Rotacionar no Centro da Cena" (Orbitar)
 * Pokémon: Orbita em torno do "Ponto P".
 * Câmera: Orbita em torno do "Ponto P".
 */
void MainWindow::on_rotateCentroCenaButton_clicked()
{
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice == -1) indice = indiceDaWindow; // Se nada estiver selecionado, orbita a Câmera

    // 1. Pega os ângulos dos SpinBoxes de objeto (os _1)
    double anguloX = ui->rotationXSpinBox->value();
    double anguloY = ui->rotationYSpinBox->value();
    double anguloZ = ui->rotationZSpinBox->value();

    // 2. Calcula o "Ponto P"
    Ponto P = calcularCentroDaCena();

    // 3. Cria a Matriz de Órbita em torno de P
    Matriz T_ida = Matriz::criarMatrizTranslacao(-P.x(), -P.y(), -P.z());
    Matriz R_X = Matriz::criarMatrizRotacaoX(anguloX);
    Matriz R_Y = Matriz::criarMatrizRotacaoY(anguloY);
    Matriz R_Z = Matriz::criarMatrizRotacaoZ(anguloZ);
    Matriz T_volta = Matriz::criarMatrizTranslacao(P.x(), P.y(), P.z());
    Matriz M_orbita = T_volta * R_X * R_Y * R_Z * T_ida;

    if (indice == indiceDaWindow) {
        // --- LÓGICA DA CÂMERA (Orbitar Ponto P) ---
        // Transforma a POSIÇÃO da câmera
        displayFile[indiceDaWindow].camera_centro = M_orbita * displayFile[indiceDaWindow].camera_centro;
    } else {
        // --- LÓGICA DO OBJETO (Orbitar Ponto P) ---
        // Transforma cada VÉRTICE do objeto
        for (Ponto &v : displayFile[indice].vertices) {
            v = M_orbita * v;
        }
    }

    ui->TelaDesenho->update();
}

void MainWindow::on_escaleEixoButton_clicked() {
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice < 0) return;

    double sx = ui->escaleXSpinBox->value();
    double sy = ui->escaleYSpinBox->value();

    // Lê o valor do novo SpinBox para Z
    double sz = ui->escaleZSpinBox->value();

    // Proteção contra escala 0
    if (sx == 0) sx = 1.0;
    if (sy == 0) sy = 1.0;
    if (sz == 0) sz = 1.0;

    displayFile[indice].escalonarEixo(sx, sy, sz);
    ui->TelaDesenho->update();
}

void MainWindow::on_radioOrtogonal_toggled(bool checked)
{
    if (checked) {
        ui->TelaDesenho->setProjecao(TelaDeDesenho::ProjecaoTipo::ORTOGONAL);
    }
    ajustarWindowParaCena(); // Re-centraliza a câmera para o modo Perspectiva
}

void MainWindow::on_radioPerspectiva_toggled(bool checked)
{
    if (checked) {
        ui->TelaDesenho->setProjecao(TelaDeDesenho::ProjecaoTipo::PERSPECTIVA);
    }
    ajustarWindowParaCena(); // Re-centraliza a câmera para o modo Perspectiva
}

void MainWindow::lidarComZoom(double fator)
{
    if (indiceDaWindow == -1) return;

    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    if (ui->radioOrtogonal->isChecked()) {
        // --- ZOOM ORTOGONAL (Escala) ---

        // --- A LÓGICA NOVA (com Limites) ---
        // Primeiro, aplicamos o zoom como antes
        windowObj.escalonarEixo(fator, fator, fator);

        // Depois, verificamos se não passámos dos limites
        if (windowObj.camera_zoom < 0.01) { // Limite mínimo de zoom
            windowObj.camera_zoom = 0.01;
        }
        if (windowObj.camera_zoom > 100.0) { // Limite máximo de zoom
            windowObj.camera_zoom = 100.0;
        }

    } else {
        // --- ZOOM EM PERSPECTIVA (Mover em Z) ---

        double dz = (fator > 1.0) ? -10.0 : 10.0; // -10 (In) ou +10 (Out)

        // --- A LÓGICA NOVA (com Limites) ---
        // 1. Calcula a nova posição Z da câmera
        double zAtual = windowObj.camera_centro.z();
        double zNovo = zAtual + dz;

        // 2. Define os limites de segurança
        // (Não deixa a câmera chegar a menos de 2 unidades dos objetos em z=0)
        double zMinimo = 2.0;
        // (Não deixa a câmera afastar-se mais de 1000 unidades)
        double zMaximo = 1000.0;

        // 3. Aplica a translação APENAS se estiver dentro dos limites
        if (zNovo >= zMinimo && zNovo <= zMaximo) {
            windowObj.transladar(0, 0, dz);
        } else {
            // Se o zoom ultrapassou o limite, "prende" a câmera no limite
            if (zNovo < zMinimo) windowObj.camera_centro.setZ(zMinimo);
            if (zNovo > zMaximo) windowObj.camera_centro.setZ(zMaximo);
        }
    }

    ui->TelaDesenho->update();
}

Ponto MainWindow::calcularCentroDaCena() const
{
    double somaX = 0, somaY = 0, somaZ = 0;
    int totalVertices = 0;

    // Itera por todos os objetos no displayFile
    for (int i = 0; i < displayFile.size(); ++i) {
        // Pula a própria câmera
        if (i == indiceDaWindow) continue;

        // Soma os vértices de cada objeto
        for (const Ponto &v : displayFile[i].vertices) {
            somaX += v.x();
            somaY += v.y();
            somaZ += v.z();
            totalVertices++;
        }
    }

    if (totalVertices == 0) {
        return Ponto(0, 0, 0); // Retorna a origem se a cena estiver vazia
    }

    // Retorna a média (o seu "Ponto P")
    return Ponto(somaX / totalVertices, somaY / totalVertices, somaZ / totalVertices);
}

