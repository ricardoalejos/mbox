#ifndef _MBOX_DISPLAY_H_
#define _MBOX_DISPLAY_H_

#include "MBox/MBox.h"
#include "MBox/List.h"
#include "MBox/Dictionary.h"

void MBox_displayMBox(struct MBox_MBox * mbox, char * prefix, char * suffix);
void MBox_displayList(struct MBox_List * list);
void MBox_displayDictionary(struct MBox_Dictionary * dictionary);

#endif
