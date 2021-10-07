#include "MBox/DynamicMBox.h"
#include "MBox/List.h"
#include "MBox/Dictionary.h"
#include "MBox/Error.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

struct DynamicMBox {
    struct MBox_MBox base;
    enum MBox_Shape shape;
    unsigned int size;
    void * content;
};

static int getShape(
    struct MBox_MBox * self,
    enum MBox_Shape * shape
);
static int getSize(
    struct MBox_MBox * self,
    unsigned int * size
);

static int _setContentSize(
    struct DynamicMBox * self,
    unsigned int size
);

static int storeUnsigned64BInteger(
    struct MBox_MBox * self,
    uint64_t value
);
static int readUnsigned64BInteger(
    struct MBox_MBox * self,
    uint64_t * value
);

static int storeSigned64BInteger(
    struct MBox_MBox * self,
    int64_t value
);
static int readSigned64BInteger(
    struct MBox_MBox * self,
    int64_t * value
);

static int storeDouble(
    struct MBox_MBox * self,
    double value
);
static int readDouble(
    struct MBox_MBox * self,
    double * value
);

static int storeBoolean(
    struct MBox_MBox * self,
    bool value
);
static int readBoolean(
    struct MBox_MBox * self,
    bool * value
);

static int storeReference(
    struct MBox_MBox * self,
    void * value
);
static int readReference(
    struct MBox_MBox * self,
    void ** value
);

static int storeString(
    struct MBox_MBox * self,
    const char * format,
    ...
);
static int readString(
    struct MBox_MBox * self,
    char * valueBuffer,
    unsigned int valueBufferSize
);
static int cloneString(
    struct MBox_MBox * self,
    char ** clonedString
);

static int isEmpty(
    struct MBox_MBox * self,
    bool * mBoxIsEmpty
);

static int storeCustomContent(
    struct MBox_MBox * self,
    void * content,
    unsigned int contentSize
);
static int readCustomContent(
    struct MBox_MBox * self,
    void * outputBuffer,
    unsigned int outputBufferSize
);

static int reset(
    struct MBox_MBox * self
);

static int destroy(
    struct MBox_MBox ** self
);

static int duplicate(
    struct MBox_MBox * self,
    struct MBox_MBox ** newBox
);

static int copyContent(
    struct MBox_MBox * self,
    struct MBox_MBox * destination
);

static int isEqual(
    struct MBox_MBox * self,
    struct MBox_MBox * another,
    bool * answer
);

static int storeListReference(
    struct MBox_MBox * self,
    struct MBox_List * value
);
static int readListReference(
    struct MBox_MBox * self,
    struct MBox_List ** value
);

static int storeDictionaryReference(
    struct MBox_MBox * self,
    struct MBox_Dictionary * value
);
static int readDictionaryReference(
    struct MBox_MBox * self,
    struct MBox_Dictionary ** value
);


int MBox_createDynamicMBox(struct MBox_MBox ** self) {

    struct DynamicMBox * _this = (struct DynamicMBox *) malloc(
        sizeof(struct DynamicMBox)
    );

    if (_this == NULL) {
        return MBox_Error_MALLOC_FAILED;
    }

    _this->shape = MBox_Shape_NULL;
    _this->size = 0;
    _this->content = NULL;

    _this->base.getSize=getSize;
    _this->base.getShape=getShape;
    _this->base.destroy=destroy;
    _this->base.reset=reset;
    _this->base.isEmpty=isEmpty;
    _this->base.readBoolean=readBoolean;
    _this->base.storeBoolean=storeBoolean;
    _this->base.readUnsigned64BInteger=readUnsigned64BInteger;
    _this->base.storeUnsigned64BInteger=storeUnsigned64BInteger;
    _this->base.readSigned64BInteger=readSigned64BInteger;
    _this->base.storeSigned64BInteger=storeSigned64BInteger;
    _this->base.readDouble=readDouble;
    _this->base.storeDouble=storeDouble;
    _this->base.readString=readString;
    _this->base.storeString=storeString;
    _this->base.readReference=readReference;
    _this->base.storeReference=storeReference;
    _this->base.readCustomContent=readCustomContent;
    _this->base.storeCustomContent=storeCustomContent;
    _this->base.duplicate=duplicate;
    _this->base.isEqual=isEqual;
    _this->base.copyContent=copyContent;
    _this->base.storeListReference=storeListReference;
    _this->base.readListReference=readListReference;
    _this->base.storeDictionaryReference=storeDictionaryReference;
    _this->base.readDictionaryReference=readDictionaryReference;
    _this->base.cloneString=cloneString;

    *self = &(_this->base);

    return MBox_Error_SUCCESS;
}

static int getShape(
    struct MBox_MBox * self,
    enum MBox_Shape * shape
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    *shape = _this->shape;

    return MBox_Error_SUCCESS;
}

static int getSize(
    struct MBox_MBox * self,
    unsigned int * size
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    *size = _this->size;

    return MBox_Error_SUCCESS;
}

