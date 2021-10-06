#include "MBox/DynamicDictionary.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
#include "MBox/Display.h"
#include <stdio.h>

int main(){

    puts("Creating dictionary dict0.");
    struct MBox_Dictionary * dict0;
    MBox_createDynamicDictionary(&dict0);

    puts("Adding elements into the dictionary.");
    MBox_toStr(dict0->key, "largeNumber");
    MBox_toUInt64(MBox_addEntry(dict0)) = 123456789;

    MBox_toStr(dict0->key, "message");
    MBox_toStr(MBox_addEntry(dict0), "Hello, world!");

    MBox_toStr(dict0->key, "anotherMessage");
    MBox_toStr(MBox_addEntry(dict0), "Another string.");

    MBox_toUInt64(dict0->key) = 11223344;
    MBox_toRef(MBox_addEntry(dict0)) = main;

    printf("Direct access to dict0['message']: ");
    MBox_toStr(dict0->key, "message");
    puts(MBox_asStr(MBox_getEntry(dict0)));

    MBox_toStr(dict0->key, "unknownKey");
    printf("Access to non existing item: %d\n", MBox_hasEntry(dict0));

    MBox_toStr(dict0->key, "message");
    printf("Confirm item existence: %d\n", MBox_hasEntry(dict0));

    MBox_toUInt64(dict0->key) = 42;
    MBox_toStr(MBox_addEntry(dict0), "magic");

    MBox_displayDictionary(dict0);

    puts("Removing an item");
    MBox_toStr(dict0->key, "anotherMessage");
    MBox_delEntry(dict0);

    MBox_displayDictionary(dict0);

    dict0->destroy(&dict0);

    return 0;
}
