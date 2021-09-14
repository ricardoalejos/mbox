#ifndef _MBOX_DYNAMICMBOX_H_
#define _MBOX_DYNAMICMBOX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MBox/MBox.h"

enum MBox_DynamicMBoxError {
    MBox_DynamicMBoxError_MALLOC_FAILED = MBox_MBoxError_ERROR_BASE,
    MBox_DynamicMBoxError_REALLOC_FAILED
};

int MBox_createDynamicMBox(struct MBox_MBox ** self);

#ifdef __cplusplus
} // Extern "C"
#endif

#endif
