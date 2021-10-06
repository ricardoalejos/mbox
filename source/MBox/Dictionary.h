#ifndef _MBOX_DICTIONARY_H_
#define _MBOX_DICTIONARY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MBox/MBox.h"
#include "MBox/List.h"


struct MBox_DictionaryEntry {
    struct MBox_MBox * key;
    struct MBox_MBox * value;
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

    // Quick getters
    struct MBox_MBox * (*readValue)(
        struct MBox_Dictionary * self,
        struct MBox_MBox * key
    );
    struct MBox_MBox * (*addValue)(
        struct MBox_Dictionary * self,
        struct MBox_MBox * key
    );
    unsigned int (*getLength2)(
        struct MBox_Dictionary * self
    );
    bool(*isEmpty2)(struct MBox_Dictionary * self);
    bool (*hasKey2)(
        struct MBox_Dictionary * self,
        struct MBox_MBox * key
    );
    struct MBox_MBox * (*seeValueWithStringKey)(
        struct MBox_Dictionary * self,
        char * stringKey
    );

    // Current key
    struct MBox_MBox * key;
    struct MBox_MBox * (*getValueMBox)(
        struct MBox_Dictionary * self,
        bool createIfMissing
    );
    struct MBox_MBox * (*getValue2)(
        struct MBox_Dictionary * self
    );
    int (*removeEntry)(struct MBox_Dictionary * self);
};

#define MBox_addEntry(dict) ((dict)->getValueMBox((dict), true))
#define MBox_getEntry(dict) ((dict)->getValueMBox((dict), false))
#define MBox_hasEntry(dict) (MBox_getEntry((dict)) != NULL)
#define MBox_delEntry(dict) ((dict)->removeEntry((dict)))
#define MBox_getDictLength(dict) ((dict)->getLength2((dict)))

#ifdef __cplusplus
} // Extern "C"
#endif

#endif
