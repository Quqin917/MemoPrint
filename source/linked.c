#include "linked.h"
#include "node.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

linkedList _createLinked (dataType type)
{
  linkedList new;

  new.head_ = NULL;
  new.tail_ = NULL;
  new.type_ = type;
  new.size_ = 0;

  return new;
}

void appendHeadLinked (linkedList *src, intptr_t data_)
{
  node *new = (node *)createNode(data_);

  if (src->tail_ == NULL)
  {
    src->tail_ = new;
    src->head_ = src->tail_;
  }
  else
  {
    new->next_ = src->head_;
    src->head_ = new;
  }
  src->size_ += 1;
}

void appendTailLinked (linkedList *src, intptr_t data_)
{
  node *new = (node *)createNode(data_);

  if (src->tail_ == NULL)
  {
    src->tail_ = new;
    src->head_ = src->tail_;
  }
  else
  {
    src->tail_->next_ = new;
    src->tail_ = new;
  }
  src->size_ += 1;
}

void printLinkedList (linkedList *src)
{
  node *cur = src->head_;
  while (cur != NULL)
  {
    printf("%d\n", (int)cur->data_);
    cur = cur->next_;
  }
}

#include <assert.h>

void insertGivenPos (linkedList *src, intptr_t data_, size_t pos)
{
  if (pos > src->size_) { return; }

  if (pos == 0)
  {
    appendHeadLinked(src, data_);
    return;
  }
  else if (pos == src->size_)
  {
    appendTailLinked(src, data_);
    return;
  }

  node *new = (node *)createNode(data_);
  node *prev = {0};

  node *curr = src->head_;
  for (int i = 0; i < pos; ++i)
  {
    prev = curr;
    curr = curr->next_;
  }

  new->next_ = curr;
  prev->next_ = new;

  src->size_ += 1;
}
