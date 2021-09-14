#ifndef _MBOX_DYNAMICDICTIONARY_H_
#define _MBOX_DYNAMICDICTIONARY_H_

#include "MBox/Dictionary.h"

enum MBox_DynamicDictionaryError {
    MBox_DynamicDictionaryError_MALLOC_FAILED = MBox_DictionaryError_ERROR_BASE,
    MBox_DynamicDictionaryError_REALLOC_FAILED
};

int MBox_createDynamicDictionary(struct MBox_Dictionary ** self);

#endif
