#include "ratio.h"
#include "symbol.h"
#include <gmp.h>

DEFINE_CLASS(class_ratio);

static int ratio_initialized_p = 0;

void
ensure_ratio_initialized(void)
{
  if(ratio_initialized_p) return;
  ratio_initialized_p = 1;
};

typedef struct ratio_rack *ratio_rack;

struct ratio_rack
{
  struct rack prefix;
  mpq_t value;
};

static int ratio_rack_size = sizeof(struct ratio_rack);

object
c_function_ratiop(object maybe_ratio)
{
  return class_of(maybe_ratio) == class_ratio ? symbol_t : symbol_nil;
}

object
c_function_binary_add_ratio(object augend, object addend)
{
  object obj = (object) malloc(header_size);
  ratio_rack r = (ratio_rack) malloc(ratio_rack_size);
  assert(c_function_ratiop(augend) == symbol_t);
  assert(c_function_ratiop(addend) == symbol_t);
  set_class_of(obj, class_ratio);
  set_rack_of(obj, (rack) r);
  mpq_init(r -> value);
  mpq_add(r -> value,
          ((ratio_rack) rack_of(augend)) -> value,
          ((ratio_rack) rack_of(addend)) -> value);
  return obj;
}

object
c_function_binary_subtract_ratio(object minuend, object subtrahend)
{
  object obj = (object) malloc(header_size);
  ratio_rack r = (ratio_rack) malloc(ratio_rack_size);
  assert(c_function_ratiop(minuend) == symbol_t);
  assert(c_function_ratiop(subtrahend) == symbol_t);
  set_class_of(obj, class_ratio);
  set_rack_of(obj, (rack) r);
  mpq_init(r -> value);
  mpq_sub(r -> value,
          ((ratio_rack) rack_of(minuend)) -> value,
          ((ratio_rack) rack_of(subtrahend)) -> value);
  return obj;
}

object
c_function_binary_multiply_ratio(object multiplicand, object multiplier)
{
  object obj = (object) malloc(header_size);
  ratio_rack r = (ratio_rack) malloc(ratio_rack_size);
  assert(c_function_ratiop(multiplicand) == symbol_t);
  assert(c_function_ratiop(multiplier) == symbol_t);
  set_class_of(obj, class_ratio);
  set_rack_of(obj, (rack) r);
  mpq_init(r -> value);
  mpq_mul(r -> value,
          ((ratio_rack) rack_of(multiplicand)) -> value,
          ((ratio_rack) rack_of(multiplier)) -> value);
  return obj;
}

object
c_function_binary_divide_ratio(object dividend, object divisor)
{
  object obj = (object) malloc(header_size);
  ratio_rack r = (ratio_rack) malloc(ratio_rack_size);
  assert(c_function_ratiop(dividend) == symbol_t);
  assert(c_function_ratiop(divisor) == symbol_t);
  set_class_of(obj, class_ratio);
  set_rack_of(obj, (rack) r);
  mpq_init(r -> value);
  mpq_div(r -> value,
          ((ratio_rack) rack_of(dividend)) -> value,
          ((ratio_rack) rack_of(divisor)) -> value);
  return obj;
}

object
c_function_negate_ratio(object ratio)
{
  object obj = (object) malloc(header_size);
  ratio_rack r = (ratio_rack) malloc(ratio_rack_size);
  assert(c_function_ratiop(ratio) == symbol_t);
  set_class_of(obj, class_ratio);
  set_rack_of(obj, (rack) r);
  mpq_init(r -> value);
  mpq_neg(r -> value, ((ratio_rack) rack_of(ratio)) -> value);
  return obj;
}
