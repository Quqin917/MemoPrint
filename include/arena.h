#ifndef ARENA_H
#define ARENA_H

#include <stddef.h> // For size_t
#include <stdint.h> // For intptr_t

#define region_inline static inline

#ifndef ARENA_ASSERT
#include <assert.h> // for assert()
#define ARENA_ASSERT assert
#endif // !ARENA_ASSERT

typedef struct region
{
  struct region *next_;
  size_t capacity_;
  size_t count_;
  intptr_t data_[];
} Region;

Region *create_region(size_t capacity);
void free_region(Region *a);

typedef struct
{
  Region *head_;
  Region *tail_;
  int *flags_;
} Arena;

void *arena_alloc(Arena *arena, size_t size);
void *arena_memcpy(void *dest, const void *src, size_t n);
void *
arena_realloc(Arena *arena, void *oldptr, size_t old_size, size_t new_size);
void *arena_at(Arena *arena, size_t iterator, size_t item_size);

void free_arena(Arena *arena);

#include <stdlib.h> // For malloc() and free()

Region *create_region (size_t capacity)
{
  // Multiply the rounded byte count by uintptr_t then add region size
  size_t data_size = sizeof(Region) + sizeof(uintptr_t) * capacity;

  Region *region = malloc(data_size);
  ARENA_ASSERT(region);

  // Initialize default member
  region->next_ = NULL;
  region->capacity_ = capacity;
  region->count_ = 0;

  return region;
}

void free_region (Region *r) { free(r); }

#define ARENA_DEFAULT_SIZE 8 * 1024

void *arena_alloc (Arena *arena, size_t size_in_bytes)
{
  // Rounds up the byte count to the nearest multiple of uintptr_t
  size_t size = (size_in_bytes + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);

  // The first initialization of arena
  if (arena->tail_ == NULL)
  {
    ARENA_ASSERT(arena->head_ == NULL);
    arena->tail_ = create_region(size);

    arena->head_ = arena->tail_;
    arena->flags_ = (int *)1;
  }

  // Move to the last region
  while (arena->tail_->count_ + size > arena->tail_->capacity_
         && arena->tail_->next_ != NULL)
  {
    arena->tail_ = arena->tail_->next_;
  }

  // Append new region to existing arena
  if (arena->tail_->count_ + size > arena->tail_->capacity_)
  {
    ARENA_ASSERT(arena->tail_->next_ == NULL);
    arena->tail_->next_ = create_region(size);
    arena->tail_ = arena->tail_->next_;
  }

  void *result = &arena->tail_->data_[arena->tail_->count_];
  arena->tail_->count_ += size;

  return result;
}

void *
arena_realloc (Arena *arena, void *oldptr, size_t old_size, size_t new_size)
{
  if (new_size <= old_size) return oldptr;

  void *new_ptr = arena_alloc(arena, new_size);

  char *old_ptr_byte = (char *)oldptr;
  char *new_ptr_byte = (char *)new_ptr;

  for (size_t i = 0; i < old_size; ++i)
    new_ptr_byte[i] = old_ptr_byte[i];

  return new_ptr;
}

void free_arena (Arena *r)
{
  Region *curr = r->head_;

  while (curr)
  {
    Region *curr_temp = curr;
    curr = curr->next_;

    free_region(curr_temp);
  }

  r->head_ = NULL;
  r->tail_ = NULL;
  r->flags_ = NULL;
}

void *arena_memcpy (void *dest, const void *src, size_t n)
{
  // Assigned data types to void
  char *d = dest;
  const char *s = src;

  // Copy every byte of src to dest
  for (; n; n--)
    *d++ = *s++;

  return dest;
}

void *region_at (void *data, size_t byte_offset)
{
  return (void *)((char *)data + byte_offset);
}

void *arena_at (Arena *arena, size_t offset, size_t item_size)
{
  Region *current = arena->head_;

  while (current != NULL)
  {
    size_t bytes_in_region = current->count_ * sizeof(uintptr_t);
    size_t iterator_region = offset * item_size;

    if (iterator_region < bytes_in_region)
    {
      return region_at(current->data_, iterator_region);
    }

    size_t item_in_region = bytes_in_region / item_size;
    offset -= item_in_region;

    current = current->next_;
  }

  return NULL;
}

#endif // !ARENA_H
