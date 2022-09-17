#include "function.h"

typedef struct function_rack *function_rack;

struct function_rack
{
  struct rack prefix;
  entry_point entry;
  object static_environment;
};

static int function_rack_size = sizeof(struct function_rack);

entry_point
entry(object function)
{
  function_rack r = (function_rack) rack_of(function);
  return r -> entry;
}

object
environment(object function)
{
  function_rack r = (function_rack) rack_of(function);
  return r -> static_environment;
}

int function_initialized_p = 0;

void ensure_function_initialized(void)
{
  if(function_initialized_p) return;

  function_initialized_p = 1;
}
