#include "arena.h"
#include "print.h"

#define cast(...)

typedef struct
{
  char *data_;
  size_t capacity_;
  size_t count_;
} Array;

int main (void)
{
  Arena arena = {0};

  Array arr = {0};

  int tmp[5] = {1, 2, 3, 4, 5};

  arr.data_ = cast(arr.data_)
    arena_realloc(&arena, &arr, arr.capacity_, 5 * sizeof(int));
  arr.capacity_ = 5 * sizeof(int);

  arena_memcpy(arr.data_, tmp, 5 * sizeof(int));
  arr.count_ = 5;

  // char tmp[5] = {'a', 'b', 'c', 'd', 'e'};

  // arr.data_ = cast(arr.data_)
  //   arena_realloc(&arena, &arr, arr.capacity_, 5 * sizeof(char));
  // arr.capacity_ = 5 * sizeof(char);
  //
  // arena_memcpy(arr.data_, tmp, 5 * sizeof(char));
  // arr.count_ = 5;

  for (size_t i = 0; i < arr.count_; i++)
  {
    int *val = (int *)arena_at(&arena, i, sizeof(int));
    print(*val);
  }
  print("\n");

  free_arena(&arena);

  return 0;
}
