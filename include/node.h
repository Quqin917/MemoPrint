#ifndef NODE_H
#define NODE_H

typedef union {
  int data_i;
  double data_b;
  char data_c;
} obj_node;

typedef struct {
  obj_node value_;
} node;

#endif  // !NODE_H
