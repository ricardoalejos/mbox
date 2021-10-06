#include "MBox/DynamicDictionary.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
#include "MBox/Display.h"
#include <stdio.h>

int main(){

    puts("Creating application objects.");
    struct MBox_Dictionary * dict0;
    MBox_createDynamicDictionary(&dict0);
    struct MBox_Dictionary * dict1;
    MBox_createDynamicDictionary(&dict1);

    puts("Adding elements into the dictionary.");
    MBox_toStr(dict0->key, "largeNumber");
    MBox_toUInt64(MBox_addEntry(dict0)) = 123456789;
    MBox_toStr(dict0->key, "message");
    MBox_toStr(MBox_addEntry(dict0), "Hello, world!");
    MBox_toStr(dict0->key, "anotherMessage");
    MBox_toStr(MBox_addEntry(dict0), "Another string.");
    MBox_toUInt64(dict0->key) = 11223344;
    MBox_toRef(MBox_addEntry(dict0)) = main;

    puts("Put one dictionary inside another");
    MBox_toStr(dict1->key, "embeddedDictionary");
    MBox_toDictRef(MBox_addEntry(dict1)) = dict0;
    MBox_displayDictionary(dict1);

    puts("Removing an item from inner dictionary.");
    MBox_toStr(dict0->key, "anotherMessage");
    MBox_delEntry(dict0);
    MBox_displayDictionary(dict1);

    dict1->destroy(&dict1);
    dict0->destroy(&dict0);

    return 0;
}
