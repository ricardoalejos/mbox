#include "MBox/DynamicList.h"
#include <stdlib.h>

struct Node {
    struct MBox_MBox * value;
    struct Node * previous;
    struct Node * next;
};

struct DynamicList {
    struct MBox_List base;
    struct Node * root;
    unsigned int length;
};

static int getLength(
    struct MBox_List * self,
    unsigned int * length
);
static int addItem(
    struct MBox_List * self,
    struct MBox_MBox * item
);
static int getItem(
    struct MBox_List * self,
    int index,
    struct MBox_MBox ** item
);
static int pop(
    struct MBox_List * self,
    int index,
    struct MBox_MBox ** item
) ;
static int getIndexOf(
    struct MBox_List * self,
    struct MBox_MBox * item,
    int * index
);
static int remove(
    struct MBox_List * self,
    struct MBox_MBox * item
);
static int insert(
    struct MBox_List * self,
    unsigned int index,
    struct MBox_MBox * item
);
static int destroy(
    struct MBox_List ** self
);

int MBox_createDynamicList(
    struct MBox_List ** self
) {
    struct DynamicList * _this = (struct DynamicList *) malloc(
        sizeof(struct DynamicList)
    );

    _this->root = (struct Node *) malloc(sizeof(struct Node));
    _this->length = 0;
    _this->root->next = _this->root;
    _this->root->previous = _this->root;

    _this->base.addItem=addItem;
    _this->base.getIndexOf=getIndexOf;
    _this->base.destroy=destroy;
    _this->base.getItem=getItem;
    _this->base.getLength=getLength;
    _this->base.insert=insert;
    _this->base.pop=pop;
    _this->base.remove=remove;

    *self = &(_this->base);

    return MBox_MBoxError_SUCCESS;
}

static int getLength(
    struct MBox_List * self,
    unsigned int * length
) {
    struct DynamicList * _this = (struct DynamicList *) self;

    *length = _this->length;

    return MBox_MBoxError_SUCCESS;
}

static int addItem(
    struct MBox_List * self,
    struct MBox_MBox * item
) {
    struct DynamicList * _this = (struct DynamicList *) self;
    struct Node * lastNode = _this->root;
    struct Node * newNode = (struct Node *) malloc(sizeof(struct Node));

    while(lastNode->next != _this->root) {
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
    newNode->previous = lastNode;
    newNode->next = _this->root;
    newNode->value = item;
    _this->length++;

    return MBox_MBoxError_SUCCESS;
}

static int getItem(
    struct MBox_List * self,
    int index,
    struct MBox_MBox ** item
) {
    struct DynamicList * _this = (struct DynamicList *) self;
    struct Node * currentNode = index >= 0 ? _this->root->next : _this->root->previous;
    int searchDelta = index >= 0 ? 1 : -1;
    int searchStart = index >= 0 ? 0 : -1;

    for(int searchIndex = searchStart; searchIndex != index; searchIndex+=searchDelta){
        if (searchDelta == 1) {
            currentNode = currentNode->next;
        } else {
            currentNode = currentNode->previous;
        }
        if (currentNode == _this->root) {
            return MBox_ListError_INVALID_INDEX;
        }
    }

    *item = currentNode;

    return MBox_MBoxError_SUCCESS;
}

static int pop(
    struct MBox_List * self,
    int index,
    struct MBox_MBox ** item
) {
    struct DynamicList * _this = (struct DynamicList *) self;
    struct Node * currentNode = index >= 0 ? _this->root->next : _this->root->previous;
    int searchDelta = index >= 0 ? 1 : -1;
    int searchStart = index >= 0 ? 0 : -1;

    for(int searchIndex = searchStart; searchIndex != index; searchIndex+=searchDelta){
        if (searchDelta == 1) {
            currentNode = currentNode->next;
        } else {
            currentNode = currentNode->previous;
        }
        if (currentNode == _this->root) {
            return MBox_ListError_INVALID_INDEX;
        }
    }

    *item = currentNode->value;

    struct Node * previous = currentNode->previous;
    struct Node * next = currentNode->next;
    previous->next = next;
    next->previous = previous;
    free(currentNode);

    return MBox_MBoxError_SUCCESS;
}

static int getIndexOf(
    struct MBox_List * self,
    struct MBox_MBox * item,
    int * index
) {
    
}
