/****************************************************************************
** Meta object code from reading C++ file 'application.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ChatClient/application.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Application_t {
    QByteArrayData data[11];
    char stringdata[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Application_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Application_t qt_meta_stringdata_Application = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Application"
QT_MOC_LITERAL(1, 12, 17), // "valueChangedConvo"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "valueChangedUsr"
QT_MOC_LITERAL(4, 47, 15), // "valueUsrRemoved"
QT_MOC_LITERAL(5, 63, 36), // "on_actionConnect_to_server_tr..."
QT_MOC_LITERAL(6, 100, 9), // "addToList"
QT_MOC_LITERAL(7, 110, 14), // "removeFromList"
QT_MOC_LITERAL(8, 125, 18), // "on_btnSend_clicked"
QT_MOC_LITERAL(9, 144, 15), // "onReturnPressed"
QT_MOC_LITERAL(10, 160, 30) // "on_action_save_convo_triggered"

    },
    "Application\0valueChangedConvo\0\0"
    "valueChangedUsr\0valueUsrRemoved\0"
    "on_actionConnect_to_server_triggered\0"
    "addToList\0removeFromList\0on_btnSend_clicked\0"
    "onReturnPressed\0on_action_save_convo_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Application[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    1,   62,    2, 0x06 /* Public */,
       4,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   68,    2, 0x08 /* Private */,
       6,    1,   69,    2, 0x08 /* Private */,
       7,    1,   72,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Application::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Application *_t = static_cast<Application *>(_o);
        switch (_id) {
        case 0: _t->valueChangedConvo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->valueChangedUsr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->valueUsrRemoved((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_actionConnect_to_server_triggered(); break;
        case 4: _t->addToList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->removeFromList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->on_btnSend_clicked(); break;
        case 7: _t->onReturnPressed(); break;
        case 8: _t->on_action_save_convo_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Application::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Application::valueChangedConvo)) {
                *result = 0;
            }
        }
        {
            typedef void (Application::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Application::valueChangedUsr)) {
                *result = 1;
            }
        }
        {
            typedef void (Application::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Application::valueUsrRemoved)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Application::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Application.data,
      qt_meta_data_Application,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Application.stringdata))
        return static_cast<void*>(const_cast< Application*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Application::valueChangedConvo(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Application::valueChangedUsr(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Application::valueUsrRemoved(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
