#include "MBox/DynamicDictionary.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
#include <stdlib.h>
#include <string.h>

struct Entry {
    struct MBox_MBox * key;
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
    struct MBox_MBox * key,
    struct MBox_MBox * valueBuffer
);
static int getValueRef(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox ** valueRef
);
static int setValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox * valueBuffer
);
static int addEmptyEntry(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox ** valueRef
);
static int _remove(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key
);
static int hasKey(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    bool * response
);
static int isEmpty(
    struct MBox_Dictionary * self,
    bool * response
);
static int addKeysToList(
    struct MBox_Dictionary * self,
    struct MBox_List * targetList
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
static int update(
    struct MBox_Dictionary * self,
    struct MBox_Dictionary * other
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
    _this->base.getValueRef=getValueRef;
    _this->base.hasKey=hasKey;
    _this->base.isEmpty=isEmpty;
    _this->base.remove=_remove;
    _this->base.reset=reset;
    _this->base.setValue=setValue;
    _this->base.addEmptyEntry=addEmptyEntry;
    _this->base.update=update;

    *self = &(_this->base);

    return MBox_Error_SUCCESS;
}

static int setValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox * valueBuffer
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    struct Entry * currentEntry = _this->root;
    struct Entry * lastEntry = _this->root;

    // Look if key exists. And if it does, update the value.
    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            int feedback = currentEntry->value->copyContent(
                currentEntry->value,
                valueBuffer
            );
            if (feedback != MBox_Error_SUCCESS){
                return MBox_Error_CANNOT_STORE_VALUE_IN_BUFFER;
            } else {
                return MBox_Error_SUCCESS;
            }
        }
        lastEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    // If the key does not exist, then create a new entry
    struct Entry * newEntry = (struct Entry *) malloc(sizeof(struct Entry));
    if (newEntry == NULL)  return MBox_Error_MALLOC_FAILED;
    if (key->duplicate(key, &(newEntry->key)) != MBox_Error_SUCCESS) {
        free(newEntry);
        return MBox_Error_CANNOT_CREATE_KEY;
    }
    int feedback = valueBuffer->duplicate(valueBuffer, &(newEntry->value));
    if (feedback != MBox_Error_SUCCESS){
        newEntry->key->destroy(&(newEntry->key));
        free(newEntry);
        return MBox_Error_CANNOT_STORE_VALUE_IN_BUFFER;
    }
    newEntry->next = NULL;
    if (_this->root == NULL) {
        _this->root = newEntry;
    } else {
        lastEntry->next = newEntry;
    }
    _this->length++;
    return MBox_Error_SUCCESS;
}

static int addEmptyEntry(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox ** valueRef
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    struct Entry * currentEntry = _this->root;
    struct Entry * lastEntry = _this->root;
    *valueRef = NULL;

    // Look if key exists. And if it does, update the value.
    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            int feedback = currentEntry->value->reset(
                currentEntry->value
            );
            *valueRef = currentEntry->value;
            if (feedback != MBox_Error_SUCCESS){
                return MBox_Error_CANNOT_STORE_VALUE_IN_BUFFER;
            } else {
                return MBox_Error_SUCCESS;
            }
        }
        lastEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    // If the key does not exist, then create a new entry
    struct Entry * newEntry = (struct Entry *) malloc(sizeof(struct Entry));
    if (newEntry == NULL)  return MBox_Error_MALLOC_FAILED;
    if (key->duplicate(key, &(newEntry->key)) != MBox_Error_SUCCESS) {
        free(newEntry);
        return MBox_Error_CANNOT_CREATE_KEY;
    }

    int feedback = MBox_createDynamicMBox(&(newEntry->value));
    if (feedback != MBox_Error_SUCCESS){
        newEntry->key->destroy(&(newEntry->key));
        free(newEntry);
        return MBox_Error_CANNOT_STORE_VALUE_IN_BUFFER;
    }
    newEntry->next = NULL;
    if (_this->root == NULL) {
        _this->root = newEntry;
    } else {
        lastEntry->next = newEntry;
    }
    _this->length++;
    *valueRef = newEntry->value;
    return MBox_Error_SUCCESS;
}

