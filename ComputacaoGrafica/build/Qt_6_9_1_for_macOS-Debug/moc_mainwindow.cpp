/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "criarCasaCompleta",
        "QList<ObjetoVirtual>",
        "",
        "x_centro",
        "y_centro",
        "nome_base",
        "criarFlor",
        "criarPikachu",
        "on_translateButton_clicked",
        "on_escaleButton_clicked",
        "on_rotationButton_clicked",
        "on_escaleEixoButton_clicked",
        "on_rotationEixoButton_clicked",
        "on_panLeftButton_clicked",
        "on_panUpButton_clicked",
        "on_panRightButton_clicked",
        "on_panDownButton_clicked",
        "on_zoomInButton_clicked",
        "on_zoomOutButton_clicked",
        "on_rotateRightButton_clicked",
        "on_rotateLeftButton_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'criarCasaCompleta'
        QtMocHelpers::SlotData<QVector<ObjetoVirtual>(double, double, const QString &)>(1, 3, QMC::AccessPrivate, 0x80000000 | 2, {{
            { QMetaType::Double, 4 }, { QMetaType::Double, 5 }, { QMetaType::QString, 6 },
        }}),
        // Slot 'criarFlor'
        QtMocHelpers::SlotData<QVector<ObjetoVirtual>(double, double, const QString &)>(7, 3, QMC::AccessPrivate, 0x80000000 | 2, {{
            { QMetaType::Double, 4 }, { QMetaType::Double, 5 }, { QMetaType::QString, 6 },
        }}),
        // Slot 'criarPikachu'
        QtMocHelpers::SlotData<QVector<ObjetoVirtual>(double, double, const QString &)>(8, 3, QMC::AccessPrivate, 0x80000000 | 2, {{
            { QMetaType::Double, 4 }, { QMetaType::Double, 5 }, { QMetaType::QString, 6 },
        }}),
        // Slot 'on_translateButton_clicked'
        QtMocHelpers::SlotData<void()>(9, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_escaleButton_clicked'
        QtMocHelpers::SlotData<void()>(10, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_rotationButton_clicked'
        QtMocHelpers::SlotData<void()>(11, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_escaleEixoButton_clicked'
        QtMocHelpers::SlotData<void()>(12, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_rotationEixoButton_clicked'
        QtMocHelpers::SlotData<void()>(13, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_panLeftButton_clicked'
        QtMocHelpers::SlotData<void()>(14, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_panUpButton_clicked'
        QtMocHelpers::SlotData<void()>(15, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_panRightButton_clicked'
        QtMocHelpers::SlotData<void()>(16, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_panDownButton_clicked'
        QtMocHelpers::SlotData<void()>(17, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_zoomInButton_clicked'
        QtMocHelpers::SlotData<void()>(18, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_zoomOutButton_clicked'
        QtMocHelpers::SlotData<void()>(19, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_rotateRightButton_clicked'
        QtMocHelpers::SlotData<void()>(20, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_rotateLeftButton_clicked'
        QtMocHelpers::SlotData<void()>(21, 3, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QList<ObjetoVirtual> _r = _t->criarCasaCompleta((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QList<ObjetoVirtual>*>(_a[0]) = std::move(_r); }  break;
        case 1: { QList<ObjetoVirtual> _r = _t->criarFlor((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QList<ObjetoVirtual>*>(_a[0]) = std::move(_r); }  break;
        case 2: { QList<ObjetoVirtual> _r = _t->criarPikachu((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QList<ObjetoVirtual>*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->on_translateButton_clicked(); break;
        case 4: _t->on_escaleButton_clicked(); break;
        case 5: _t->on_rotationButton_clicked(); break;
        case 6: _t->on_escaleEixoButton_clicked(); break;
        case 7: _t->on_rotationEixoButton_clicked(); break;
        case 8: _t->on_panLeftButton_clicked(); break;
        case 9: _t->on_panUpButton_clicked(); break;
        case 10: _t->on_panRightButton_clicked(); break;
        case 11: _t->on_panDownButton_clicked(); break;
        case 12: _t->on_zoomInButton_clicked(); break;
        case 13: _t->on_zoomOutButton_clicked(); break;
        case 14: _t->on_rotateRightButton_clicked(); break;
        case 15: _t->on_rotateLeftButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
