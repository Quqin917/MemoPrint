//  Copyright (c) 2025 Quqin

#include <stdio.h>

#include "arena.h"
#include "linked.h"

Arena arena = {0};

int main (void)
{
  linkedList linked = _createLinked(INT);

  appendHeadLinked(&linked, 1);

  appendTailLinked(&linked, 3);

  insertGivenPos(&linked, 2, 1);

  printLinkedList(&linked);

  printf("size of linked list: %d\n", (int)linked.size_);
  printf("types of data: %d \n", linked.type_);

  freeArena(&arena);

  return 0;
}
