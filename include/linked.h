#ifndef LINKED_H
#define LINKED_H

// TODO: Make a generic for user to choose different data types
//      Ways to solve this problem:
//      1. Macro
//      2. Union
//      3. Enums

#include <stddef.h> // For size_t
#include <stdint.h>

#include "node.h" // For node

typedef enum
{
  INT,
  CHAR,
  STRING,
  DOUBLE,
} dataType;

typedef struct
{
  dataType type_;
  node *head_;
  node *tail_;
  size_t size_;
} linkedList;

typedef enum
{
  SUCCESS = 0,
  ERROR_TYPE_MISMATCH = 1,
  ERROR_MEMORY_ALLOCATION_FAILED = 2,
} ErrorCode;

linkedList _createLinked(dataType type);

void appendHeadLinked(linkedList *src, intptr_t data);
void appendTailLinked(linkedList *src, intptr_t data);
void insertGivenPos(linkedList *src, intptr_t data, size_t pos);

void printLinkedList(linkedList *src);

#endif // !LINKED_H
