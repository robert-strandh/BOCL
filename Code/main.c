#include <stdio.h>

#include "object.h"
#include "character.h"
#include "string.h"
#include "package.h"
#include "symbol.h"
#include "integer.h"
#include "stream.h"
#include "cons.h"
#include "print.h"
#include "control.h"
#include "function.h"

int main(void)
{
  ensure_string_initialized();
  ensure_package_initialized();
  ensure_symbol_initialized();
  ensure_integer_initialized();
  ensure_stream_initialized();
  ensure_function_initialized();
  ensure_control_initialized();
  object x = c_function_integer_to_integer(234);
  object y = c_function_integer_to_integer(345);
  object z = c_function_binary_add_integer(x, y);
  printf("The sum is %ld\n", c_function_integer_to_c_integer(z));
  c_function_print(c_function_cons(symbol_if, c_function_cons(symbol_block, symbol_nil)), standard_output);
  printf("\n");
  return 0;
}