static int _setContentSize(
    struct DynamicMBox * self,
    unsigned int size
) {
    void * newContentBuffer = realloc(self->content, size);
    if (newContentBuffer == NULL) {
        return MBox_Error_REALLOC_FAILED;
    }
    self->content = newContentBuffer;
    self->size = size;

    return MBox_Error_SUCCESS;
}

static int storeUnsigned64BInteger(
    struct MBox_MBox * self,
    uint64_t value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    int resizeResult = _setContentSize(_this, sizeof(uint64_t));
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    *((uint64_t *) _this->content) = value;
    _this->shape = MBox_Shape_UNSIGNED_64B_INTEGER;
    _this->size = sizeof(uint64_t);

    return MBox_Error_SUCCESS;
}

static int readUnsigned64BInteger(
    struct MBox_MBox * self,
    uint64_t * value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_UNSIGNED_64B_INTEGER) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    *value = *((uint64_t *) _this->content);

    return MBox_Error_SUCCESS;
}

static int storeSigned64BInteger(
    struct MBox_MBox * self,
    int64_t value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    int resizeResult = _setContentSize(_this, sizeof(int64_t));
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    *((int64_t *) _this->content) = value;
    _this->shape = MBox_Shape_SIGNED_64B_INTEGER;
    _this->size = sizeof(int64_t);

    return MBox_Error_SUCCESS;
}

static int readSigned64BInteger(
    struct MBox_MBox * self,
    int64_t * value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_SIGNED_64B_INTEGER) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    *value = *((int64_t *) _this->content);

    return MBox_Error_SUCCESS;
}

static int storeDouble(
    struct MBox_MBox * self,
    double value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    int resizeResult = _setContentSize(_this, sizeof(double));
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    *((double *) _this->content) = value;
    _this->shape = MBox_Shape_DOUBLE;
    _this->size = sizeof(double);

    return MBox_Error_SUCCESS;
}

static int readDouble(
    struct MBox_MBox * self,
    double * value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_DOUBLE) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    *value = *((double *) _this->content);

    return MBox_Error_SUCCESS;
}

static int storeBoolean(
    struct MBox_MBox * self,
    bool value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    int resizeResult = _setContentSize(_this, sizeof(bool));
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    memcpy(_this->content, &value, sizeof(bool));
    _this->shape = MBox_Shape_BOOLEAN;
    _this->size = sizeof(bool);

    return MBox_Error_SUCCESS;
}

static int readBoolean(
    struct MBox_MBox * self,
    bool * value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_BOOLEAN) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    memcpy(value, _this->content, _this->size);

    return MBox_Error_SUCCESS;
}

static int storeReference(
    struct MBox_MBox * self,
    void * value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    int resizeResult = _setContentSize(_this, sizeof(void *));
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    memcpy(_this->content, &(value), sizeof(void *));
    _this->shape = MBox_Shape_REFERENCE;
    _this->size = sizeof(void *);

    return MBox_Error_SUCCESS;
}

static int readReference(
    struct MBox_MBox * self,
    void ** value
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_REFERENCE) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    memcpy(value, _this->content, sizeof(void *));

    return MBox_Error_SUCCESS;
}

static int storeString(
    struct MBox_MBox * self,
    const char * format,
    ...
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    va_list args;
    va_start (args, format);
    unsigned int stringLength = vsnprintf (NULL,0, format, args) + 1;
    va_end (args);

    //stringLength = strlen(valueBuffer) + 1;
    stringLength = stringLength > 0 ? stringLength : 1;

    int resizeResult = _setContentSize(_this, stringLength);
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    //memcpy(_this->content, valueBuffer, stringLength);
    va_start(args, format);
    vsnprintf((char*) _this->content, stringLength, format, args);
    va_end (args);
    ((char *)_this->content)[stringLength-1] ='\0';

    _this->shape = MBox_Shape_STRING;
    _this->size = stringLength;

    return MBox_Error_SUCCESS;
}

static int readString(
    struct MBox_MBox * self,
    char * valueBuffer,
    unsigned int valueBufferSize
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_STRING) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    if (valueBufferSize < _this->size) {
        return MBox_Error_CONTENT_DOES_NOT_FIT_IN_OUTPUT_BUFFER;
    }

    strncpy(valueBuffer, _this->content, _this->size);

    return MBox_Error_SUCCESS;
}

static int cloneString(
    struct MBox_MBox * self,
    char ** clonedString
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;
    *clonedString = NULL;

    if (_this->shape != MBox_Shape_STRING) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    char * newString = (char*) malloc(_this->size);
    if (newString == NULL) return MBox_Error_MALLOC_FAILED;
    strncpy(newString, _this->content, _this->size);
    *clonedString = newString;

    return MBox_Error_SUCCESS;
}

static int isEmpty(
    struct MBox_MBox * self,
    bool * mBoxIsEmpty
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;
    _this->size = _this->size == 0 ? true : false;
    return MBox_Error_SUCCESS;
}

