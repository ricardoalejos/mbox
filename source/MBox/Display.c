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

static void _createIndentStrings(
    unsigned int indentLevel,
    unsigned int indentSize,
    char ** innerIndent,
    char ** outerIndent
);

static void _displayMBox(
    struct MBox_MBox * mbox,
    bool addNewLine,
    unsigned int depth,
    unsigned int indentSize
){
    enum MBox_Shape shape;
    unsigned int size;

    char * newLine = addNewLine ? "\n" : "";

    uint64_t unsignedIntegerValue;
    int64_t signedIntegerValue;
    double doubleValue;
    bool booleanValue;
    char * stringValue;
    void * referenceValue;
    struct MBox_List * listReference;
    struct MBox_Dictionary * dictionaryReference;

    mbox->getShape(mbox, &shape);
    mbox->getSize(mbox, &size);

    switch (shape) {
        case MBox_Shape_DOUBLE:
            mbox->readDouble(mbox, &doubleValue);
            printf("%lf%s", doubleValue, newLine);
            break;
        case MBox_Shape_SIGNED_64B_INTEGER:
            mbox->readSigned64BInteger(mbox, &signedIntegerValue);
            printf("%ld%s", signedIntegerValue, newLine);
            break;
        case MBox_Shape_STRING:
            mbox->seeString(mbox, &stringValue);
            printf("'%s'%s", stringValue, newLine);
            break;
        case MBox_Shape_BOOLEAN:
            mbox->readBoolean(mbox, &booleanValue);
            printf("%s%s", booleanValue ? "true" : "false", newLine);
            break;
        case MBox_Shape_UNSIGNED_64B_INTEGER:
            mbox->readUnsigned64BInteger(mbox, &unsignedIntegerValue);
            printf("%lu%s", unsignedIntegerValue, newLine);
            break;
        case MBox_Shape_REFERENCE:
            mbox->readReference(mbox, &referenceValue);
            printf("%p%s", referenceValue, newLine);
            break;
        case MBox_Shape_NULL:
            printf("NULL%s", newLine);
            break;
        case MBox_Shape_LIST_REFERENCE:
            mbox->readListReference(mbox, &listReference);
            _displayList(listReference, addNewLine, depth, indentSize);
            break;
        case MBox_Shape_DICTIONARY_REFERENCE:
            mbox->readDictionaryReference(mbox, &dictionaryReference);
            _displayDictionary(
                dictionaryReference,
                addNewLine,
                depth,
                indentSize
            );
            break;
        default:
            break;
    }
}

static void _createIndentStrings(
    unsigned int indentLevel,
    unsigned int indentSize,
    char ** innerIndent,
    char ** outerIndent
) {
    unsigned int outerIndentSize = indentSize*indentLevel;
    *outerIndent = (char *) malloc(outerIndentSize+1);
    snprintf(*outerIndent, outerIndentSize+1, "%*c", outerIndentSize, ' ');
    unsigned int innerIndentSize = indentSize*(indentLevel + 1);
    *innerIndent = (char *) malloc(innerIndentSize+1);
    snprintf(*innerIndent, innerIndentSize+1, "%*c", innerIndentSize, ' ');
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

    char * outerIndent;
    char * innerIndent;
    _createIndentStrings(depth, indentSize, &innerIndent, &outerIndent);

    printf("[\n");
    for(int index = 0; index < length; index ++){
        list->getItem(list, index, buffer);
        printf("%s", innerIndent);
        _displayMBox(buffer, false, depth + 1, indentSize);
        printf(index < length - 1 ? ",\n" : "\n");
    }
    printf("%s]%s", outerIndent, addNewLine ? "\n" : "");

    free(innerIndent);
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

    char * outerIndent;
    char * innerIndent;
    _createIndentStrings(depth, indentSize, &innerIndent, &outerIndent);

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
        printf(numberOfElements > 0 ? ",\n" : "\n");
    }
    printf("%s}%s", outerIndent, addNewLine ? "\n" : "");

    free(innerIndent);
    free(outerIndent);
    buffer->destroy(&buffer);
    keys->destroy(&keys);
    return;
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
