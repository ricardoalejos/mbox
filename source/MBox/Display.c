#include "MBox/Display.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
#include <stdio.h>
#include <stdlib.h>

static void _displayMBox(
    struct MBox_MBox * mbox,
    bool addNewLine,
    unsigned int depth,
    unsigned int indentSize
);

static void _displayList(
    struct MBox_List * list,
    bool addNewLine,
    unsigned int depth,
    unsigned int indentSize
);

static void _displayDictionary(
    struct MBox_Dictionary * dictionary,
    bool addNewLine,
    unsigned int depth,
    unsigned int indentSize
);

static void _displayMBox(
    struct MBox_MBox * mbox,
    bool addNewLine,
    unsigned int depth,
    unsigned int indentSize
){
    enum MBox_Shape shape;
    unsigned int size;

    char * newLine;
    if (addNewLine) {
        newLine = "\n";
    } else {
        newLine = "";
    }

    uint64_t uBuffer;
    int64_t iBuffer;
    double dBuffer;
    bool bBuffer;
    char * sBuffer;
    void * rBuffer;
    struct MBox_List * lBuffer;
    struct MBox_Dictionary * dictBuffer;

    mbox->getShape(mbox, &shape);
    mbox->getSize(mbox, &size);

    switch (shape) {
        case MBox_Shape_DOUBLE:
            mbox->readDouble(mbox, &dBuffer);
            printf("%lf%s", dBuffer, newLine);
            break;
        case MBox_Shape_SIGNED_64B_INTEGER:
            mbox->readSigned64BInteger(mbox, &iBuffer);
            printf("%ld%s", iBuffer, newLine);
            break;
        case MBox_Shape_STRING:
            sBuffer = (char *) malloc(size);
            mbox->readString(mbox, sBuffer, size);
            printf("'%s'%s", sBuffer, newLine);
            free(sBuffer);
            break;
        case MBox_Shape_BOOLEAN:
            mbox->readBoolean(mbox, &bBuffer);
            printf("%d%s", bBuffer, newLine);
            break;
        case MBox_Shape_UNSIGNED_64B_INTEGER:
            mbox->readUnsigned64BInteger(mbox, &uBuffer);
            printf("%lu%s", uBuffer, newLine);
            break;
        case MBox_Shape_REFERENCE:
            mbox->readReference(mbox, &rBuffer);
            printf("%p%s", rBuffer, newLine);
            break;
        case MBox_Shape_NULL:
            printf("NULL%s", newLine);
            break;
        case MBox_Shape_LIST_REFERENCE:
            mbox->readListReference(mbox, &lBuffer);
            _displayList(lBuffer, addNewLine, depth, indentSize);
            break;
        case MBox_Shape_DICTIONARY_REFERENCE:
            mbox->readDictionaryReference(mbox, &dictBuffer);
            _displayDictionary(dictBuffer, addNewLine, depth, indentSize);
            break;
        default:
            break;
    }
}

static void _displayList(
    struct MBox_List * list,
    bool addNewLine,
    unsigned int depth,
    unsigned int indentSize
){
    struct MBox_MBox * buffer;
    MBox_createDynamicMBox(&buffer);

    unsigned int length;
    list->getLength(list, &length);

    char * outerIndent = (char *) malloc(indentSize*depth + 1);
    snprintf(outerIndent, indentSize*depth + 1, "%*c", indentSize*depth, ' ');
    char * innerIndent = (char *) malloc(indentSize*(depth + 1) + 1);
    snprintf(
        innerIndent,
        indentSize*(depth + 1) + 1,
        "%*c",
        indentSize*(depth + 1),
        ' '
    );

    char * newLine;
    if (addNewLine) {
        newLine = "\n";
    } else {
        newLine = "";
    }

    printf("[\n");
    for(int index = 0; index < length; index ++){
        list->getItem(list, index, buffer);
        printf("%s", innerIndent);
        _displayMBox(buffer, false, depth + 1, indentSize);
        if (index < length - 1) printf(",");
        printf("\n");
    }
    printf("%s" ,outerIndent);
    printf("]%s", newLine);

    free(outerIndent);
    buffer->destroy(&buffer);
    return;
}

static void _displayDictionary(
    struct MBox_Dictionary * dictionary,
    bool addNewLine,
    unsigned int depth,
    unsigned int indentSize
) {
    struct MBox_MBox * buffer;
    MBox_createDynamicMBox(&buffer);
    struct MBox_List * keys;
    MBox_createDynamicList(&keys);

    dictionary->addKeysToList(dictionary, keys);

    unsigned int numberOfElements;
    keys->getLength(keys, &numberOfElements);

    char * outerIndent = (char *) malloc(indentSize*depth + 1);
    snprintf(outerIndent, indentSize*depth + 1, "%*c", indentSize*depth, ' ');
    char * innerIndent = (char *) malloc(indentSize*(depth + 1) + 1);
    snprintf(
        innerIndent,
        indentSize*(depth + 1) + 1,
        "%*c",
        indentSize*(depth + 1),
        ' '
    );

    char * newLine;
    if (addNewLine) {
        newLine = "\n";
    } else {
        newLine = "";
    }

    puts("{");
    while (numberOfElements > 0) {
        struct MBox_MBox * currentKey;
        keys->pop(keys, 0, &currentKey);
        dictionary->getValue(dictionary, currentKey, buffer);
        printf("%s", innerIndent);
        _displayMBox(currentKey, false, depth + 1, indentSize);
        printf(": ");
        _displayMBox(buffer, false, depth + 1, indentSize);
        currentKey->destroy(&currentKey);
        keys->getLength(keys, &numberOfElements);
        if (numberOfElements > 0) printf(",");
        printf("\n");
    }
    printf("%s", outerIndent);
    printf("}%s", newLine);

    free(innerIndent);
    free(outerIndent);
    buffer->destroy(&buffer);
    keys->destroy(&keys);
}


void MBox_displayMBox(
    struct MBox_MBox * mbox
) {
    _displayMBox(mbox, true, 0, 4);
}

void MBox_displayList(
    struct MBox_List * list
) {
    _displayList(list, true, 0, 4);
}

void MBox_displayDictionary(
    struct MBox_Dictionary * dictionary
) {
    _displayDictionary(dictionary, true, 0, 4);
}
