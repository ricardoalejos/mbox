#include "MBox/DynamicDictionary.h"
#include <stdlib.h>
#include <string.h>

struct Entry {
    char * key;
    struct MBox_MBox * value;
    struct Entry * next;
};

struct DynamicDictionary {
    struct MBox_Dictionary base;
    struct Entry * root;
    unsigned int length;
};

static int getValue(
    struct MBox_Dictionary * self,
    char * key,
    struct MBox_MBox * itemBuffer
);
static int setValue(
    struct MBox_Dictionary * self,
    char * key,
    struct MBox_MBox * itemBuffer
);
static int _remove(
    struct MBox_Dictionary * self,
    char * key
);
static int hasKey(
    struct MBox_Dictionary * self,
    char * key,
    bool * response
);
static int isEmpty(
    struct MBox_Dictionary * self,
    bool * response
);
static int addKeysToList(
    struct MBox_Dictionary * self,
    struct MBox_List * targetList,
    struct MBox_MBox * keyBuffer
);
static int getLength(
    struct MBox_Dictionary * self,
    unsigned int * length
);
static int reset(
    struct MBox_Dictionary * self
);
static int destroy(
    struct MBox_Dictionary ** self
);

int MBox_createDynamicDictionary(struct MBox_Dictionary ** self){
    struct DynamicDictionary * _this = (struct DynamicDictionary *) malloc(
        sizeof(struct DynamicDictionary)
    );

    _this->root = NULL;
    _this->length=0;
    _this->base.addKeysToList=addKeysToList;
    _this->base.destroy=destroy;
    _this->base.getLength=getLength;
    _this->base.getValue=getValue;
    _this->base.hasKey=hasKey;
    _this->base.isEmpty=isEmpty;
    _this->base.remove=_remove;
    _this->base.reset=reset;
    _this->base.setValue=setValue;

    *self = &(_this->base);

    return MBox_DictionaryError_SUCCESS;
}

static int setValue(
    struct MBox_Dictionary * self,
    char * key,
    struct MBox_MBox * itemBuffer
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    struct Entry * currentEntry = _this->root;
    struct Entry * lastEntry = _this->root;

    // Look if key exists. And if it does, update the value.
    while(currentEntry != NULL) {
        if (strcmp(currentEntry->key, key) == 0) {
            int feedback = currentEntry->value->copyContent(
                currentEntry->value,
                itemBuffer
            );
            if (feedback != MBox_MBoxError_SUCCESS){
                return MBox_DictionaryError_CANNOT_STORE_VALUE_IN_BUFFER;
            } else {
                return MBox_DictionaryError_SUCCESS;
            }
        }
        lastEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    // If the key does not exist, then create a new entry
    struct Entry * newEntry = (struct Entry *) malloc(sizeof(struct Entry));
    if (newEntry == NULL)  return MBox_DynamicDictionaryError_MALLOC_FAILED;
    int keySize = strlen(key);
    newEntry->key = (char *) malloc(keySize + 1);
    if (newEntry->key == NULL){
        free(newEntry);
        return MBox_DynamicDictionaryError_MALLOC_FAILED;
    }
    strncpy(newEntry->key, key, keySize + 1);
    int feedback = itemBuffer->duplicate(itemBuffer, &(newEntry->value));
    if (feedback != MBox_MBoxError_SUCCESS){
        free(newEntry->key);
        free(newEntry);
        return MBox_DictionaryError_CANNOT_STORE_VALUE_IN_BUFFER;
    }
    newEntry->next = NULL;
    if (_this->root == NULL) {
        _this->root = newEntry;
    } else {
        lastEntry->next = newEntry;
    }
    _this->length++;
    return MBox_DictionaryError_SUCCESS;
}

static int getValue(
    struct MBox_Dictionary * self,
    char * key,
    struct MBox_MBox * itemBuffer
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        if (strcmp(currentEntry->key, key) == 0) {
            int feedback = itemBuffer->copyContent(
                itemBuffer,
                currentEntry->value
            );
            if (feedback != MBox_MBoxError_SUCCESS){
                return MBox_DictionaryError_CANNOT_STORE_VALUE_IN_BUFFER;
            } else {
                return MBox_DictionaryError_SUCCESS;
            }
        }
        currentEntry = currentEntry->next;
    }

    return MBox_DictionaryError_KEY_NOT_FOUND;
}

static int _remove(
    struct MBox_Dictionary * self,
    char * key
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    if (_this->root == NULL) {
        return MBox_DictionaryError_KEY_NOT_FOUND;
    }

    struct Entry * previousEntry = NULL;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        if (strcmp(currentEntry->key, key) == 0) {
            currentEntry->value->destroy(&(currentEntry->value));
            if (previousEntry != NULL) {
                previousEntry->next = currentEntry->next;
            } else {
                _this->root = currentEntry->next;
            }
            free(currentEntry->key);
            free(currentEntry);
            _this->length--;
            return MBox_DictionaryError_SUCCESS;
        }
        previousEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    return MBox_DictionaryError_KEY_NOT_FOUND;
}

static int hasKey(
    struct MBox_Dictionary * self,
    char * key,
    bool * response
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        if (strcmp(currentEntry->key, key) == 0) {
            *response = true;
            return MBox_MBoxError_SUCCESS;
        }
        currentEntry = currentEntry->next;
    }

    *response = false;

    return MBox_MBoxError_SUCCESS;
}

static int addKeysToList(
    struct MBox_Dictionary * self,
    struct MBox_List * targetList,
    struct MBox_MBox * keyBuffer
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        keyBuffer->storeString(keyBuffer, currentEntry->key);
        targetList->addItem(targetList, keyBuffer);
        currentEntry = currentEntry->next;
    }

    return MBox_MBoxError_SUCCESS;
}

static int isEmpty(
    struct MBox_Dictionary * self,
    bool * response
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    
    if (_this->root == NULL){
        *response = true;
    } else {
        *response = false;
    }

    return MBox_MBoxError_SUCCESS;
}

static int getLength(
    struct MBox_Dictionary * self,
    unsigned int * length
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    *length = _this->length;

    return MBox_DictionaryError_SUCCESS;
}

static int reset(
    struct MBox_Dictionary * self
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    if (_this->root == NULL){
        return MBox_DictionaryError_SUCCESS;
    }

    struct Entry * currentEntry = _this->root;
    struct Entry * nextEntry = currentEntry->next;

    while (currentEntry != NULL) {
        nextEntry = currentEntry->next;
        currentEntry->value->destroy(&(currentEntry->value));
        free(currentEntry->key);
        free(currentEntry);
        currentEntry = nextEntry;
    }

    _this->length = 0;
    _this->root = NULL;

    return MBox_DictionaryError_SUCCESS;
}

static int destroy(
    struct MBox_Dictionary ** self
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) *self;

    _this->base.reset(&(_this->base));
    free(_this);
    *self = NULL;

    return MBox_DictionaryError_SUCCESS;
}
