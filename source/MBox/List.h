#ifndef _MBOX_LIST_H_
#define _MBOX_LIST_H_

#include "MBox/MBox.h"

enum MBox_ListError {
    MBox_ListError_INVALID_INDEX = MBox_MBoxError_ERROR_BASE,
    MBox_ListError_ITEM_NOT_FOUND,
    MBox_ListError_MBOX_COPY_FAILED,
    MBox_ListError_INVALID_OPERATION_IN_EMPTY_LIST,
    MBox_ListError_ERROR_BASE
};

struct MBox_List {
    int (*getLength)(
        struct MBox_List * self,
        unsigned int * length
    );
    int (*addItem)(
        struct MBox_List * self,
        struct MBox_MBox * item
    );
    int (*getItem)(
        struct MBox_List * self,
        int index,
        struct MBox_MBox * itemBuffer
    );
    int (*pop)(
        struct MBox_List * self,
        int index,
        struct MBox_MBox ** item
    );
    int (*getIndexOf)(
        struct MBox_List * self,
        struct MBox_MBox * item,
        int * index
    );
    int (*remove)(
        struct MBox_List * self,
        struct MBox_MBox * item
    );
    int (*insert)(
        struct MBox_List * self,
        unsigned int index,
        struct MBox_MBox * item
    );
    int (*destroy)(
        struct MBox_List ** self
    );
};

#endif
