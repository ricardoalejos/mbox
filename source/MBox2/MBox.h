#ifndef _MBOX_MBOX_H_
#define _MBOX_MBOX_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#include "MBox2/Error.h"
#include "MBox2/Shape.h"

struct MBox_Box;
struct MBox_List;
struct MBox_Dictionary;

typedef enum MBox_Error (*MBox_listMapCallback)(struct MBox_Box * box, void * args);
typedef enum MBox_Error (*MBox_dictMapCallback)(struct MBox_Box * key, struct MBox_Box * value, void * args);

enum MBox_Error MBox_getLastBoxError(struct MBox_Box * box);
enum MBox_Error MBox_clearLastBoxError(struct MBox_Box * box);
size_t MBox_getBoxContentSize(struct MBox_Box * box);
struct MBox_Box * MBox_cloneBox(struct MBox_Box * box);
enum MBox_Error MBox_copyBoxContent(struct MBox_Box * dst, struct MBox_Box src);
enum MBox_Error MBox_clearBox(struct MBox_Box * box);
enum MBox_Error MBox_destroyBox(struct MBox_Box ** box);
enum MBox_Shape MBox_getBoxShape(struct MBox_Box * box);
bool MBox_areBoxContentsEqual(struct MBox_Box * boxA, struct MBox_Box * boxB);

uint64_t MBox_getCopyOfUnsignedIntegerFromBox(struct MBox_Box * box);
enum MBox_Error MBox_putUnsignedIntegerIntoBox(struct MBox_Box * box, uint64_t value);
int64_t MBox_getCopyOfIntegerFromBox(struct MBox_Box * box);
enum MBox_Error MBox_putIntegerIntoBox(struct MBox_Box * box, int64_t value);
bool MBox_getCopyOfBooleanFromBox(struct MBox_Box * box);
enum MBox_Error MBox_putBooleanIntoBox(struct MBox_Box * box, bool value);
double MBox_getCopyOfDoubleFromBox(struct MBox_Box * box);
enum MBox_Error MBox_putDoubleIntoBox(struct MBox_Box * box, double value);
char * MBox_getStringFromBox(struct MBox_Box * box);
char * MBox_getCopyOfStringFromBox(struct MBox_Box * box);
enum MBox_Error MBox_putStringIntoBox(struct MBox_Box * box, const char * fmt, ...);
void * MBox_getCopyOfReferenceFromBox(struct MBox_Box * box);
enum MBox_Error MBox_putReferenceIntoBox(struct MBox_Box * box, void * value);
struct MBox_List * MBox_getCopyOfListReferenceFromBox(struct MBox_Box * box);
enum MBox_Error MBox_putListReferenceIntoBox(struct MBox_Box * box, struct MBox_List * value);
struct MBox_Dictionary * MBox_getCopyOfDictionaryReferenceFromBox(struct MBox_Box * box);
enum MBox_Error MBox_putDictionaryReferenceIntoBox(struct MBox_Box * box, struct MBox_Dictionary * value);

struct MBox_Box * MBox_getBoxFromList(struct MBox_List * list, int index);
int MBox_getIndexOfSimilarBoxInList(struct MBox_List * list, struct MBox_Box * box);
struct MBox_Box * MBox_popBoxFromList(struct MBox_List * list, int index);
enum MBox_Error MBox_removeBoxFromList(struct MBox_List * list, int index);
bool MBox_isSimilarBoxInList(struct MBox_List * list, struct MBox_Box * box);
enum MBox_Error MBox_removeSimilarBoxFromList(struct MBox_List * list, struct MBox_Box * box);
enum MBox_Error MBox_appendSimilarBoxFromList(struct MBox_List * list, struct MBox_Box * box);
enum MBox_Error MBox_insertSimilarBoxFromList(struct MBox_List * list, int index, struct MBox_Box * box);
struct MBox_Box * MBox_appendEmptyBoxToList(struct MBox_List * list);
struct MBox_Box * MBox_insertEmptyBoxToList(struct MBox_List * list, int index);
size_t MBox_getListLength(struct MBox_List * list);
bool MBox_isListEmpty(struct MBox_List * list);
enum MBox_Error MBox_getLastListError(struct MBox_List * list);
enum MBox_Error MBox_extendList(struct MBox_List * dst, struct MBox_List * src);
enum MBox_Error MBox_mapList(struct MBox_List * list, MBox_listMapCallback function, void * args);
enum MBox_Error MBox_clearLastListError(struct MBox_List * list);

struct MBox_Box * MBox_getBoxFromDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key);
struct MBox_Box * MBox_popBoxFromDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key);
bool MBox_isKeyInDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key);
enum MBox_Error MBox_removeBoxFromDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key);
size_t MBox_getDictionaryLength(struct MBox_Dictionary * dict);
bool MBox_isDictionaryEmpty(struct MBox_Dictionary * dict);
enum MBox_Error MBox_getLastDictionaryError(struct MBox_Dictionary * dict);
struct MBox_List * MBox_createDictionaryKeyList(struct MBox_Dictionary * dict);
enum MBox_Error MBox_addSimilarBoxToDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key, struct MBox_Box * box);
struct MBox_Box * MBox_addEmptyBoxToDictionary(struct MBox_Dictionary * dict, struct MBox_Box * key);
enum MBox_Error MBox_extendDictionary(struct MBox_Dictionary * dst, struct MBox_Dictionary * src);
enum MBox_Error MBox_mapDictionary(struct MBox_Dictionary * dict, MBox_dictMapCallback function, void * args);
enum MBox_Error MBox_clearLastDictionaryError(struct MBox_Dictionary * dict);

#endif
