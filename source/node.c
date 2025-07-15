#include "node.h"
#include "arena.h"

#include <stddef.h>
#include <stdint.h>

extern Arena arena;

void *createNode (intptr_t data)
{
  node *new = (node *)arenaAllocation(&arena, sizeof(node));

  new->data_ = data;
  new->next_ = NULL;

  return new;
}
