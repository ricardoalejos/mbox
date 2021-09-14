#include "MBox/DynamicDictionary.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
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
    struct MBox_Dictionary * dict0;
    MBox_createDynamicDictionary(&dict0);

    puts("Adding elements into the dictionary.");
    buffer->storeSigned64BInteger(buffer, 0x12345678);
    dict0->setValue(dict0, "largeNumber", buffer);
    buffer->storeDouble(buffer, 3.141592);
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

    MBox_displayDictionary(dict0);

    puts("Removing an item");
    dict0->remove(dict0, "anotherMessage");
    MBox_displayDictionary(dict0);

    dict0->destroy(&dict0);

    showMemoryUsageDelta(baseUsage);

    return 0;
}
