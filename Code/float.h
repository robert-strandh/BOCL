#ifndef FLOAT_H
#define FLOAT_H

#include "object.h"

extern void ensure_float_initialized(void);
extern object c_function_floatp(object maybe_float);
extern object c_function_float_to_float(double dfloat);
extern object c_function_binary_add_float(object augend, object addend);
extern object c_function_binary_subtract_float(object minuend, object subtrahend);
extern object c_function_binary_multiply_float(object multiplicand, object multiplier);
extern object c_function_binary_divide_float(object dividend, object divisor);
extern object c_function_negate_float(object obj);
extern object c_function_sin_float(object obj);
extern object c_function_cos_float(object obj);
extern object c_function_tan_float(object obj);
extern object c_function_asin_float(object obj);
extern object c_function_acos_float(object obj);
extern object c_function_atan_float(object obj);

extern object class_float;

#endif
