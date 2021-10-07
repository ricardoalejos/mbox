#include "MBox2/FakeBox.h"

static enum MBox_Error getLastBoxError(struct MBox_Box * box);
static enum MBox_Error clearLastBoxError(struct MBox_Box * box);
static size_t getBoxContentSize(struct MBox_Box * box);
static struct MBox_Box * cloneBox(struct MBox_Box * box);
static enum MBox_Error copyBoxContent(struct MBox_Box * dst, struct MBox_Box src);
static enum MBox_Error clearBox(struct MBox_Box * box);
static enum MBox_Error destroyBox(struct MBox_Box ** box);
static enum MBox_Shape getBoxShape(struct MBox_Box * box);
static bool areBoxContentsEqual(struct MBox_Box * boxA, struct MBox_Box * boxB);
static uint64_t getCopyOfUnsignedIntegerFromBox(struct MBox_Box * box);
static enum MBox_Error putUnsignedIntegerIntoBox(struct MBox_Box * box, uint64_t value);
static int64_t getCopyOfIntegerFromBox(struct MBox_Box * box);
static enum MBox_Error putIntegerIntoBox(struct MBox_Box * box, int64_t value);
static bool getCopyOfBooleanFromBox(struct MBox_Box * box);
static enum MBox_Error putBooleanIntoBox(struct MBox_Box * box, bool value);
static double getCopyOfDoubleFromBox(struct MBox_Box * box);
static enum MBox_Error putDoubleIntoBox(struct MBox_Box * box, double value);
static char * getStringFromBox(struct MBox_Box * box);
static char * getCopyOfStringFromBox(struct MBox_Box * box);
static enum MBox_Error putStringIntoBox(struct MBox_Box * box, const char * fmt, va_list arg);
static void * getCopyOfReferenceFromBox(struct MBox_Box * box);
static enum MBox_Error putReferenceIntoBox(struct MBox_Box * box, void * value);
static struct MBox_List * getCopyOfListReferenceFromBox(struct MBox_Box * box);
static enum MBox_Error putListReferenceIntoBox(struct MBox_Box * box, struct MBox_List * value);
static struct MBox_Dictionary * getCopyOfDictionaryReferenceFromBox(struct MBox_Box * box);
static enum MBox_Error putDictionaryReferenceIntoBox(struct MBox_Box * box, struct MBox_Dictionary * value);

struct FakeBox {
    struct MBox_Box base;
};

struct FakeBox onlyBox = {
    .base.getLastBoxError=getLastBoxError,
    .base.clearLastBoxError=clearLastBoxError,
    .base.getBoxContentSize=getBoxContentSize,
    .base.cloneBox=cloneBox,
    .base.copyBoxContent=copyBoxContent,
    .base.clearBox=clearBox,
    .base.destroyBox=destroyBox,
    .base.getBoxShape=getBoxShape,
    .base.areBoxContentsEqual=areBoxContentsEqual,
    .base.getCopyOfUnsignedIntegerFromBox=getCopyOfUnsignedIntegerFromBox,
    .base.putUnsignedIntegerIntoBox=putUnsignedIntegerIntoBox,
    .base.getCopyOfIntegerFromBox=getCopyOfIntegerFromBox,
    .base.putIntegerIntoBox=putIntegerIntoBox,
    .base.getCopyOfBooleanFromBox=getCopyOfBooleanFromBox,
    .base.putBooleanIntoBox=putBooleanIntoBox,
    .base.getCopyOfDoubleFromBox=getCopyOfDoubleFromBox,
    .base.putDoubleIntoBox=putDoubleIntoBox,
    .base.getStringFromBox=getStringFromBox,
    .base.getCopyOfStringFromBox=getCopyOfStringFromBox,
    .base.putStringIntoBox=putStringIntoBox,
    .base.getCopyOfReferenceFromBox=getCopyOfReferenceFromBox,
    .base.putReferenceIntoBox=putReferenceIntoBox,
    .base.getCopyOfListReferenceFromBox=getCopyOfListReferenceFromBox,
    .base.putListReferenceIntoBox=putListReferenceIntoBox,
    .base.getCopyOfDictionaryReferenceFromBox=getCopyOfDictionaryReferenceFromBox,
    .base.putDictionaryReferenceIntoBox=putDictionaryReferenceIntoBox
};

