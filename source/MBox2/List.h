#ifndef _MBOX_LIST_H_
#define _MBOX_LIST_H_

#include "MBox2/MBox.h"

struct MBox_List {
    struct MBox_Box * (*getBoxFromList)(struct MBox_List * self, int index);
    int (*getIndexOfSimilarBoxInList)(struct MBox_List * self, struct MBox_Box * box);
    struct MBox_Box * (*popBoxFromList)(struct MBox_List * self, int index);
    enum MBox_Error (*removeBoxFromList)(struct MBox_List * list, int index);
    bool (*isSimilarBoxInList)(struct MBox_List * self, struct MBox_Box * box);
    enum MBox_Error (*removeSimilarBoxFromList)(struct MBox_List * self, struct MBox_Box * box);
    enum MBox_Error (*appendSimilarBoxFromList)(struct MBox_List * self, struct MBox_Box * box);
    enum MBox_Error (*insertSimilarBoxFromList)(struct MBox_List * self, int index, struct MBox_Box * box);
    struct MBox_Box * (*appendEmptyBoxToList)(struct MBox_List * self);
    struct MBox_Box * (*insertEmptyBoxToList)(struct MBox_List * self, int index);
    size_t (*getListLength)(struct MBox_List * self);
    bool (*isListEmpty)(struct MBox_List * self);
    enum MBox_Error (*getLastListError)(struct MBox_List * self);
    enum MBox_Error (*extendList)(struct MBox_List * self, struct MBox_List * src);
    enum MBox_Error (*mapList)(struct MBox_List * self, MBox_listMapCallback function, void * args);
    enum MBox_Error (*clearLastListError)(struct MBox_List * list);
};

#endif
