#include "MBox/DynamicDictionary.h"
#include "MBox/DynamicMBox.h"
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
    enum MBox_Error lastError;
};

static int getValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox * itemBuffer
);
static int setValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox * itemBuffer
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

static struct MBox_MBox * readValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key
);

static struct MBox_MBox * addValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key
);

static unsigned int getLength2(
    struct MBox_Dictionary * self
);
static struct MBox_MBox * seeValueWithStringKey(
    struct MBox_Dictionary * self,
    char * stringKey
);

static bool isEmpty2(struct MBox_Dictionary * self);

static bool hasKey2(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key
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
    _this->base.getLength2=getLength2;
    _this->base.readValue=readValue;
    _this->base.addValue=addValue;
    _this->base.seeValueWithStringKey=seeValueWithStringKey;
    _this->base.isEmpty2=isEmpty2;
    _this->base.hasKey2=hasKey2;

    *self = &(_this->base);

    return MBox_Error_SUCCESS;
}

static int setValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox * itemBuffer
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
                itemBuffer
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
    int feedback = itemBuffer->duplicate(itemBuffer, &(newEntry->value));
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

static int getValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key,
    struct MBox_MBox * itemBuffer
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            int feedback = itemBuffer->copyContent(
                itemBuffer,
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

static bool hasKey2(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;
    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            return true;
        }
        currentEntry = currentEntry->next;
    }
    return false;
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


static bool isEmpty2(struct MBox_Dictionary * self) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    return _this->root == NULL;
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

static struct MBox_MBox * readValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key
){
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            return currentEntry->value;
        }
        currentEntry = currentEntry->next;
    }
    _this->lastError = MBox_Error_KEY_NOT_FOUND;
    return NULL;
}


static unsigned int getLength2(
    struct MBox_Dictionary * self
){
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    return _this->length;
}

static struct MBox_MBox * seeValueWithStringKey(
    struct MBox_Dictionary * self,
    char * stringKey
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;
    struct Entry * currentEntry = _this->root;

    while(currentEntry != NULL) {
        struct MBox_MBox * key = currentEntry->key;
        bool keyMatches;
        enum MBox_Shape keyShape;
        key->getShape(key, &keyShape);
        if (keyShape != MBox_Shape_STRING) return NULL;
        keyMatches = strncmp(
            stringKey, key->seeContent(key), key->getSize2(key)) == 0;
        if (keyMatches) return currentEntry->value;
        currentEntry = currentEntry->next;
    }

    return NULL;
}


static struct MBox_MBox * addValue(
    struct MBox_Dictionary * self,
    struct MBox_MBox * key
) {
    struct DynamicDictionary * _this = (struct DynamicDictionary *) self;

    struct Entry * currentEntry = _this->root;
    struct Entry * lastEntry = _this->root;

    // Look if key exists. And if it does, update the value.
    while(currentEntry != NULL) {
        bool keyMatches;
        currentEntry->key->isEqual(currentEntry->key, key, &keyMatches);
        if (keyMatches) {
            return currentEntry->value;
        }
        lastEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    // If the key does not exist, then create a new entry
    struct Entry * newEntry = (struct Entry *) malloc(sizeof(struct Entry));
    if (newEntry == NULL)  {
        _this->lastError = MBox_Error_MALLOC_FAILED;
        return NULL;
    }
    if (key->duplicate(key, &(newEntry->key)) != MBox_Error_SUCCESS) {
        free(newEntry);
        _this->lastError = MBox_Error_CANNOT_CREATE_KEY;
        return NULL;
    }
    int feedback =  MBox_createDynamicMBox(&(newEntry->value));
    if (feedback != MBox_Error_SUCCESS){
        newEntry->key->destroy(&(newEntry->key));
        free(newEntry);
        _this->lastError = feedback;
        return NULL;
    }
    newEntry->next = NULL;
    if (_this->root == NULL) {
        _this->root = newEntry;
    } else {
        lastEntry->next = newEntry;
    }
    _this->length++;
    return newEntry->value;
}

