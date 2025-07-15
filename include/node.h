#ifndef NODE_H
#define NODE_H

#include <stddef.h>
#include <stdint.h>

typedef struct node node;

struct node
{
  struct node *next_;
  intptr_t data_;
};

void *createNode(intptr_t data);

#endif // !NODE_H
