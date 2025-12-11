/****************************************************************************
** Meta object code from reading C++ file 'dugraphicsscene.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dugraphicsscene.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dugraphicsscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
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
struct qt_meta_tag_ZN15DuGraphicsSceneE_t {};
} // unnamed namespace

template <> constexpr inline auto DuGraphicsScene::qt_create_metaobjectdata<qt_meta_tag_ZN15DuGraphicsSceneE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DuGraphicsScene",
        "scoreChanged",
        "",
        "newScore",
        "speedChanged",
        "newSpeed",
        "gameWin",
        "gameLose",
        "gameOver",
        "gameReset",
        "gameQuit"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'scoreChanged'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'speedChanged'
        QtMocHelpers::SignalData<void(int)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Signal 'gameWin'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gameLose'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gameOver'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gameReset'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gameQuit'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DuGraphicsScene, qt_meta_tag_ZN15DuGraphicsSceneE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DuGraphicsScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15DuGraphicsSceneE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15DuGraphicsSceneE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15DuGraphicsSceneE_t>.metaTypes,
    nullptr
} };

void DuGraphicsScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DuGraphicsScene *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->scoreChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->speedChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->gameWin(); break;
        case 3: _t->gameLose(); break;
        case 4: _t->gameOver(); break;
        case 5: _t->gameReset(); break;
        case 6: _t->gameQuit(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DuGraphicsScene::*)(int )>(_a, &DuGraphicsScene::scoreChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DuGraphicsScene::*)(int )>(_a, &DuGraphicsScene::speedChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DuGraphicsScene::*)()>(_a, &DuGraphicsScene::gameWin, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (DuGraphicsScene::*)()>(_a, &DuGraphicsScene::gameLose, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (DuGraphicsScene::*)()>(_a, &DuGraphicsScene::gameOver, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (DuGraphicsScene::*)()>(_a, &DuGraphicsScene::gameReset, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (DuGraphicsScene::*)()>(_a, &DuGraphicsScene::gameQuit, 6))
            return;
    }
}

const QMetaObject *DuGraphicsScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DuGraphicsScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15DuGraphicsSceneE_t>.strings))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int DuGraphicsScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DuGraphicsScene::scoreChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void DuGraphicsScene::speedChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void DuGraphicsScene::gameWin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DuGraphicsScene::gameLose()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DuGraphicsScene::gameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void DuGraphicsScene::gameReset()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void DuGraphicsScene::gameQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
