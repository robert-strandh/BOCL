#include "assert.h"
#include "symbol.h"

void
c_function_assert(object obj)
{
  assert(obj == symbol_t);
}
