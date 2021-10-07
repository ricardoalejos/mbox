#ifndef _MBOX_SHAPE_H_
#define _MBOX_SHAPE_H_

enum MBox_Shape {
    MBox_Shape_UNSIGNED_64B_INTEGER,
    MBox_Shape_SIGNED_64B_INTEGER,
    MBox_Shape_DOUBLE,
    MBox_Shape_STRING,
    MBox_Shape_BOOLEAN,
    MBox_Shape_REFERENCE,
    MBox_Shape_LIST_REFERENCE,
    MBox_Shape_DICTIONARY_REFERENCE,
    MBox_Shape_CUSTOM,
    MBox_Shape_NULL,
    MBox_Shape_NUMBER_OF_SHAPES
};

#endif