static int storeCustomContent(
    struct MBox_MBox * self,
    void * content,
    unsigned int contentSize
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    int resizeResult = _setContentSize(_this, contentSize);
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    memcpy(_this->content, content, contentSize);
    _this->shape = MBox_Shape_CUSTOM;
    _this->size = contentSize;

    return MBox_Error_SUCCESS;
}

static int readCustomContent(
    struct MBox_MBox * self,
    void * outputBuffer,
    unsigned int outputBufferSize
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_CUSTOM) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    if (outputBufferSize < _this->size) {
        return MBox_Error_CONTENT_DOES_NOT_FIT_IN_OUTPUT_BUFFER;
    }

    memcpy(outputBuffer, _this->content, _this->size);

    return MBox_Error_SUCCESS;
}

static int reset(
    struct MBox_MBox * self
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->content != NULL) {
        memset(_this->content, 0, _this->size);
        free(_this->content);
        _this->content = NULL;
    }

    _this->size = 0;
    _this->shape = MBox_Shape_NULL;

    return MBox_Error_SUCCESS;
}

static int destroy(
    struct MBox_MBox ** self
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) *self;
    _this->base.reset(&(_this->base));
    free(_this);
    *self = NULL;
    return MBox_Error_SUCCESS;
}

static int duplicate (
    struct MBox_MBox * self,
    struct MBox_MBox ** newBox
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;
    struct DynamicMBox * _newBox;
    int feedback;

    feedback = MBox_createDynamicMBox(newBox);

    if (feedback != MBox_Error_SUCCESS) return feedback;

    _newBox = (struct DynamicMBox *)*newBox;
    _newBox->shape = _this->shape;
    _newBox->size = _this->size;
    // Protect memcpy from accessing NULL pointers.
    if (_this->shape != MBox_Shape_NULL) {
        _newBox->content = malloc(_this->size);
        memcpy(_newBox->content, _this->content, _this->size);
    }

    return MBox_Error_SUCCESS;
}

static int isEqual(
    struct MBox_MBox * self,
    struct MBox_MBox * another,
    bool * answer
) {
    struct DynamicMBox * _this = (struct DynamicMBox *) self;
    struct DynamicMBox * _another = (struct DynamicMBox *) another;

    *answer = false;

    if (_this->shape != _another->shape) {
        return MBox_Error_SUCCESS;
    }

    if (_this->size != _another->size) {
        return MBox_Error_SUCCESS;
    }

    if(memcmp(_this->content, _another->content, _this->size) != 0) {
        return MBox_Error_SUCCESS;
    }

    *answer = true;
    return MBox_Error_SUCCESS;
}

static int copyContent(
    struct MBox_MBox * self,
    struct MBox_MBox * source
) {
    struct DynamicMBox * _destinaton = (struct DynamicMBox *) self;
    struct DynamicMBox * _source = (struct DynamicMBox *) source;

    // NULL values cannot be copied because memcpy would receive a NULL
    // pointer for its source.
    if (_source->shape == MBox_Shape_NULL) {
        self->reset(self);
        return MBox_Error_SUCCESS;
    }

    void * newContent = realloc(_destinaton->content, _source->size);
    if (newContent == NULL) {
        return MBox_Error_REALLOC_FAILED;
    }
    _destinaton->content = newContent;
    memcpy(_destinaton->content, _source->content, _source->size);
    _destinaton->size = _source->size;
    _destinaton->shape = _source->shape;

    return MBox_Error_SUCCESS;
}

static int storeListReference(
    struct MBox_MBox * self,
    struct MBox_List * value
){
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    int resizeResult = _setContentSize(_this, sizeof(struct DynamicList *));
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    memcpy(_this->content, &(value), sizeof(struct DynamicList *));
    _this->shape = MBox_Shape_LIST_REFERENCE;
    _this->size = sizeof(struct DynamicList *);

    return MBox_Error_SUCCESS;
}

static int readListReference(
    struct MBox_MBox * self,
    struct MBox_List ** value
){
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_LIST_REFERENCE) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    memcpy(value, _this->content, sizeof(struct DynamicList *));

    return MBox_Error_SUCCESS;
}

static int storeDictionaryReference(
    struct MBox_MBox * self,
    struct MBox_Dictionary * value
){
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    int resizeResult = _setContentSize(_this, sizeof(struct DynamicMBox *));
    if (resizeResult != MBox_Error_SUCCESS) {
        return resizeResult;
    }

    memcpy(_this->content, &(value), sizeof(struct DynamicMBox *));
    _this->shape = MBox_Shape_DICTIONARY_REFERENCE;
    _this->size = sizeof(void *);

    return MBox_Error_SUCCESS;
}

static int readDictionaryReference(
    struct MBox_MBox * self,
    struct MBox_Dictionary ** value
){
    struct DynamicMBox * _this = (struct DynamicMBox *) self;

    if (_this->shape != MBox_Shape_DICTIONARY_REFERENCE) {
        return MBox_Error_SHAPE_MISMATCH;
    }

    memcpy(value, _this->content, sizeof(struct DynamicMBox *));

    return MBox_Error_SUCCESS;
}
