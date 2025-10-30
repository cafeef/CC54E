// Em face.h
#ifndef FACE_H
#define FACE_H

#include <QVector>

struct Face {
    // Uma lista de índices que apontam para os vértices no
    // vetor de vértices do ObjetoVirtual.
    QVector<int> indicesVertices;
};

#endif // FACE_H
