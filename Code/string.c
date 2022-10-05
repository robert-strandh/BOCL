#include "string.h"
#include "character.h"
#include "symbol.h"
#include "integer.h"
#include "cons.h"
#include "assert.h"
#include <string.h>

DEFINE_CLASS(class_string);

static int string_initialized_p = 0;

void
ensure_string_initialized(void)
{
  if(string_initialized_p) return;
  ensure_character_initialized();
  string_initialized_p = 1;
}

typedef struct string_rack *string_rack;

struct string_rack
{
  struct rack prefix;
  object dimensions;
  object fill_pointer;
  object characters[0];
};

static int string_rack_size = sizeof(struct string_rack);

object
c_function_make_string(object size, object initial_element)
{
  assert(c_function_integerp(size) == symbol_t);
  assert(c_function_characterp(initial_element) == symbol_t);
  {
    int c_size = c_function_integer_to_c_integer(size);
    object result = (object) malloc(header_size);
    string_rack r = (string_rack) malloc(string_rack_size + c_size * sizeof(object));
    set_class_of(result, class_string);
    set_rack_of(result, (rack) r);
    for(int i = 0; i < c_size; i++)
    {
      object index = c_function_integer_to_integer(i);
      c_function_setf_char(initial_element, result, index);
    }
    r -> dimensions = c_function_cons(size, symbol_nil);
    r -> fill_pointer = size;
    return result;
  }
}
    
object
c_function_char(object string, object index)
{
  assert(c_function_stringp(string) == symbol_t);
  assert(c_function_integerp(index) == symbol_t);
  {
    object total_length = c_function_string_total_length(string);
    assert((c_function_binary_less_integer(index, total_length) == symbol_t) ||
           (c_function_binary_equal_integer(index, total_length) == symbol_t));
    {
      signed long int c_index = c_function_integer_to_c_integer(index);
      string_rack r = ((string_rack) rack_of(string));
      return r -> characters[c_index];
    }
  }
}

object
c_function_setf_char(object character, object string, object index)
{
  c_function_assert(c_function_characterp(character));
  c_function_assert(c_function_stringp(string));
  c_function_assert(c_function_integerp(index));
  {
    object total_length = c_function_string_total_length(string);
    assert((c_function_binary_less_integer(index, total_length) == symbol_t) ||
           (c_function_binary_equal_integer(index, total_length) == symbol_t));
    {
      signed long int c_index = c_function_integer_to_c_integer(index);
      string_rack r = ((string_rack) rack_of(string));
      r -> characters[c_index] = character;
    }
  }
  return character;
}

object
c_function_string_to_string(char *s)
{
  int length = strlen(s);
  object integer_length = c_function_integer_to_integer(length);
  object obj = (object) malloc(header_size);
  string_rack r = (string_rack) malloc(string_rack_size + length * sizeof(object));
  set_class_of(obj, class_string);
  set_rack_of(obj, (rack) r);
  for(int i = 0; i < length; i++)
    {
      object c = c_function_char_to_character(s[i]);
      r -> characters[i] = c;
    }
  r -> dimensions = c_function_cons(integer_length, symbol_nil);
  r -> fill_pointer = integer_length;
  return obj;
}

object
c_function_stringp(object maybe_string)
{
  return class_of(maybe_string) == class_string ? symbol_t : symbol_nil;
}

object
c_function_string_total_length(object string)
{
  assert(c_function_stringp(string) == symbol_t);
  {
    string_rack r = ((string_rack) rack_of(string));
    return c_function_car(r -> dimensions);
  }
}

object
c_function_string_fill_pointer(object string)
{
  assert(c_function_stringp(string) == symbol_t);
  {
    string_rack r = ((string_rack) rack_of(string));
    return r -> fill_pointer;
  }
}

object
c_function_string_push_extend(object character, object string, object extension)
{
  assert(c_function_characterp(character) == symbol_t);
  assert(c_function_stringp(string) == symbol_t);
  assert(c_function_integerp(extension) == symbol_t);
  {
    string_rack r = ((string_rack) rack_of(string));
    object length = c_function_car(r -> dimensions);
    signed long int c_length = c_function_integer_to_c_integer(length);
    signed long int c_extension = c_function_integer_to_c_integer(extension);
    object fill_pointer = r -> fill_pointer;
    signed long int c_fill_pointer = c_function_integer_to_c_integer(fill_pointer);
    if(c_length == c_fill_pointer)
      {
        signed long int c_new_length = c_length + c_extension;
        object new_length = c_function_integer_to_integer(c_new_length);
        object new_dimensions = c_function_cons(new_length, symbol_nil);
        r = (string_rack) realloc(r, string_rack_size + c_new_length * sizeof(object));
        set_rack_of(string, (rack) r);
        r -> dimensions = new_dimensions;
      }
    signed long int c_new_fill_pointer = c_fill_pointer + 1;
    object new_fill_pointer = c_function_integer_to_integer(c_new_fill_pointer);
    r -> fill_pointer = new_fill_pointer;
    r -> characters[c_fill_pointer] = character;
  }
  return extension;
}

object
c_function_string_equal_sign(object string1, object string2)
{
  assert(c_function_stringp(string1) == symbol_t);
  assert(c_function_stringp(string2) == symbol_t);
  string_rack r1 = ((string_rack) rack_of(string1));
  string_rack r2 = ((string_rack) rack_of(string2));
  object length1 = c_function_car(r1 -> dimensions);
  object length2 = c_function_car(r2 -> dimensions);
  signed long int c_length1 = c_function_integer_to_c_integer(length1);
  signed long int c_length2 = c_function_integer_to_c_integer(length2);
  if(c_length1 != c_length2)
    return symbol_nil;
  for(int i = 0; i < c_length1; i++)
    if(r1 -> characters[i] != r2 -> characters[i])
      return symbol_nil;
  return symbol_t;
}
