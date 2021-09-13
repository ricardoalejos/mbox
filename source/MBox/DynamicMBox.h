#ifndef _MBOX_DYNAMICMBOX_H_
#define _MBOX_DYNAMICMBOX_H_

#include "MBox/MBox.h"

enum MBox_DynamicMBoxError {
    MBox_DynamicMBoxError_MALLOC_FAILED = MBox_MBoxError_ERROR_BASE,
    MBox_DynamicMBoxError_REALLOC_FAILED
};

int DynamicMBox_create(struct MBox_MBox ** self);

#endif
