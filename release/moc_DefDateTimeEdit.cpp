/****************************************************************************
** Meta object code from reading C++ file 'DefDateTimeEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DefDateTimeEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DefDateTimeEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DefDateTimeEdit_t {
    QByteArrayData data[6];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DefDateTimeEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DefDateTimeEdit_t qt_meta_stringdata_DefDateTimeEdit = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DefDateTimeEdit"
QT_MOC_LITERAL(1, 16, 11), // "setFinished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "dateTime"
QT_MOC_LITERAL(4, 38, 16), // "setStartDateTime"
QT_MOC_LITERAL(5, 55, 11) // "getDateTime"

    },
    "DefDateTimeEdit\0setFinished\0\0dateTime\0"
    "setStartDateTime\0getDateTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DefDateTimeEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QDateTime,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QDateTime,    3,
    QMetaType::Void, QMetaType::QDateTime,    3,

       0        // eod
};

void DefDateTimeEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DefDateTimeEdit *_t = static_cast<DefDateTimeEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFinished((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 1: _t->setStartDateTime((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 2: _t->getDateTime((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DefDateTimeEdit::*_t)(const QDateTime & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DefDateTimeEdit::setFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DefDateTimeEdit::staticMetaObject = {
    { &QDateTimeEdit::staticMetaObject, qt_meta_stringdata_DefDateTimeEdit.data,
      qt_meta_data_DefDateTimeEdit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DefDateTimeEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DefDateTimeEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DefDateTimeEdit.stringdata0))
        return static_cast<void*>(const_cast< DefDateTimeEdit*>(this));
    return QDateTimeEdit::qt_metacast(_clname);
}

int DefDateTimeEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDateTimeEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DefDateTimeEdit::setFinished(const QDateTime & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
