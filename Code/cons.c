#include "cons.h"
#include "symbol.h"
#include "control.h"

DEFINE_CLASS(class_cons);

static int cons_initialized_p = 0;

void
ensure_cons_initialized(void)
{
  if(cons_initialized_p) return;
  cons_initialized_p = 1;
};

typedef struct cons_rack *cons_rack;

struct cons_rack
{
  struct rack prefix;
  object car;
  object cdr;
};

static int cons_rack_size = sizeof(struct cons_rack);

object
c_function_cons(object car, object cdr)
{
  object result = make_object();
  cons_rack r = (cons_rack) malloc(cons_rack_size);
  set_class_of(result, class_cons);
  set_rack_of(result, (rack) r);
  ((cons_rack) rack_of(result)) -> car = car;
  ((cons_rack) rack_of(result)) -> cdr = cdr;
  return result;
}

object
c_function_car(object cons)
{
  assert(c_function_consp(cons) == symbol_t);
  return ((cons_rack) rack_of(cons)) -> car;
}

object
c_function_cdr(object cons)
{
  assert(c_function_consp(cons) == symbol_t);
  return ((cons_rack) rack_of(cons)) -> cdr;
}

object
list1(object element)
{
  return c_function_cons(element, symbol_nil);
}

object
list2(object element1, object element2)
{
  return c_function_cons(element1, list1(element2));
}

object
list3(object element1, object element2, object element3)
{
  return c_function_cons(element1, list2(element2, element3));
}

object
list4(object element1, object element2, object element3, object element4)
{
  return c_function_cons(element1, list3(element2, element3, element4));
}

object
list5(object element1, object element2, object element3, object element4, object element5)
{
  return c_function_cons(element1, list4(element2, element3, element4, element5));
}

object
l_function_cons(__attribute__((unused)) object static_environment, object arguments)
{
  check_argument_count(arguments, 2, 2);
  return(c_function_cons(c_function_car(arguments), c_function_car(c_function_cdr(arguments))));
}

object
l_function_car(__attribute__((unused)) object static_environment, object arguments)
{
  check_argument_count(arguments, 1, 1);
  object argument = c_function_car(arguments);
  if(argument == symbol_nil)
    {
      return list1(symbol_nil);
    }
  else if(c_function_consp(argument) == symbol_t)
    {
      return list1(c_function_car(argument));
    }
  else
    return named_call(symbol_error,
                      list5(symbol_type_error,
                            keyword_datum,
                            argument,
                            keyword_expected_type,
                            symbol_list));
}

object
l_function_cdr(__attribute__((unused)) object static_environment, object arguments)
{
  check_argument_count(arguments, 1, 1);
  object argument = c_function_car(arguments);
  if(argument == symbol_nil)
    {
      return list1(symbol_nil);
    }
  else if(c_function_consp(argument) == symbol_t)
    {
      return list1(c_function_cdr(argument));
    }
  else
    return named_call(symbol_error,
                      list5(symbol_type_error,
                            keyword_datum,
                            argument,
                            keyword_expected_type,
                            symbol_list));
}

object
c_function_consp(object maybe_cons)
{
  return class_of(maybe_cons) == class_cons ? symbol_t : symbol_nil;
}

object
c_function_rplaca(object cons, object obj)
{
  assert(c_function_consp(cons) == symbol_t);
  ((cons_rack) rack_of(cons)) -> car = obj;
  return cons;
}

object
c_function_rplacd(object cons, object obj)
{
  assert(c_function_consp(cons) == symbol_t);
  ((cons_rack) rack_of(cons)) -> cdr = obj;
  return cons;
}
