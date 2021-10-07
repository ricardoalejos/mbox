#include "MBox2/Box.h"
#include <string.h>

enum MBox_Error MBox_getLastBoxError(struct MBox_Box * box){
    return box->getLastBoxError(box);
}

size_t MBox_getBoxContentSize(struct MBox_Box * box) {
    return box->getBoxContentSize(box);
}

struct MBox_Box * MBox_cloneBox(struct MBox_Box * box) {
    return box->cloneBox(box);
}

enum MBox_Error MBox_copyBoxContent(struct MBox_Box * dst, struct MBox_Box src) {
    return dst->copyBoxContent(dst, src);
}

enum MBox_Error MBox_clearBox(struct MBox_Box * box) {
    return box->clearBox(box);
}

enum MBox_Error MBox_destroyBox(struct MBox_Box ** box) {
    return (*box)->destroyBox(box);
}

enum MBox_Shape MBox_getBoxShape(struct MBox_Box * box) {
    return box->getBoxShape(box);
}

bool MBox_areBoxContentsEqual(struct MBox_Box * boxA, struct MBox_Box * boxB) {
    return boxA->areBoxContentsEqual(boxA, boxB);
}

uint64_t MBox_getCopyOfUnsignedIntegerFromBox(struct MBox_Box * box) {
    return box->getCopyOfUnsignedIntegerFromBox(box);
}

enum MBox_Error MBox_putUnsignedIntegerIntoBox(struct MBox_Box * box, uint64_t value) {
    return box->putUnsignedIntegerIntoBox(box, value);
}

int64_t MBox_getCopyOfIntegerFromBox(struct MBox_Box * box) {
    return box->getCopyOfIntegerFromBox(box);
}

enum MBox_Error MBox_putIntegerIntoBox(struct MBox_Box * box, int64_t value){
    return box->putIntegerIntoBox(box, value);
}

bool MBox_getCopyOfBooleanFromBox(struct MBox_Box * box) {
    return box->getCopyOfBooleanFromBox(box);
}

enum MBox_Error MBox_putBooleanIntoBox(struct MBox_Box * box, bool value) {
    return box->putBooleanIntoBox(box, value);
}

double MBox_getCopyOfDoubleFromBox(struct MBox_Box * box) {
    return box->getCopyOfDoubleFromBox(box);
}

enum MBox_Error MBox_putDoubleIntoBox(struct MBox_Box * box, double value){
    return box->putDoubleIntoBox(box, value);
}

char * MBox_getStringFromBox(struct MBox_Box * box) {
    return box->getStringFromBox(box);
}

char * MBox_getCopyOfStringFromBox(struct MBox_Box * box) {
    return box->getCopyOfStringFromBox(box);
}

enum MBox_Error MBox_putStringIntoBox(struct MBox_Box * box, const char * fmt, ...) {
    va_list argPointer;
    enum MBox_Error returnValue;
    va_start(argPointer, fmt);
    returnValue = box->putStringIntoBox(box, fmt, argPointer);
    va_end(argPointer);
    return returnValue;
}

void * MBox_getCopyOfReferenceFromBox(struct MBox_Box * box) {
    return box->getCopyOfReferenceFromBox(box);
}

enum MBox_Error MBox_putReferenceIntoBox(struct MBox_Box * box, void * value) {
    return box->putReferenceIntoBox(box, value);
}

struct MBox_List * MBox_getCopyOfListReferenceFromBox(struct MBox_Box * box) {
    return box->getCopyOfListReferenceFromBox(box);
}

enum MBox_Error MBox_putListReferenceIntoBox(struct MBox_Box * box, struct MBox_List * value) {
    return box->putListReferenceIntoBox(box, value);
}

struct MBox_Dictionary * MBox_getCopyOfDictionaryReferenceFromBox(struct MBox_Box * box) {
    return box->getCopyOfDictionaryReferenceFromBox(box);
}

enum MBox_Error MBox_putDictionaryReferenceIntoBox(struct MBox_Box * box, struct MBox_Dictionary * value) {
    return box->putDictionaryReferenceIntoBox(box, value);
}

enum MBox_Error MBox_clearLastBoxError(struct MBox_Box * box) {
    return box->clearLastBoxError(box);
}
