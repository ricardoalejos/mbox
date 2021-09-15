#include "MBox/Display.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
#include <stdio.h>
#include <stdlib.h>

void MBox_displayMBox(struct MBox_MBox * mbox, char * prefix, char * suffix){
    enum MBox_Shape shape;
    unsigned int size;

    uint64_t uBuffer;
    int64_t iBuffer;
    double dBuffer;
    bool bBuffer;
    char * sBuffer;
    void * rBuffer;

    mbox->getShape(mbox, &shape);
    mbox->getSize(mbox, &size);

    switch (shape) {
        case MBox_Shape_DOUBLE:
            mbox->readDouble(mbox, &dBuffer);
            printf("%s%lf%s", prefix, dBuffer, suffix);
            break;
        case MBox_Shape_SIGNED_64B_INTEGER:
            mbox->readSigned64BInteger(mbox, &iBuffer);
            printf("%s%ld%s", prefix, iBuffer, suffix);
            break;
        case MBox_Shape_STRING:
            sBuffer = (char *) malloc(size);
            mbox->readString(mbox, sBuffer, size);
            printf("%s'%s'%s", prefix, sBuffer, suffix);
            free(sBuffer);
            break;
        case MBox_Shape_BOOLEAN:
            mbox->readBoolean(mbox, &bBuffer);
            printf("%s%d%s", prefix, bBuffer, suffix);
            break;
        case MBox_Shape_UNSIGNED_64B_INTEGER:
            mbox->readUnsigned64BInteger(mbox, &uBuffer);
            printf("%s%lu%s", prefix, uBuffer, suffix);
            break;
        case MBox_Shape_REFERENCE:
            mbox->readReference(mbox, &rBuffer);
            printf("%s%p%s", prefix, rBuffer, suffix);
            break;
        case MBox_Shape_NULL:
            printf("%sNULL%s", prefix, suffix);
            break;
        default:
            break;
    }
}

void MBox_displayList(struct MBox_List * list){
    struct MBox_MBox * buffer;
    MBox_createDynamicMBox(&buffer);

    unsigned int length;
    list->getLength(list, &length);

    printf("[\n");
    for(int index = 0; index < length; index ++){
        list->getItem(list, index, buffer);
        MBox_displayMBox(buffer, "    ", "");
        if (index < length - 1) printf(",");
        printf("\n");
    }
    printf("]\n");

    buffer->destroy(&buffer);
    return;
}

void MBox_displayDictionary(struct MBox_Dictionary * dictionary) {
    struct MBox_MBox * buffer;
    MBox_createDynamicMBox(&buffer);
    struct MBox_List * keys;
    MBox_createDynamicList(&keys);

    dictionary->addKeysToList(dictionary, keys);

    unsigned int numberOfElements;
    keys->getLength(keys, &numberOfElements);

    puts("{");
    while (numberOfElements > 0) {
        struct MBox_MBox * currentKey;
        keys->pop(keys, 0, &currentKey);
        dictionary->getValue(dictionary, currentKey, buffer);
        MBox_displayMBox(currentKey, "    ", " : ");
        MBox_displayMBox(buffer, "", "");
        currentKey->destroy(&currentKey);
        keys->getLength(keys, &numberOfElements);
        if (numberOfElements > 0) printf(",");
        printf("\n");
    }
    puts("}");

    buffer->destroy(&buffer);
    keys->destroy(&keys);
}
