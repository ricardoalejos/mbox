#include <stdio.h>
#include "MBox2/MBox.h"
#include "MBox2/FakeBox.h"

int main() {
    struct MBox_Box * box0 = MBox_createFakeBox();
    MBox_putStringIntoBox(box0, "Hello world!");
    printf("Box0 contains: %s\n", MBox_getStringFromBox(box0));
    return 0;
}
