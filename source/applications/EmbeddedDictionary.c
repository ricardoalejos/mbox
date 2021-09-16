#include "MBox/DynamicDictionary.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
#include "MBox/Display.h"
#include <stdio.h>

int main(){

    puts("Creating application objects.");
    struct MBox_MBox * valueBuffer;
    MBox_createDynamicMBox(&valueBuffer);
    struct MBox_MBox * keyBuffer;
    MBox_createDynamicMBox(&keyBuffer);
    struct MBox_Dictionary * dict0;
    MBox_createDynamicDictionary(&dict0);
    struct MBox_Dictionary * dict1;
    MBox_createDynamicDictionary(&dict1);

    puts("Adding elements into the dictionary.");
    keyBuffer->storeString(keyBuffer, "largeNumber");
    valueBuffer->storeSigned64BInteger(valueBuffer, 0x12345678);
    dict0->setValue(dict0, keyBuffer, valueBuffer);
    keyBuffer->storeString(keyBuffer, "pi");
    valueBuffer->storeDouble(valueBuffer, 3.141592);
    dict0->setValue(dict0, keyBuffer, valueBuffer);
    keyBuffer->storeString(keyBuffer, "message");
    valueBuffer->storeString(valueBuffer, "Hello, world!");
    dict0->setValue(dict0, keyBuffer, valueBuffer);
    keyBuffer->storeString(keyBuffer, "anotherMessage");
    valueBuffer->storeString(valueBuffer, "Just another string");
    dict0->setValue(dict0, keyBuffer, valueBuffer);
    keyBuffer->storeUnsigned64BInteger(keyBuffer, 0xABCDEF);
    valueBuffer->storeReference(valueBuffer, main);
    dict0->setValue(dict0, keyBuffer, valueBuffer);
    keyBuffer->storeString(keyBuffer, "embeddedDictionary");
    valueBuffer->storeDictionaryReference(valueBuffer, dict0);
    dict1->setValue(dict1, keyBuffer, valueBuffer);

    MBox_displayDictionary(dict1);

    puts("Removing an item");
    keyBuffer->storeString(keyBuffer, "anotherMessage");
    dict0->remove(dict0, keyBuffer);
    MBox_displayDictionary(dict0);

    dict0->destroy(&dict0);
    valueBuffer->destroy(&valueBuffer);
    keyBuffer->destroy(&keyBuffer);

    return 0;
}
