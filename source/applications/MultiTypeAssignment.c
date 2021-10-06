#include "MBox/DynamicMBox.h"
#include "MBox/Display.h"
#include <stdio.h>

void displayBoxInformation(struct MBox_MBox * box, char * name){
    unsigned int size;
    enum MBox_Shape shape;

    static char * SHAPE_NAMES[MBox_Shape_NUMBER_OF_SHAPES] = {
        [MBox_Shape_UNSIGNED_64B_INTEGER] = "Unsigned 64-bit Integer",
        [MBox_Shape_SIGNED_64B_INTEGER] = "Signed 64-bit Integer",
        [MBox_Shape_DOUBLE] = "Double",
        [MBox_Shape_STRING] = "String",
        [MBox_Shape_BOOLEAN] = "Boolean",
        [MBox_Shape_REFERENCE] = "Reference",
        [MBox_Shape_LIST_REFERENCE] = "List Reference",
        [MBox_Shape_DICTIONARY_REFERENCE] = "Dictionary Reference",
        [MBox_Shape_CUSTOM] = "Custom",
        [MBox_Shape_NULL] = "Null"
    };

    box->getShape(box, &shape);
    box->getSize(box, &size);

    printf("%s (%s, %d bytes) = ", name, SHAPE_NAMES[shape], size);
    MBox_displayMBox(box);
}

int main(){
    struct MBox_MBox * box0;

    puts("Creating box0.");
    MBox_createDynamicMBox(&box0);
    displayBoxInformation(box0, "box0");

    puts("Storing an uint64_t value in box0.");
    MBox_toUInt64(box0) = 0x1234567812345678;
    printf("Direct read as uint64t: 0x%08lX.\n", MBox_asUInt64(box0));

    printf("Storing a string value in box0.");
    MBox_toStr(box0, "Hello %s!", "over there");
    displayBoxInformation(box0, "box0");

    puts("Resetting box0.");
    box0->reset(box0);
    displayBoxInformation(box0, "box0");

    puts("Duplicating box0 into box1.");
    struct MBox_MBox * box1 = box0->clone(box0);
    displayBoxInformation(box1, "box1"); 

    puts("Storing a boolean.");
    MBox_toBool(box0) = false;
    displayBoxInformation(box0, "box0");

    puts("Storing the address of main.");
    MBox_toRef(box0) = main;
    printf("Main is at %p, and the box has %p\n", main, MBox_asRef(box0));

    puts("Deleting box0.");
    box0->destroy(&box0);
    displayBoxInformation(box1, "box1"); 
    puts("Deleting box1.");
    box1->destroy(&box1);
    printf("box0 = %p\n", box0);
    printf("box1 = %p\n", box1);

    return 0;
}
