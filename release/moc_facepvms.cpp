/****************************************************************************
** Meta object code from reading C++ file 'facepvms.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../facepvms.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'facepvms.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_facePvms_t {
    QByteArrayData data[18];
    char stringdata0[360];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_facePvms_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_facePvms_t qt_meta_stringdata_facePvms = {
    {
QT_MOC_LITERAL(0, 0, 8), // "facePvms"
QT_MOC_LITERAL(1, 9, 11), // "textChanged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "stateChanged"
QT_MOC_LITERAL(4, 35, 16), // "setStartDateTime"
QT_MOC_LITERAL(5, 52, 8), // "dateTime"
QT_MOC_LITERAL(6, 61, 14), // "setEndDateTime"
QT_MOC_LITERAL(7, 76, 9), // "readFrame"
QT_MOC_LITERAL(8, 86, 20), // "ImageListItemClicked"
QT_MOC_LITERAL(9, 107, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(10, 124, 4), // "item"
QT_MOC_LITERAL(11, 129, 28), // "on_pushButton_search_clicked"
QT_MOC_LITERAL(12, 158, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(13, 185, 35), // "on_pushbutton_device_config_c..."
QT_MOC_LITERAL(14, 221, 33), // "on_pushbutton_device_open_cli..."
QT_MOC_LITERAL(15, 255, 34), // "on_pushButton_device_close_cl..."
QT_MOC_LITERAL(16, 290, 32), // "on_pushButton_pathSelect_clicked"
QT_MOC_LITERAL(17, 323, 36) // "on_pushButton_storageConfirm_..."

    },
    "facePvms\0textChanged\0\0stateChanged\0"
    "setStartDateTime\0dateTime\0setEndDateTime\0"
    "readFrame\0ImageListItemClicked\0"
    "QListWidgetItem*\0item\0"
    "on_pushButton_search_clicked\0"
    "on_pushButton_save_clicked\0"
    "on_pushbutton_device_config_clicked\0"
    "on_pushbutton_device_open_clicked\0"
    "on_pushButton_device_close_clicked\0"
    "on_pushButton_pathSelect_clicked\0"
    "on_pushButton_storageConfirm_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_facePvms[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    1,   81,    2, 0x08 /* Private */,
       6,    1,   84,    2, 0x08 /* Private */,
       7,    0,   87,    2, 0x08 /* Private */,
       8,    1,   88,    2, 0x08 /* Private */,
      11,    0,   91,    2, 0x08 /* Private */,
      12,    0,   92,    2, 0x08 /* Private */,
      13,    0,   93,    2, 0x08 /* Private */,
      14,    0,   94,    2, 0x08 /* Private */,
      15,    0,   95,    2, 0x08 /* Private */,
      16,    0,   96,    2, 0x08 /* Private */,
      17,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDateTime,    5,
    QMetaType::Void, QMetaType::QDateTime,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void facePvms::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        facePvms *_t = static_cast<facePvms *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->textChanged(); break;
        case 1: _t->stateChanged(); break;
        case 2: _t->setStartDateTime((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 3: _t->setEndDateTime((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 4: _t->readFrame(); break;
        case 5: _t->ImageListItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_search_clicked(); break;
        case 7: _t->on_pushButton_save_clicked(); break;
        case 8: _t->on_pushbutton_device_config_clicked(); break;
        case 9: _t->on_pushbutton_device_open_clicked(); break;
        case 10: _t->on_pushButton_device_close_clicked(); break;
        case 11: _t->on_pushButton_pathSelect_clicked(); break;
        case 12: _t->on_pushButton_storageConfirm_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject facePvms::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_facePvms.data,
      qt_meta_data_facePvms,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *facePvms::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *facePvms::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_facePvms.stringdata0))
        return static_cast<void*>(const_cast< facePvms*>(this));
    return QWidget::qt_metacast(_clname);
}

int facePvms::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
