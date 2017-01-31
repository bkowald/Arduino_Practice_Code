
#include "file2.h"

// heres a function in a different file

int foo() {
  static int v = 0;
  return v++;
}
