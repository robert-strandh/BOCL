#ifndef RATIO_H
#define RATIO_H

#include "object.h"

extern void ensure_ratio_initialized(void);
extern object c_function_ratiop(object maybe_ratio);
extern object c_function_binary_add_ratio(object augend, object addend);
extern object c_function_binary_subtract_ratio(object minuend, object subtrahend);
extern object c_function_binary_multiply_ratio(object multiplicand, object multiplier);
extern object c_function_binary_divide_ratio(object multiplicand, object multiplier);
extern object c_function_negate_ratio(object ratio);

extern object class_integer;

#endif
