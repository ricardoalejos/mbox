#include "MBox/DynamicList.h"
#include "MBox/DynamicMBox.h"
#include "MBox/Display.h"
#include <stdio.h>

int main(){

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

    struct MBox_MBox * newValue;
    list0->addEmptyItem(list0, &newValue);
    newValue->storeString(newValue, "Value added without buffers!");

    puts("Destroying created objects.");
    buffer->destroy(&buffer);
    MBox_displayList(list0);
    list0->destroy(&list0);

    return 0;
}