static int getValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox * valueBuffer
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            int feedback = valueBuffer->copyContent(
                valueBuffer,
                currentEntry->value
            );
            if (feedback != MBox_Error_SUCCESS){
                return MBox_Error_CANNOT_STORE_VALUE_IN_BUFFER;
            } else {
                return MBox_Error_SUCCESS;
            }
        }
        currentEntry = currentEntry->next;
    }

    return MBox_Error_KEY_NOT_FOUND;
}

static int getValueRef(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox ** valueRef
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;
    *valueRef = NULL;

    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            *valueRef = currentEntry->value;
            return MBox_Error_SUCCESS;
        }
        currentEntry = currentEntry->next;
    }
    return MBox_Error_KEY_NOT_FOUND;
}

static int _remove(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    if (_this->root == NULL) {
        return MBox_Error_KEY_NOT_FOUND;
    }

    struct Entry * previousEntry = NULL;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            currentEntry->value->destroy(&(currentEntry->value));
            if (previousEntry != NULL) {
                previousEntry->next = currentEntry->next;
            } else {
                _this->root = currentEntry->next;
            }
            currentEntry->key->destroy(&(currentEntry->key));
            free(currentEntry);
            _this->length--;
            return MBox_Error_SUCCESS;
        }
        previousEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    return MBox_Error_KEY_NOT_FOUND;
}

static int hasKey(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    bool * response
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            *response = true;
            return MBox_Error_SUCCESS;
        }
        currentEntry = currentEntry->next;
    }

    *response = false;

    return MBox_Error_SUCCESS;
}

static int addKeysToList(
    struct MBox_Dictionary * self,
    struct MBox_List * targetList
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        targetList->addItem(targetList, currentEntry->key);
        currentEntry = currentEntry->next;
    }

    return MBox_Error_SUCCESS;
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

    return MBox_Error_SUCCESS;
}

static int getLength(
    struct MBox_Dictionary * self,
    unsigned int * length
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    *length = _this->length;

    return MBox_Error_SUCCESS;
}

static int reset(
    struct MBox_Dictionary * self
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    if (_this->root == NULL){
        return MBox_Error_SUCCESS;
    }

    struct Entry * currentEntry = _this->root;
    struct Entry * nextEntry = currentEntry->next;

    while (currentEntry != NULL) {
        nextEntry = currentEntry->next;
        currentEntry->value->destroy(&(currentEntry->value));
        currentEntry->key->destroy(&(currentEntry->key));
        free(currentEntry);
        currentEntry = nextEntry;
    }

    _this->length = 0;
    _this->root = NULL;

    return MBox_Error_SUCCESS;
}

static int destroy(
    struct MBox_Dictionary ** self
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) *self;

    _this->base.reset(&(_this->base));
    free(_this);
    *self = NULL;

    return MBox_Error_SUCCESS;
}

static int update(
    struct MBox_Dictionary * self,
    struct MBox_Dictionary * other
) {
    if (self == other) {
        return MBox_Error_CANNOT_UPDATE_A_DICTIONARY_WITH_ITSELF;
    }

    struct MBox_List * otherKeyList;
    int feedback = MBox_createDynamicList(&otherKeyList);

    if (feedback != MBox_Error_SUCCESS) return feedback;

    other->addKeysToList(other, otherKeyList);

    unsigned int numberOfOtherKeys;

    otherKeyList->getLength(otherKeyList, &numberOfOtherKeys);

    unsigned int currentKeyIndex;

    for (currentKeyIndex = 0; currentKeyIndex < numberOfOtherKeys; currentKeyIndex++) {
        struct MBox_MBox * currentKey;
        otherKeyList->getItemRef(otherKeyList, currentKeyIndex, &currentKey);
        struct MBox_MBox * newValue;
        other->getValueRef(other, currentKey, &newValue);
        self->setValue(self, currentKey, newValue);
    }

    otherKeyList->destroy(&otherKeyList);

    return MBox_Error_SUCCESS;
}
