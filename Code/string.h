#ifndef STRING_H
#define STRING_H

#include "object.h"

extern void ensure_string_initialized(void);

extern object c_function_make_string(object size, object initial_element);
extern object c_function_string_to_string(char *s);
extern object c_function_stringp(object maybe_string);
extern object c_function_char(object string, object index);
extern object c_function_setf_char(object character, object string, object index);
extern object c_function_string_total_length(object string);
extern object c_function_setf_string_total_length(object length, object string);
extern object c_function_string_fill_pointer(object string);
extern object c_function_setf_string_fill_pointer(object fill_pointer, object string);
extern object c_function_string_push_extend(object character, object string, object extension);
extern object c_function_string_equal_sign(object string1, object string2);

extern object class_string;

#endif
