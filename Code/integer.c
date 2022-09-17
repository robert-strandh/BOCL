#include "integer.h"
#include "symbol.h"
#include <gmp.h>

DEFINE_CLASS(class_integer);

static int integer_initialized_p = 0;

object integer_0;
object integer_1;

void
ensure_integer_initialized(void)
{
  if(integer_initialized_p) return;
  integer_0 = c_function_integer_to_integer(0);
  integer_1 = c_function_integer_to_integer(1);
  integer_initialized_p = 1;
};

typedef struct integer_rack *integer_rack;

struct integer_rack
{
  struct rack prefix;
  mpz_t value;
};

static int integer_rack_size = sizeof(struct integer_rack);

object
c_function_integerp(object maybe_integer)
{
  return class_of(maybe_integer) == class_integer ? symbol_t : symbol_nil;
}

object
c_function_integer_to_integer(signed long int c_integer)
{
  object obj = (object) malloc(header_size);
  integer_rack r = (integer_rack) malloc(integer_rack_size);
  set_class_of(obj, class_integer);
  set_rack_of(obj, (rack) r);
  mpz_init(r -> value);
  mpz_set_si(r -> value, c_integer);
  return obj;
}

signed long int
c_function_integer_to_c_integer(object integer)
{
  assert(c_function_integerp(integer) == symbol_t);
  return mpz_get_si(((integer_rack) rack_of(integer)) -> value);
}

object
c_function_binary_add_integer(object augend, object addend)
{
  object obj = (object) malloc(header_size);
  integer_rack r = (integer_rack) malloc(integer_rack_size);
  assert(c_function_integerp(augend) == symbol_t);
  assert(c_function_integerp(addend) == symbol_t);
  set_class_of(obj, class_integer);
  set_rack_of(obj, (rack) r);
  mpz_init(r -> value);
  mpz_add(r -> value,
          ((integer_rack) rack_of(augend)) -> value,
          ((integer_rack) rack_of(addend)) -> value);
  return obj;
}

object
c_function_binary_subtract_integer(object minuend, object subtrahend)
{
  object obj = (object) malloc(header_size);
  integer_rack r = (integer_rack) malloc(integer_rack_size);
  assert(c_function_integerp(minuend) == symbol_t);
  assert(c_function_integerp(subtrahend) == symbol_t);
  set_class_of(obj, class_integer);
  set_rack_of(obj, (rack) r);
  mpz_init(r -> value);
  mpz_sub(r -> value,
          ((integer_rack) rack_of(minuend)) -> value,
          ((integer_rack) rack_of(subtrahend)) -> value);
  return obj;
}

object
c_function_binary_multiply_integer(object multiplicand, object multiplier)
{
  object obj = (object) malloc(header_size);
  integer_rack r = (integer_rack) malloc(integer_rack_size);
  assert(c_function_integerp(multiplicand) == symbol_t);
  assert(c_function_integerp(multiplier) == symbol_t);
  set_class_of(obj, class_integer);
  set_rack_of(obj, (rack) r);
  mpz_init(r -> value);
  mpz_mul(r -> value,
          ((integer_rack) rack_of(multiplicand)) -> value,
          ((integer_rack) rack_of(multiplier)) -> value);
  return obj;
}

object
c_function_binary_divide_floor_quotient_integer(object dividend, object divisor)
{
  object obj = (object) malloc(header_size);
  integer_rack r = (integer_rack) malloc(integer_rack_size);
  assert(c_function_integerp(dividend) == symbol_t);
  assert(c_function_integerp(divisor) == symbol_t);
  set_class_of(obj, class_integer);
  set_rack_of(obj, (rack) r);
  mpz_init(r -> value);
  mpz_fdiv_q(r -> value,
             ((integer_rack) rack_of(dividend)) -> value,
             ((integer_rack) rack_of(divisor)) -> value);
  return obj;
}

object
c_function_binary_divide_floor_remainder_integer(object dividend, object divisor)
{
  object obj = (object) malloc(header_size);
  integer_rack r = (integer_rack) malloc(integer_rack_size);
  assert(c_function_integerp(dividend) == symbol_t);
  assert(c_function_integerp(divisor) == symbol_t);
  set_class_of(obj, class_integer);
  set_rack_of(obj, (rack) r);
  mpz_init(r -> value);
  mpz_fdiv_r(r -> value,
             ((integer_rack) rack_of(dividend)) -> value,
             ((integer_rack) rack_of(divisor)) -> value);
  return obj;
}

object
c_function_negate_integer(object integer)
{
  object obj = (object) malloc(header_size);
  integer_rack r = (integer_rack) malloc(integer_rack_size);
  assert(c_function_integerp(integer) == symbol_t);
  set_class_of(obj, class_integer);
  set_rack_of(obj, (rack) r);
  mpz_init(r -> value);
  mpz_neg(r -> value, ((integer_rack) rack_of(integer)) -> value);
  return obj;
}

object
c_function_one_plus_integer(object integer)
{
  return c_function_binary_add_integer(integer, integer_1);
}

object
c_function_one_minus_integer(object integer)
{
  return c_function_binary_subtract_integer(integer, integer_1);
}

object
c_function_binary_less_integer(object x, object y)
{
  assert(c_function_integerp(x) == symbol_t);
  assert(c_function_integerp(y) == symbol_t);
  {
    return mpz_cmp(((integer_rack) rack_of(x)) -> value,
                   ((integer_rack) rack_of(y)) -> value)
      < 0 ? symbol_t : symbol_nil;
  }
}

object
c_function_binary_equal_integer(object x, object y)
{
  assert(c_function_integerp(x) == symbol_t);
  assert(c_function_integerp(y) == symbol_t);
  {
    return mpz_cmp(((integer_rack) rack_of(x)) -> value,
                   ((integer_rack) rack_of(y)) -> value)
      == 0 ? symbol_t : symbol_nil;
  }
}

object
c_function_binary_not_greater(object x, object y)
{
  assert(c_function_integerp(x) == symbol_t);
  assert(c_function_integerp(y) == symbol_t);
  {
    return mpz_cmp(((integer_rack) rack_of(x)) -> value,
                   ((integer_rack) rack_of(y)) -> value)
      <= 0 ? symbol_t : symbol_nil;
  }
}  

object
c_function_zerop_integer(object integer)
{
  assert(c_function_integerp(integer) == symbol_t);
  return c_function_binary_equal_integer(integer, integer_0);
}

object
c_function_plusp_integer(object integer)
{
  assert(c_function_integerp(integer) == symbol_t);
  return c_function_binary_less_integer(integer_0, integer);
}

object
c_function_minusp_integer(object integer)
{
  assert(c_function_integerp(integer) == symbol_t);
  return c_function_binary_less_integer(integer, integer_0);
}
