#ifndef _MBOX_DICTIONARY_H_
#define _MBOX_DICTIONARY_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "MBox/MBox.h"
#include "MBox/List.h"

enum MBox_DictionaryError {
    MBox_DictionaryError_SUCCESS,
    MBox_DictionaryError_KEY_NOT_FOUND,
    MBox_DictionaryError_CANNOT_STORE_VALUE_IN_BUFFER,
    MBox_DictionaryError_ERROR_BASE
};

struct MBox_Dictionary {
    int (*getValue)(
        struct MBox_Dictionary * self,
        struct MBox_MBox * key,
        struct MBox_MBox * itemBuffer
    );
    int (*setValue)(
        struct MBox_Dictionary * self,
        struct MBox_MBox * key,
        struct MBox_MBox * itemBuffer
    );
    int (*remove)(
        struct MBox_Dictionary * self,
        struct MBox_MBox * key
    );
    int (*hasKey)(
        struct MBox_Dictionary * self,
        struct MBox_MBox * key,
        bool * response
    );
    int (*isEmpty)(
        struct MBox_Dictionary * self,
        bool * response
    );
    int (*addKeysToList)(
        struct MBox_Dictionary * self,
        struct MBox_List * targetList
    );
    int (*getLength)(
        struct MBox_Dictionary * self,
        unsigned int * length
    );
    int (*reset)(
        struct MBox_Dictionary * self
    );
    int (*destroy)(
        struct MBox_Dictionary ** self
    );
};

#ifdef __cplusplus
} // Extern "C"
#endif

#endif
