#ifndef _MBOX_LIST_H_
#define _MBOX_LIST_H_

#include "MBox/MBox.h"

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
        unsigned int index,
        struct MBox_MBox ** item
    );
    int (*pop)(
        struct MBox_List * self,
        unsigned int length
    );
    int (*contains)(
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
