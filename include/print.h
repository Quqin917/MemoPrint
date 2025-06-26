#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h> // For va_list, va_start(), va_arg()
#include <stdio.h>  // For FILE, fprintf()

#define __CONTOKEN(A, B) A##B
#define __CAT(A) #A

#define __PRINT_ARRAY_IMPL(fd, T, format)                                     \
  do                                                                          \
  {                                                                           \
    size_t n = size / sizeof(T);                                              \
    T *val = va_arg(va, T *);                                                 \
                                                                              \
    for (size_t i = 0; i < n; i++)                                            \
    {                                                                         \
      fprintf(fd, format, val[i]);                                            \
    }                                                                         \
  } while (0);

void __print_array_func (FILE *fd, size_t count, unsigned short types[], ...)
{
  va_list va;
  va_start(va, types);

  for (size_t i = 0; i < count; i++)
  {
    char type = types[i] & 0x1F;
    char size = types[i] >> 5;

    switch (type)
    {
    case 2: // Char array type
      __PRINT_ARRAY_IMPL(fd, char, "%c ");
      break;

    case 8: // Int array type
      __PRINT_ARRAY_IMPL(fd, int, "%i ");
      break;

    case 9: // String array type
      __PRINT_ARRAY_IMPL(fd, char *, "%s ");
      break;

    default: fprintf(stderr, "Unsupported %d, %d\n", size, type); break;
    }
    fprintf(fd, "\n");
  }
  va_end(va);
}

void __print_func (FILE *fd, size_t count, unsigned short types[], ...)
{
  va_list va;
  va_start(va, types);

  for (size_t i = 0; i < count; i++)
  {
    if (i > 0) fprintf(fd, " ");
    char type = types[i] & 0x1F;
    char size = types[i] >> 5;

    // fprintf(fd, "%d ", type);
    switch (type)
    {
    case 1: // Double and Float type
      fprintf(fd, "%f", va_arg(va, double));
      break;

    case 2: // String type
      fprintf(fd, "%s", va_arg(va, char *));
      break;

    case 3: // Char type
      fprintf(fd, "%c", va_arg(va, int));
      break;

    case 4: // Int type
      fprintf(fd, "%i", va_arg(va, int));
      break;

    case 5: // Unsigned Int type
      fprintf(fd, "%i", va_arg(va, unsigned int));
      break;

    case 6: // Unsigned Long type
      fprintf(fd, "%lu", va_arg(va, unsigned long));
      break;

    default: fprintf(stderr, "Unsupported %d, %d\n", size, type); break;
    }
  }

  va_end(va);
}

#define fprint(fd, ...)                                                       \
  do                                                                          \
  {                                                                           \
    size_t count = __COUNT_ARGS(__VA_ARGS__);                                 \
    unsigned short stack[count], *pointer = stack + count;                    \
                                                                              \
    __TYPE_ARGS(__VA_ARGS__);                                                 \
    __print_func(fd, count, pointer, __VA_ARGS__);                            \
  } while (0);

#define fprint_array(fd, ...)                                                 \
  do                                                                          \
  {                                                                           \
    size_t count = __COUNT_ARGS(__VA_ARGS__);                                 \
    unsigned short stack[count], *pointer = stack + count;                    \
                                                                              \
    __TYPE_ARGS(__VA_ARGS__);                                                 \
    __print_array_func(fd, count, pointer, __VA_ARGS__);                      \
  } while (0);

#define print(...) fprint(stdout, "", ##__VA_ARGS__)
#define print_array(...) fprint_array(stdout, "", ##__VA_ARGS__)

#endif // !PRINT_H
