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

    puts("Adding elements into the dictionary.");
    keyBuffer->storeString(keyBuffer, "largeNumber");
    valueBuffer->storeSigned64BInteger(valueBuffer, 12345678);
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
    struct MBox_MBox * newValue;
    dict0->addEmptyEntry(dict0, keyBuffer, &newValue);
    newValue->storeString(newValue, "This string was allocated without value buffering!");

    puts("Retrieving one value");
    keyBuffer->storeString(keyBuffer, "largeNumber");
    struct MBox_MBox * valueReference;
    dict0->getValueRef(dict0, keyBuffer, &valueReference);
    printf("dict0['largeNumber']=");
    MBox_displayMBox(valueReference);
    keyBuffer->storeString(keyBuffer, "pi");
    dict0->getValue(dict0, keyBuffer, valueBuffer);
    printf("dict0['pi']=");
    MBox_displayMBox(valueBuffer);

    MBox_displayDictionary(dict0);

    puts("Removing an item");
    keyBuffer->storeString(keyBuffer, "anotherMessage");
    dict0->remove(dict0, keyBuffer);
    MBox_displayDictionary(dict0);

    dict0->destroy(&dict0);
    valueBuffer->destroy(&valueBuffer);
    keyBuffer->destroy(&keyBuffer);

    return 0;
}
