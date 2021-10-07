#include "MBox2/List.h"

struct MBox_Box * MBox_getBoxFromList(struct MBox_List * list, int index) {
    return list->getBoxFromList(list, index);
}

int MBox_getIndexOfSimilarBoxInList(struct MBox_List * list, struct MBox_Box * box) {
    return list->getIndexOfSimilarBoxInList(list, box);
}

struct MBox_Box * MBox_popBoxFromList(struct MBox_List * list, int index) {
    return list->popBoxFromList(list, index);
}

enum MBox_Error MBox_removeBoxFromList(struct MBox_List * list, int index) {
    return list->removeBoxFromList(list, index);
}

bool MBox_isSimilarBoxInList(struct MBox_List * list, struct MBox_Box * box) {
    return list->isSimilarBoxInList(list, box);
}

enum MBox_Error MBox_removeSimilarBoxFromList(struct MBox_List * list, struct MBox_Box * box) {
    return list->removeSimilarBoxFromList(list, box);
}

enum MBox_Error MBox_appendSimilarBoxFromList(struct MBox_List * list, struct MBox_Box * box) {
    return list->appendSimilarBoxFromList(list, box);
}

enum MBox_Error MBox_insertSimilarBoxFromList(struct MBox_List * list, int index, struct MBox_Box * box) {
    return list->insertSimilarBoxFromList(list, index, box);
}

struct MBox_Box * MBox_appendEmptyBoxToList(struct MBox_List * list) {
    return list->appendEmptyBoxToList(list);
}

struct MBox_Box * MBox_insertEmptyBoxToList(struct MBox_List * list, int index) {
    return list->insertEmptyBoxToList(list, index);
}

size_t MBox_getListLength(struct MBox_List * list) {
    return list->getListLength(list);
}

bool MBox_isListEmpty(struct MBox_List * list) {
    return list->isListEmpty(list);
}

enum MBox_Error MBox_getLastListError(struct MBox_List * list) {
    return list->getLastListError(list);
}

enum MBox_Error MBox_extendList(struct MBox_List * dst, struct MBox_List * src) {
    return dst->extendList(dst, src);
}

enum MBox_Error MBox_mapList(struct MBox_List * list, MBox_listMapCallback function, void * args) {
    return list->mapList(list, function, args);
}

enum MBox_Error MBox_clearLastListError(struct MBox_List * list) {
    return list->clearLastListError(list);
}
