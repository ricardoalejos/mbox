#include "MBox/DynamicList.h"
#include "MBox/DynamicMBox.h"
#include "MBox/Display.h"
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

long showMemoryUsageDelta(long base) {
    struct rusage myUsage;
    getrusage(RUSAGE_SELF, &myUsage);
    printf("MemoryUsageDelta=%ld\n", myUsage.ru_maxrss - base);
    return myUsage.ru_maxrss;
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
    MBox_displayList(list0);

    puts("Removing a value from the list.");
    buffer->storeString(buffer, "Hello, world!");
    list0->remove(list0, buffer);
    MBox_displayList(list0);

    puts("Inserting a value in the list.");
    buffer->storeString(buffer, "Hello again, world!");
    list0->insert(list0, 1, buffer);
    MBox_displayList(list0);

    puts("Popping one element from the list.");
    list0->pop(list0, -2, NULL);
    MBox_displayList(list0);

    puts("Destroying created objects.");
    buffer->destroy(&buffer);
    MBox_displayList(list0);

    showMemoryUsageDelta(baseUsage);

    return 0;
}
