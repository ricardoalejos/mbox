#include "MBox/DynamicDictionary.h"
#include "MBox/DynamicMBox.h"
#include "MBox/DynamicList.h"
#include "MBox/Display.h"
#include <stdio.h>

int main(){

    struct MBox_MBox * bufferBox;
    MBox_createDynamicMBox(&bufferBox);

    // Store data in the bottomList
    struct MBox_List * bottomList;
    MBox_createDynamicList(&bottomList);
    bufferBox->storeDouble(bufferBox, 3.141592);
    bottomList->addItem(bottomList, bufferBox);

    // Store a reference to bottomList inside topList
    struct MBox_List * topList;
    MBox_createDynamicList(&topList);
    bufferBox->storeReference(bufferBox, bottomList);
    topList->addItem(topList, bufferBox);
    MBox_displayList(topList);

    // We can delete the bufferBox because list->pop() delegates the ownership
    // of the list element to the caller.
    bufferBox->destroy(&bufferBox);

    // Let us retrieve the bottomList in a different reference.
    struct MBox_List * bottomListReference;
    topList->pop(topList, 0, &bufferBox);
    bufferBox->readReference(bufferBox, (void**) &bottomListReference);
    MBox_displayList(bottomListReference);

    // Notice how both bottomList and bottomListReference point to the same
    // address. Thus, they point to the same object.
    printf("bottomList is allocated at address %p,\n", bottomList);
    printf("bottomListReference = %p.\n", bottomListReference);

    // The owner of the object must destroy it.
    bufferBox->destroy(&bufferBox);
    bottomList->destroy(&bottomList);
    topList->destroy(&topList);

    return 0;
}
