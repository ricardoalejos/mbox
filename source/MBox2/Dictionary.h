#ifndef _MBOX_DICTIONARY_H_
#define _MBOX_DICTIONARY_H_

#include "MBox2/MBox.h"

struct MBox_Dictionary {
    struct MBox_Box * (*getBoxFromDictionary)(struct MBox_Dictionary * self, struct MBox_Box * key);
    struct MBox_Box * (*popBoxFromDictionary)(struct MBox_Dictionary * self, struct MBox_Box * key);
    bool (*isKeyInDictionary)(struct MBox_Dictionary * self, struct MBox_Box * key);
    enum MBox_Error (*removeBoxFromDictionary)(struct MBox_Dictionary * dict, struct MBox_Box * key);
    size_t (*getDictionaryLength)(struct MBox_Dictionary * self);
    bool (*isDictionaryEmpty)(struct MBox_Dictionary * self);
    enum MBox_Error (*getLastDictionaryError)(struct MBox_Dictionary * self);
    struct MBox_List * (*createDictionaryKeyList)(struct MBox_Dictionary * self);
    enum MBox_Error (*addSimilarBoxToDictionary)(struct MBox_Dictionary * self, struct MBox_Box * key, struct MBox_Box * box);
    struct MBox_Box * (*addEmptyBoxToDictionary)(struct MBox_Dictionary * self, struct MBox_Box * key);
    enum MBox_Error (*extendDictionary)(struct MBox_Dictionary *self, struct MBox_Dictionary * src);
    enum MBox_Error (*mapDictionary)(struct MBox_Dictionary * self, MBox_dictMapCallback function, void * args);
    enum MBox_Error (*clearLastDictionaryError)(struct MBox_Dictionary * dict);
};

#endif
