#include "MBox/DynamicDictionary.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

long showMemoryUsageDelta(long base) {
    struct rusage myUsage;
    getrusage(RUSAGE_SELF, &myUsage);
    printf("MemoryUsageDelta=%ld\n", myUsage.ru_maxrss - base);
    return myUsage.ru_maxrss;
}

void displayDictionary(struct MBox_Dictionary * d) {

    puts("Displaying dictionary.");

    struct MBox_MBox * buffer;
    MBox_createDynamicMBox(&buffer);
    struct MBox_List * keyList;
    MBox_createDynamicList(&keyList);

    d->addKeysToList(d, keyList, buffer);

    unsigned int keyListSize;

    keyList->getLength(keyList, &keyListSize);

    printf("The dictionary has %d keys.\n", keyListSize);

    while(keyListSize != 0) {
        struct MBox_MBox * keyBuffer;
        char keyString[256];
        keyList->pop(keyList, 0, &keyBuffer);
        enum MBox_Shape s;
        keyBuffer->getShape(keyBuffer, &s);
        keyBuffer->readString(keyBuffer, keyString, 256);
        keyBuffer->destroy(&keyBuffer);
        d->getValue(d, keyString, buffer);
        enum MBox_Shape contentShape;
        buffer->getShape(buffer, &contentShape);
        double dvalue;
        int64_t i64value;
        uint64_t u64value;
        bool bvalue;
        char svalue[256];
        void * rvalue;
        switch(contentShape) {
            case MBox_Shape_DOUBLE:
                buffer->readDouble(buffer, &dvalue);
                printf("dict['%s']=%lf\n", keyString, dvalue);
                break;
            case MBox_Shape_SIGNED_64B_INTEGER:
                buffer->readSigned64BInteger(buffer, &i64value);
                printf("dict['%s']=%ld\n", keyString, i64value);
                break;
            case MBox_Shape_STRING:
                buffer->readString(buffer, svalue, 256);
                printf("dict['%s']='%s'\n", keyString, svalue);
                break;
            case MBox_Shape_BOOLEAN:
                buffer->readBoolean(buffer, &bvalue);
                printf("dict['%s']=%d\n", keyString, bvalue);
                break;
            case MBox_Shape_UNSIGNED_64B_INTEGER:
                buffer->readUnsigned64BInteger(buffer, &u64value);
                printf("dict['%s']=%lu\n", keyString, u64value);
                break;
            case MBox_Shape_REFERENCE:
                buffer->readReference(buffer, &rvalue);
                printf("dict['%s']=%p\n", keyString, rvalue);
                break;
            case MBox_Shape_NULL:
                printf("dict['%s']=null\n", keyString);
                break;
            default:
                break;
        }
        keyList->getLength(keyList, &keyListSize);
    }

    buffer->destroy(&buffer);
    keyList->destroy(&keyList);

    return;
}

int main(){

    long baseUsage = showMemoryUsageDelta(0);

    puts("Creating application objects.");
    struct MBox_MBox * buffer;
    MBox_createDynamicMBox(&buffer);
    struct MBox_Dictionary * dict0;
    MBox_createDynamicDictionary(&dict0);

    puts("Adding elements into the dictionary.");
    buffer->storeSigned64BInteger(buffer, 0x12345678);
    dict0->setValue(dict0, "largeNumber", buffer);
    buffer->storeDouble(buffer,3.141592);
    dict0->setValue(dict0, "pi", buffer);
    buffer->storeString(buffer, "Hello, world!");
    dict0->setValue(dict0, "message", buffer);
    buffer->storeString(buffer, "Just another string");
    dict0->setValue(dict0, "anotherMessage", buffer);
    buffer->storeReference(buffer, main);
    dict0->setValue(dict0, "mainAddress", buffer);

    puts("Retrieving one value");
    dict0->getValue(dict0, "largeNumber", buffer);
    int64_t readBuffer;
    buffer->readSigned64BInteger(buffer, &readBuffer);
    printf("dict0['largeNumber']=0x%lx\n", readBuffer);
    double doubleBuffer;
    dict0->getValue(dict0, "pi", buffer);
    buffer->readDouble(buffer, &doubleBuffer);
    printf("dict0['pi']=%lf\n", doubleBuffer);

    displayDictionary(dict0);

    puts("Removing an item");
    dict0->remove(dict0, "anotherMessage");
    displayDictionary(dict0);

    dict0->destroy(&dict0);

    showMemoryUsageDelta(baseUsage);

    return 0;
}
