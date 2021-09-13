#include "MBox/DynamicMBox.h"
#include <stdio.h>

int main(){
    struct MBox_MBox * box0;

    puts("Creating box0.");
    DynamicMBox_create(&box0);
    printf("Created box0 at %p\n", box0);

    bool isEmpty;
    enum MBox_Shape box0Shape;
    unsigned int box0Size;

    box0->isEmpty(box0, &isEmpty);
    box0->getShape(box0, &box0Shape);
    box0->getSize(box0, &box0Size);
    printf(
        "box0Size=%d, isEmpty=%d, box0Shape=%d\n",
        box0Size,
        isEmpty,
        box0Shape
    );

    puts("Storing an uint64_t value in box0.");
    uint64_t u64WriteValue = 0x1234567812345678;
    uint64_t u64bReadValue = 0x0;
    box0->storeUnsigned64BInteger(box0, u64WriteValue);
    box0->readUnsigned64BInteger(box0, &u64bReadValue);
    printf("u64bReadValue=%lx\n", u64bReadValue);

    box0->isEmpty(box0, &isEmpty);
    box0->getShape(box0, &box0Shape);
    box0->getSize(box0, &box0Size);
    printf(
        "box0Size=%d, isEmpty=%d, box0Shape=%d\n",
        box0Size,
        isEmpty,
        box0Shape
    );

    puts("Storing a string value in box0.");
    char * stringWriteValue = "Hello, world!";
    char stringReadValue[32] = {0};
    box0->storeString(box0, stringWriteValue);
    box0->readString(box0, stringReadValue, 32);
    printf("stringReadValue=%s\n", stringReadValue);

    box0->isEmpty(box0, &isEmpty);
    box0->getShape(box0, &box0Shape);
    box0->getSize(box0, &box0Size);
    printf(
        "box0Size=%d, isEmpty=%d, box0Shape=%d\n",
        box0Size,
        isEmpty,
        box0Shape
    );

    puts("Resetting box0.");
    box0->reset(box0);

    box0->isEmpty(box0, &isEmpty);
    box0->getShape(box0, &box0Shape);
    box0->getSize(box0, &box0Size);
    printf(
        "box0Size=%d, isEmpty=%d, box0Shape=%d\n",
        box0Size,
        isEmpty,
        box0Shape
    );

    puts("Deleting box0.");
    box0->destroy(&box0);
    printf("box0 = %p\n", box0);

    return 0;
}
