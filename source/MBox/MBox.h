#ifndef _MBOX_MBOX_H_
#define _MBOX_MBOX_H_

#include <stdint.h>
#include <stdbool.h>

enum MBox_Shape {
    MBox_Shape_UNSIGNED_64B_INTEGER,
    MBox_Shape_SIGNED_64B_INTEGER,
    MBox_Shape_DOUBLE,
    MBox_Shape_STRING,
    MBox_Shape_BOOLEAN,
    MBox_Shape_REFERENCE,
    MBox_Shape_CUSTOM,
    MBox_Shape_NULL,
    MBox_Shape_NUMBER_OF_SHAPES
};

enum MBox_MBoxError {
    MBox_MBoxError_SUCCESS,
    MBox_MBoxError_INVALID_SHAPE,
    MBox_MBoxError_CONTENT_DOES_NOT_FIT_IN_MBOX,
    MBox_MBoxError_CONTENT_DOES_NOT_FIT_IN_OUTPUT_BUFFER,
    MBox_MBoxError_REQUEST_DOES_NOT_MATCH_MBOX_SHAPE,
    MBox_MBoxError_ERROR_BASE
};

struct MBox_MBox {
    int (*getShape)(
        struct MBox_MBox * self,
        enum MBox_Shape * shape
    );
    int (*getSize)(
        struct MBox_MBox * self,
        unsigned int * size
    );

    int (*storeUnsigned64BInteger)(
        struct MBox_MBox * self,
        uint64_t value
    );
    int (*readUnsigned64BInteger)(
        struct MBox_MBox * self,
        uint64_t * value
    );

    int (*storeSigned64BInteger)(
        struct MBox_MBox * self,
        int64_t value
    );
    int (*readSigned64BInteger)(
        struct MBox_MBox * self,
        int64_t * value
    );

    int (*storeDouble)(
        struct MBox_MBox * self,
        double value
    );
    int (*readDouble)(
        struct MBox_MBox * self,
        double * value
    );

    int (*storeString)(
        struct MBox_MBox * self,
        char * valueBuffer
    );
    int (*readString)(
        struct MBox_MBox * self,
        char * valueBuffer,
        unsigned int valueBufferSize
    );

    int (*storeBoolean)(
        struct MBox_MBox * self,
        bool value
    );
    int (*readBoolean)(
        struct MBox_MBox * self,
        bool * value
    );

    int (*storeReference)(
        struct MBox_MBox * self,
        void * value
    );
    int (*readReference)(
        struct MBox_MBox * self,
        void ** value
    );

    int (*isEmpty)(
        struct MBox_MBox * self,
        bool * mBoxIsEmpty
    );

    int (*storeCustomContent)(
        struct MBox_MBox * self,
        void * content,
        unsigned int contentSize
    );
    int (*readCustomContent)(
        struct MBox_MBox * self,
        void * outputBuffer,
        unsigned int outputBufferSize
    );

    int (*reset)(
        struct MBox_MBox * self
    );

    int (*destroy)(
        struct MBox_MBox ** self
    );
};

#endif
