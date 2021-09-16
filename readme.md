# Memory Boxes

This is a framework for creating intermediate representations of serializable/deserializable objects. This means that the abstractions contained in this module may serve as a way to present to the application layer an uniform interface to data in popular formats like JSON, XML, databases, and etcetera (when used together with libraries that parse such formats like "json-c", "libxml2", "sqlite3", and so on).

The Memory Box ("MBox" for short; or just "box" in this text) is the foundational abstraction of this module. Boxes have three attributes that describe their content:

- its size in bytes,
- its "shape" (its format, datatype, an indication of how to interpret the content),
- its data: the byte values that compose the content.

Boxes allow us hiding the data types of their content, allowing us to create type-agnostic abstractions. In this module we have included two abstractions that explot that benefit:

- lists, and
- dictionaries.

## Build instructions

For building this project you will need CMake >= 3.16. Since it only uses standard C libraries, it will build for whatever system. However, in its current version it requires the system to be able to allocate memory dynamically (it uses malloc(), realloc(), free() from "stdlib.h").

For building, open a terminal in the root directory of this repository and run:

```
source setenv.sh
mbox_configure
mbox_build
```

Once you have run these commands:

- the library should be available in the out/lib subdirectory. 
- the public header files should be available in the out/include subdirectory.
- the test applications should be available in the out/bin subdirectory.

## Supported shapes

- MBox_Shape_UNSIGNED_64B_INTEGER: Contains a 64 bit signed integer.
- MBox_Shape_SIGNED_64B_INTEGER: Contains a 64 bit unsigned integer.
- MBox_Shape_DOUBLE: Contains a 64 bit floating point number.
- MBox_Shape_STRING: Contains a C-style (null-terminated) string.
- MBox_Shape_BOOLEAN: Contains a "bool" value.
- MBox_Shape_LIST_REFERENCE: A pointer to a list.
- MBox_Shape_DICTIONARY_REFERENCE: A pointer to a dictionary.
- MBox_Shape_REFERENCE: Contains a generic pointer.
- MBox_Shape_CUSTOM: Contains an array of bytes with a custom data structure.
- MBox_Shape_NULL: The shape of an empty memory box.

## Collections

### Lists

Example of use at [SimpleListTest.c](source/applications/SimpleListTest.c).

### Dictionaries

Example of use at [SimpleDictionaryTest.c](source/applications/SimpleDictionaryTest.c).
