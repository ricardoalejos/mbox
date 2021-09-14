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
    struct MBox_MBox * itemBuffer
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
static int _remove(
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
    _this->base.remove=_remove;

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

    if (newNode == NULL) return MBox_DynamicListError_MALLOC_FAILED;
    if (item->duplicate(item, &(newNode->value)) != MBox_MBoxError_SUCCESS) {
        return MBox_ListError_MBOX_COPY_FAILED;
    }

    while(lastNode->next != _this->root) {
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
    newNode->previous = lastNode;
    newNode->next = _this->root;
    _this->root->previous = newNode;
    _this->length++;

    return MBox_MBoxError_SUCCESS;
}

static int getItem(
    struct MBox_List * self,
    int index,
    struct MBox_MBox * itemBuffer
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

    return itemBuffer->copyContent(itemBuffer, currentNode->value);
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

    if (item != NULL) {
        *item = currentNode->value;
    }

    currentNode->previous->next = currentNode->next;
    currentNode->next->previous = currentNode->previous;
    free(currentNode);
    _this->length--;

    return MBox_MBoxError_SUCCESS;
}

static int getIndexOf(
    struct MBox_List * self,
    struct MBox_MBox * item,
    int * index
) {
    struct DynamicList * _this = (struct DynamicList *) self;
    struct Node * currentNode = _this->root;
    int _index = 0;

    if (_this->length == 0) {
        return MBox_ListError_INVALID_OPERATION_IN_EMPTY_LIST;
    }

    while(currentNode->next != _this->root) {
        currentNode = currentNode->next;
        bool itemsAreEqual = false;
        currentNode->value->isEqual(currentNode->value, item, &itemsAreEqual);
        if (itemsAreEqual) {
            *index = _index;
            break;
        }
        _index++;
    }

    return MBox_MBoxError_SUCCESS;
}

static int _remove(
    struct MBox_List * self,
    struct MBox_MBox * item
) {
    struct DynamicList * _this = (struct DynamicList *) self;
    struct Node * currentNode = _this->root;

    if (_this->length == 0) {
        return MBox_ListError_INVALID_OPERATION_IN_EMPTY_LIST;
    }

    while(currentNode->next != _this->root) {
        currentNode = currentNode->next;
        bool itemsAreEqual = false;
        currentNode->value->isEqual(currentNode->value, item, &itemsAreEqual);
        if (itemsAreEqual) {
            currentNode->previous->next = currentNode->next;
            currentNode->next->previous = currentNode->previous;
            currentNode->value->destroy(&(currentNode->value));
            free(currentNode);
            _this->length--;
            break;
        }
    }

    return MBox_MBoxError_SUCCESS;
}

static int insert(
    struct MBox_List * self,
    unsigned int index,
    struct MBox_MBox * item
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

    currentNode = currentNode->previous;

    struct Node * newNode = (struct Node *) malloc(sizeof(struct Node));
    if (newNode == NULL) return MBox_DynamicListError_MALLOC_FAILED;
    if (item->duplicate(item, &(newNode->value)) != MBox_MBoxError_SUCCESS) {
        return MBox_ListError_MBOX_COPY_FAILED;
    }
    newNode->next = currentNode->next;
    newNode->previous = currentNode;
    currentNode->next = newNode;
    _this->length++;

    return MBox_MBoxError_SUCCESS;
}

static int destroy(
    struct MBox_List ** self
) {
    struct DynamicList * _this = (struct DynamicList *) *self;
    struct Node * lastNode = _this->root->previous;

    while(lastNode->previous != _this->root) {
        struct Node * currentNode = lastNode;
        lastNode = currentNode->previous;
        lastNode->next = currentNode->next;
        currentNode->value->destroy(&(currentNode->value));
        free(currentNode);
        _this->length--;
    }

    free(_this);
    *self = NULL;
    
    return MBox_MBoxError_SUCCESS;
}
