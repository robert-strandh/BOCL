#ifndef CHARACTER_H
#define CHARACTER_H

#include "object.h"

extern void ensure_character_initialized(void);
extern object c_function_char_to_character(char c);
extern char c_function_character_to_c_char(object character);
extern object c_function_characterp(object maybe_character);
extern object c_function_char_equal_sign(object char1, object char2);
extern object c_function_char_not_equal_sign(object char1, object char2);
extern object c_function_char_less_than_sign(object char1, object char2);
extern object c_function_char_greater_than_sign(object char1, object char2);
extern object c_function_char_less_than_or_equal_sign(object char1, object char2);
extern object c_function_char_greater_than_or_equal_sign(object char1, object char2);
extern object c_function_char_equal(object char1, object char2);
extern object c_function_char_not_equal(object char1, object char2);
extern object c_function_char_lessp(object char1, object char2);
extern object c_function_char_greaterp(object char1, object char2);
extern object c_function_char_not_lessp(object char1, object char2);
extern object c_function_char_not_greaterp(object char1, object char2);
extern object c_function_char_upcase(object character);
extern object c_function_char_downcase(object character);
extern object c_function_upper_case_p(object character);
extern object c_function_lower_case_p(object character);
extern object c_function_both_case_p(object character);

extern object class_character;

#endif
