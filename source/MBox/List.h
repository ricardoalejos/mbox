#ifndef _MBOX_LIST_H_
#define _MBOX_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

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
    int (*contains)(
        struct MBox_List * self,
        struct MBox_MBox * item,
        bool * answer
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

    // Quick getters

    struct MBox_MBox *  (*seeItem)(
        struct MBox_List * self,
        int index
    );
    unsigned int (*seeLength)(
        struct MBox_List * self
    );
};

#ifdef __cplusplus
} // Extern "C"
#endif

#endif