struct MBox_Box * MBox_createFakeBox() {
    return &(onlyBox.base);
}

static enum MBox_Error getLastBoxError(struct MBox_Box * box){
    return MBox_Error_NOT_IMPLEMENTED;
}

static enum MBox_Error clearLastBoxError(struct MBox_Box * box){
    return MBox_Error_NOT_IMPLEMENTED;
}

static size_t getBoxContentSize(struct MBox_Box * box){
    return 0;
}

static struct MBox_Box * cloneBox(struct MBox_Box * box){
    return NULL;
}

static enum MBox_Error copyBoxContent(struct MBox_Box * dst, struct MBox_Box src){
    return MBox_Error_NOT_IMPLEMENTED;
}

static enum MBox_Error clearBox(struct MBox_Box * box){
    return MBox_Error_NOT_IMPLEMENTED;
}

static enum MBox_Error destroyBox(struct MBox_Box ** box){
    return MBox_Error_NOT_IMPLEMENTED;
}

static enum MBox_Shape getBoxShape(struct MBox_Box * box){
    return MBox_Error_NOT_IMPLEMENTED;
}

static bool areBoxContentsEqual(struct MBox_Box * boxA, struct MBox_Box * boxB){
    return false;
}

static uint64_t getCopyOfUnsignedIntegerFromBox(struct MBox_Box * box){
    return 0;
}

static enum MBox_Error putUnsignedIntegerIntoBox(struct MBox_Box * box, uint64_t value){
    return MBox_Error_NOT_IMPLEMENTED;
}

static int64_t getCopyOfIntegerFromBox(struct MBox_Box * box){
    return 0;
}

static enum MBox_Error putIntegerIntoBox(struct MBox_Box * box, int64_t value){
    return MBox_Error_NOT_IMPLEMENTED;
}

static bool getCopyOfBooleanFromBox(struct MBox_Box * box){
    return false;
}

static enum MBox_Error putBooleanIntoBox(struct MBox_Box * box, bool value){
    return MBox_Error_NOT_IMPLEMENTED;
}

static double getCopyOfDoubleFromBox(struct MBox_Box * box){
    return 0.0;
}

static enum MBox_Error putDoubleIntoBox(struct MBox_Box * box, double value){
    return MBox_Error_NOT_IMPLEMENTED;
}

static char * getStringFromBox(struct MBox_Box * box){
    return "Hello from the fake box";
}

static char * getCopyOfStringFromBox(struct MBox_Box * box){
    return "";
}

static enum MBox_Error putStringIntoBox(struct MBox_Box * box, const char * fmt, va_list arg){
    return MBox_Error_NOT_IMPLEMENTED;
}

static void * getCopyOfReferenceFromBox(struct MBox_Box * box){
    return NULL;
}

static enum MBox_Error putReferenceIntoBox(struct MBox_Box * box, void * value){
    return MBox_Error_NOT_IMPLEMENTED;
}

static struct MBox_List * getCopyOfListReferenceFromBox(struct MBox_Box * box){
    return NULL;
}

static enum MBox_Error putListReferenceIntoBox(struct MBox_Box * box, struct MBox_List * value){
    return MBox_Error_NOT_IMPLEMENTED;
}

static struct MBox_Dictionary * getCopyOfDictionaryReferenceFromBox(struct MBox_Box * box){
    return NULL;
}

static enum MBox_Error putDictionaryReferenceIntoBox(struct MBox_Box * box, struct MBox_Dictionary * value){
    return MBox_Error_NOT_IMPLEMENTED;
}
