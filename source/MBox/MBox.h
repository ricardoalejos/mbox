#ifndef _MBOX_MBOX_H_
#define _MBOX_MBOX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "MBox/Error.h"

enum MBox_Shape {
    MBox_Shape_UNSIGNED_64B_INTEGER,
    MBox_Shape_SIGNED_64B_INTEGER,
    MBox_Shape_DOUBLE,
    MBox_Shape_STRING,
    MBox_Shape_BOOLEAN,
    MBox_Shape_REFERENCE,
    MBox_Shape_LIST_REFERENCE,
    MBox_Shape_DICTIONARY_REFERENCE,
    MBox_Shape_CUSTOM,
    MBox_Shape_NULL,
    MBox_Shape_NUMBER_OF_SHAPES
};

struct MBox_List;
struct MBox_Dictionary;

struct MBox_MBox {

    /**
     * @brief Gets what type of the object (a.k.a. "Shape") that resides inside 
     * the Memory Box. If there is no object inside the box, then the output 
     * will be MBox_Shape_NULL.
     * 
     * @param[in] self The MBox object.
     * 
     * @param[out] shape The type (Shape) of the object within the Box.
     * 
     * @return int MBox_Error_SUCCESS if the operation is successful.
     * Else it will be a member of the enumeration MBox_MBoxError or other 
     * implementation- specific errors based on MBox_MBoxError_ERROR_BASE.
     */
    int (*getShape)(
        struct MBox_MBox * self,
        enum MBox_Shape * shape
    );

    /**
     * @brief Gets the size of the content of the Memory Box in bytes. This
     * is particularly useful for allocating a buffer of the right size to
     * extract the data from the Box.
     * 
     * @param[in] self The MBox object.
     * 
     * @param[out] size The size of the object within the Box (in bytes).
     * 
     * @return int MBox_Error_SUCCESS if the operation is successful.
     * Else it will be a member of the enumeration MBox_MBoxError or other 
     * implementation- specific errors based on MBox_MBoxError_ERROR_BASE.
     */
    int (*getSize)(
        struct MBox_MBox * self,
        unsigned int * size
    );

    /**
     * @brief Sets "answer" to "true" if the content of this Box is the same as
     * the content of the box "another". Equality here means that the data in
     * the box matches in size, shape, and the content itself.
     * 
     * @param[in] self The MBox object.
     * 
     * @param[out] answer "true" if the content of this box is the same as the
     * one in the "another" box. Else, it is "false".
     * 
     * @return int MBox_Error_SUCCESS if the operation is successful.
     * Else it will be a member of the enumeration MBox_MBoxError or other 
     * implementation- specific errors based on MBox_MBoxError_ERROR_BASE.
     */
    int (*isEqual)(
        struct MBox_MBox * self,
        struct MBox_MBox * another,
        bool * answer
    );

    /**
     * @brief Stores an unsinged 64-bit integer into the Box. Also, it removes
     * any other data that was previously stored in the Box.
     * 
     * @param[in] self The MBox object.
     * 
     * @param[in] value An "uint64_t" integer to store in the box.
     * 
     * @return int MBox_Error_SUCCESS if the operation is successful.
     * Else it will be a member of the enumeration MBox_MBoxError or other 
     * implementation- specific errors based on MBox_MBoxError_ERROR_BASE.
     */
    int (*storeUnsigned64BInteger)(
        struct MBox_MBox * self,
        uint64_t value
    );

    /**
     * @brief Retrieves an unsinged 64-bit integer from the Box. If the box was
     * storing any other type of data, then this function will fail with the
     * error code MBox_Error_CONTENT_DOES_NOT_FIT_IN_MBOX.
     * 
     * @param[in] self The MBox object.
     * 
     * @param[in] value A buffer to store a copy of the "uint64_t" integer 
     * contained in the box. The box will continue to have its own copy of
     * such data.
     * 
     * @return int MBox_Error_SUCCESS if the operation is successful.
     * Else it will be a member of the enumeration MBox_MBoxError or other 
     * implementation- specific errors based on MBox_MBoxError_ERROR_BASE.
     */
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
        const char * format,
        ...
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

    int (*storeListReference)(
        struct MBox_MBox * self,
        struct MBox_List * value
    );
    int (*readListReference)(
        struct MBox_MBox * self,
        struct MBox_List ** value
    );

    int (*storeDictionaryReference)(
        struct MBox_MBox * self,
        struct MBox_Dictionary * value
    );
    int (*readDictionaryReference)(
        struct MBox_MBox * self,
        struct MBox_Dictionary ** value
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
    int (*duplicate)(
        struct MBox_MBox * self,
        struct MBox_MBox ** newBox
    );
    int (*copyContent)(
        struct MBox_MBox * self,
        struct MBox_MBox * source
    );

    // Quick getters: The "seeing" interface
    void * (*seeContent)(struct MBox_MBox * self);
    unsigned int (*getSize2)(struct MBox_MBox * self);
    enum MBox_Shape (*getShape2)(struct MBox_MBox * self);

    // Short-hand
    uint64_t*(*readUInt64)(struct MBox_MBox * self);
    uint64_t*(*writeUInt64)(struct MBox_MBox * self);
    int64_t*(*readInt64)(struct MBox_MBox * self);
    int64_t*(*writeInt64)(struct MBox_MBox * self);
    bool*(*readBool)(struct MBox_MBox * self);
    bool*(*writeBool)(struct MBox_MBox * self);
    char*(*readStr)(struct MBox_MBox * self);
    unsigned int (*writeStr)(struct MBox_MBox * self, const char * format, ...);
    void**(*readRef)(struct MBox_MBox * self);
    void**(*writeRef)(struct MBox_MBox * self);
    struct MBox_List**(*readListRef)(struct MBox_MBox * self);
    struct MBox_List**(*writeListRef)(struct MBox_MBox * self);
    struct MBox_Dictionary**(*readDictRef)(struct MBox_MBox * self);
    struct MBox_Dictionary**(*writeDictRef)(struct MBox_MBox * self);
    struct MBox_MBox *(*clone)(struct MBox_MBox * self);
    int (*copyFrom)(struct MBox_MBox * self, struct MBox_MBox * source);
    int (*copyTo)(struct MBox_MBox * self, struct MBox_MBox * destination);
};

#ifdef __cplusplus
} // Extern "C"
#endif

#endif
