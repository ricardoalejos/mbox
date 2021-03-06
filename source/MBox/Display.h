#ifndef _MBOX_DISPLAY_H_
#define _MBOX_DISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "MBox/MBox.h"
#include "MBox/List.h"
#include "MBox/Dictionary.h"

void MBox_displayMBox(struct MBox_MBox * mbox);
void MBox_displayList(struct MBox_List * list);
void MBox_displayDictionary(struct MBox_Dictionary * dictionary);

#ifdef __cplusplus
} // Extern "C"
#endif

#endif
