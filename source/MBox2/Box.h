#ifndef _MBOX_BOX_H_
#define _MBOX_BOX_H_

#include "MBox2/MBox.h"
#include <stdarg.h>

struct MBox_Box {
    enum MBox_Error (*getLastBoxError)(struct MBox_Box * self);
    enum MBox_Error (*clearLastBoxError)(struct MBox_Box * box);
    size_t (*getBoxContentSize)(struct MBox_Box * self);
    struct MBox_Box * (*cloneBox)(struct MBox_Box * self);
    enum MBox_Error (*copyBoxContent)(struct MBox_Box * self, struct MBox_Box src);
    enum MBox_Error (*clearBox)(struct MBox_Box * self);
    enum MBox_Error (*destroyBox)(struct MBox_Box ** self);
    enum MBox_Shape (*getBoxShape)(struct MBox_Box * self);
    bool (*areBoxContentsEqual)(struct MBox_Box * selfA, struct MBox_Box * boxB);
    uint64_t (*getCopyOfUnsignedIntegerFromBox)(struct MBox_Box * self);
    enum MBox_Error (*putUnsignedIntegerIntoBox)(struct MBox_Box * self, uint64_t value);
    int64_t (*getCopyOfIntegerFromBox)(struct MBox_Box * self);
    enum MBox_Error (*putIntegerIntoBox)(struct MBox_Box * self, int64_t value);
    bool (*getCopyOfBooleanFromBox)(struct MBox_Box * self);
    enum MBox_Error (*putBooleanIntoBox)(struct MBox_Box * self, bool value);
    double (*getCopyOfDoubleFromBox)(struct MBox_Box * self);
    enum MBox_Error (*putDoubleIntoBox)(struct MBox_Box * self, double value);
    char * (*getStringFromBox)(struct MBox_Box * self);
    char * (*getCopyOfStringFromBox)(struct MBox_Box * self);
    enum MBox_Error (*putStringIntoBox)(struct MBox_Box * self, const char * fmt, va_list arg);
    void * (*getCopyOfReferenceFromBox)(struct MBox_Box * self);
    enum MBox_Error (*putReferenceIntoBox)(struct MBox_Box * self, void * value);
    struct MBox_List * (*getCopyOfListReferenceFromBox)(struct MBox_Box * self);
    enum MBox_Error (*putListReferenceIntoBox)(struct MBox_Box * self, struct MBox_List * value);
    struct MBox_Dictionary * (*getCopyOfDictionaryReferenceFromBox)(struct MBox_Box * self);
    enum MBox_Error (*putDictionaryReferenceIntoBox)(struct MBox_Box * self, struct MBox_Dictionary * value);
};

#endif
