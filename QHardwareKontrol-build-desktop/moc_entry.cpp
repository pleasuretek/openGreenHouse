/****************************************************************************
** Meta object code from reading C++ file 'entry.h'
**
** Created: Wed Feb 8 22:25:50 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QHardwareKontrol/entry.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'entry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Entry[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,    6,    7,    6, 0x0a,
      33,    6,    6,    6, 0x0a,
      58,    6,    6,    6, 0x0a,
      67,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Entry[] = {
    "Entry\0\0QList<QVariant>\0getAmts()\0"
    "setAmts(QList<QVariant>)\0setImg()\0"
    "getImg()\0"
};

const QMetaObject Entry::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Entry,
      qt_meta_data_Entry, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Entry::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Entry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Entry::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Entry))
        return static_cast<void*>(const_cast< Entry*>(this));
    return QDialog::qt_metacast(_clname);
}

int Entry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QList<QVariant> _r = getAmts();
            if (_a[0]) *reinterpret_cast< QList<QVariant>*>(_a[0]) = _r; }  break;
        case 1: setAmts((*reinterpret_cast< QList<QVariant>(*)>(_a[1]))); break;
        case 2: setImg(); break;
        case 3: getImg(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
