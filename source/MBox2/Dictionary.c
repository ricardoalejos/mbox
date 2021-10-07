#include "MBox2/Dictionary.h"

struct MBox_Box * MBox_getBoxFromDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key) {
    return dict->getBoxFromDictionary(dict, key);
}

struct MBox_Box * MBox_popBoxFromDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key) {
    return dict->popBoxFromDictionary(dict, key);
}

bool MBox_isKeyInDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key) {
    return dict->isKeyInDictionary(dict, key);
}

enum MBox_Error MBox_removeBoxFromDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key) {
    return dict->removeBoxFromDictionary(dict, key);
}

size_t MBox_getDictionaryLength(struct MBox_Dictionary * dict) {
    return dict->getDictionaryLength(dict);
}

bool MBox_isDictionaryEmpty(struct MBox_Dictionary * dict) {
    return dict->isDictionaryEmpty(dict);
}

enum MBox_Error MBox_getLastDictionaryError(struct MBox_Dictionary * dict) {
    return dict->getLastDictionaryError(dict);
}
struct MBox_List * MBox_createDictionaryKeyList(struct MBox_Dictionary * dict) {
    return dict->createDictionaryKeyList(dict);
}

enum MBox_Error MBox_addSimilarBoxToDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key, struct MBox_Box * box) {
    return dict->addSimilarBoxToDictionary(dict, key, box);
}

struct MBox_Box * MBox_addEmptyBoxToDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key) {
    return dict->addEmptyBoxToDictionary(dict, key);
}

enum MBox_Error MBox_extendDictionary(struct MBox_Dictionary * dst, struct MBox_Dictionary * src) {
    return dst->extendDictionary(dst, src);
}

enum MBox_Error MBox_mapDictionary(struct MBox_Dictionary * dict, MBox_dictMapCallback function, void * args) {
    return dict->mapDictionary(dict, function, args);
}

enum MBox_Error MBox_clearLastDictionaryError(struct MBox_Dictionary * dict) {
    return dict->clearLastDictionaryError(dict);
}