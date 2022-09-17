#include "control.h"
#include "symbol.h"
#include "function.h"
#include "cons.h"
#include <setjmp.h>
#include <string.h>

typedef struct stack_frame_rack *stack_frame_rack;

struct stack_frame_rack
{
  struct rack prefix;
  jmp_buf buffer;
  object name;
  object arguments;
};

static int stack_frame_rack_size = sizeof(struct stack_frame_rack);

object dynamic_environment;
object control_stack;

static object return_values;

object
call(object function, object arguments)
{
  jmp_buf buffer;
  if(setjmp(buffer) == 0)
    {
      object frame = make_object();
      stack_frame_rack r = (stack_frame_rack) make_rack(stack_frame_rack_size);
      set_rack_of(frame, (rack) r);
      entry_point e = entry(function);
      object static_environment = environment(function);
      memcpy(&(r -> buffer), &buffer, sizeof(jmp_buf));
      r -> name = symbol_nil;
      r -> arguments = arguments;
      control_stack = c_function_cons(frame, control_stack);
      (*e)(static_environment, arguments);
      assert(0);
    }
  else
    {
      control_stack = c_function_cdr(control_stack);
      return return_values;
    }
}

object
named_call(object function_name, object arguments)
{
  return call(symbol_slot_function(function_name), arguments);
}

void
ret(object values)
{
  object frame = c_function_car(control_stack);
  stack_frame_rack r = (stack_frame_rack) rack_of(frame);
  control_stack = c_function_cdr(control_stack);
  return_values = values;
  longjmp(r -> buffer, 1);
}

int control_initialized_p = 0;

void ensure_control_initialized(void)
{
  if(control_initialized_p) return;
  ensure_symbol_initialized();
  dynamic_environment = symbol_nil;
  control_stack = symbol_nil;
  control_initialized_p = 1;
}

/* At the moment, we don't do anything here.  Later, when we have
   functions such as LIST-LENGTH, we can activate this function. */
void
check_argument_count(__attribute__((unused)) object arguments,
                     __attribute__((unused)) int min,
                     __attribute__((unused))int max)
{
  /*
  if(count < min)
    named_call(symbol_error,
               c_function_cons(data_and_control_flow_symbol_too_few_arguments, symbol_nil));
  else if (count > max)
    named_call(symbol_error,
               c_function_cons(data_and_control_flow_symbol_too_many_arguments, symbol_nil));
  */
}
