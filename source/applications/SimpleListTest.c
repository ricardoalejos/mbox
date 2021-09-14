#include "MBox/DynamicList.h"
#include "MBox/DynamicMBox.h"
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

long showMemoryUsageDelta(long base) {
    struct rusage myUsage;
    getrusage(RUSAGE_SELF, &myUsage);
    printf("MemoryUsageDelta=%ld\n", myUsage.ru_maxrss - base);
    return myUsage.ru_maxrss;
}

void displayList(struct MBox_List * list, struct MBox_MBox * buffer){
    unsigned int listLength;
    list->getLength(list, &listLength);
    printf("The list has %d elements:\n", listLength);

    for(int index = 0; index < listLength; index++){
        list->getItem(list, index, buffer);
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
                printf("list[%d]=%lf\n", index, dvalue);
                break;
            case MBox_Shape_SIGNED_64B_INTEGER:
                buffer->readSigned64BInteger(buffer, &i64value);
                printf("list[%d]=%ld\n", index, i64value);
                break;
            case MBox_Shape_STRING:
                buffer->readString(buffer, svalue, 256);
                printf("list[%d]='%s'\n", index, svalue);
                break;
            case MBox_Shape_BOOLEAN:
                buffer->readBoolean(buffer, &bvalue);
                printf("list[%d]=%d\n", index, bvalue);
                break;
            case MBox_Shape_UNSIGNED_64B_INTEGER:
                buffer->readUnsigned64BInteger(buffer, &u64value);
                printf("list[%d]=%lu\n", index, u64value);
                break;
            case MBox_Shape_REFERENCE:
                buffer->readReference(buffer, &rvalue);
                printf("list[%d]=%p\n", index, rvalue);
                break;
            case MBox_Shape_NULL:
                printf("list[%d]=null\n", index);
                break;
            default:
                break;
        }
    }
}

int main(){

    long baseUsage = showMemoryUsageDelta(0);

    puts("Creating application objects.");
    struct MBox_MBox * buffer;
    MBox_createDynamicMBox(&buffer);
    struct MBox_List * list0;
    MBox_createDynamicList(&list0);

    puts("Adding elements into the list.");
    buffer->storeSigned64BInteger(buffer, 0x12345678);
    list0->addItem(list0, buffer);
    buffer->storeDouble(buffer, 3.141592);
    list0->addItem(list0, buffer);
    buffer->storeString(buffer, "Hello, world!");
    list0->addItem(list0, buffer);
    buffer->storeString(buffer, "Just another string");
    list0->addItem(list0, buffer);
    buffer->storeReference(buffer, main);
    list0->addItem(list0, buffer);
    displayList(list0, buffer);

    puts("Removing a value from the list.");
    buffer->storeString(buffer, "Hello, world!");
    list0->remove(list0, buffer);
    displayList(list0, buffer);

    puts("Inserting a value in the list.");
    buffer->storeString(buffer, "Hello again, world!");
    list0->insert(list0, 1, buffer);
    displayList(list0, buffer);

    puts("Popping one element from the list.");
    list0->pop(list0, -2, NULL);
    displayList(list0, buffer);

    puts("Destroying created objects.");
    buffer->destroy(&buffer);
    list0->destroy(&list0);

    showMemoryUsageDelta(baseUsage);

    return 0;
}
