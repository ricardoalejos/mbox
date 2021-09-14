#ifndef _MBOX_DYNAMICLIST_H_
#define _MBOX_DYNAMICLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MBox/List.h"

enum MBox_DynamicListError{
    MBox_DynamicListError_MALLOC_FAILED = MBox_ListError_ERROR_BASE
};

int MBox_createDynamicList(
    struct MBox_List ** self
);

#ifdef __cplusplus
} // Extern "C"
#endif

#endif
