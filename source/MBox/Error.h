#ifndef _MBOX_ERROR_H_
#define _MBOX_ERROR_H_

enum MBox_Error {
    MBox_Error_SUCCESS,
    MBox_Error_SHAPE_MISMATCH,
    MBox_Error_INVALID_SHAPE,
    MBox_Error_CONTENT_DOES_NOT_FIT_IN_MBOX,
    MBox_Error_CONTENT_DOES_NOT_FIT_IN_OUTPUT_BUFFER,
    MBox_Error_INVALID_INDEX,
    MBox_Error_ITEM_NOT_FOUND,
    MBox_Error_MBOX_COPY_FAILED,
    MBox_Error_INVALID_OPERATION_IN_EMPTY_LIST,
    MBox_Error_MALLOC_FAILED,
    MBox_Error_REALLOC_FAILED,
    MBox_CANNOT_CREATE_KEY,
    MBox_Error_KEY_NOT_FOUND,
    MBox_Error_CANNOT_STORE_VALUE_IN_BUFFER
};

#endif