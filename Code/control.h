#ifndef CONTROL_H
#define CONTROL_H

#include "object.h"

void ensure_control_initialized(void);

extern object dynamic_environment;
extern object control_stack;

extern object call(object function, object arguments);
extern object named_call(object function_name, object arguments);
extern void ret(object values);
extern void check_argument_count(object arguments, int min, int max);

#endif
