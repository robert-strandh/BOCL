#include "character.h"
#include "symbol.h"
#include "function.h"
#include "control.h"
#include "cons.h"

DEFINE_CLASS(class_character);

typedef struct character_rack *character_rack;

struct character_rack
{
  struct rack prefix;
  char character;
};

static int character_rack_size = sizeof(struct character_rack);

static object characters[256];

static object
make_character(char c)
{
  object obj = (object) malloc(header_size);
  character_rack r = (character_rack) malloc(character_rack_size);
  set_class_of(obj, class_character);
  set_rack_of(obj, (rack) r);
  r -> character = c;
  return obj;
}

static int character_initialized_p = 0;

void
ensure_character_initialized(void)
{
  if (character_initialized_p) return;
  for (int i = 0; i < 256; i++)
    characters[i] = make_character(i);
  character_initialized_p = 1;
}

object
c_function_char_to_character(char c)
{
  ensure_character_initialized();
  return characters[(int) c];
}

object
c_function_characterp(object maybe_character)
{
  return class_of(maybe_character) == class_character ? symbol_t : symbol_nil;
}

object
l_characterp(__attribute__((unused)) object static_environment, object arguments)
{
  check_argument_count(arguments, 1, 1);
  object argument = c_function_car(arguments);
  return list1(c_function_characterp(argument));
}

char
c_function_character_to_c_char(object character)
{
 assert(c_function_characterp(character) == symbol_t);
 return ((character_rack) rack_of(character)) -> character;
}

object
c_function_char_equal_sign(object char1, object char2)
{
  assert(c_function_characterp(char1) == symbol_t);
  assert(c_function_characterp(char2) == symbol_t);
  return char1 == char2 ? symbol_t : symbol_nil;
}

object
c_function_char_not_equal_sign(object char1, object char2)
{
  assert(c_function_characterp(char1) == symbol_t);
  assert(c_function_characterp(char2) == symbol_t);
  return char1 != char2 ? symbol_t : symbol_nil;
}

object
c_function_char_less_than_sign(object char1, object char2)
{
  assert(c_function_characterp(char1) == symbol_t);
  assert(c_function_characterp(char2) == symbol_t);
  character_rack r1 = (character_rack) rack_of(char1);
  character_rack r2 = (character_rack) rack_of(char2);
  return r1 -> character < r2 -> character ? symbol_t : symbol_nil;
}

object
c_function_char_greater_than_sign(object char1, object char2)
{
  assert(c_function_characterp(char1) == symbol_t);
  assert(c_function_characterp(char2) == symbol_t);
  character_rack r1 = (character_rack) rack_of(char1);
  character_rack r2 = (character_rack) rack_of(char2);
  return r1 -> character > r2 -> character ? symbol_t : symbol_nil;
}

object
c_function_char_less_than_or_equal_sign(object char1, object char2)
{
  assert(c_function_characterp(char1) == symbol_t);
  assert(c_function_characterp(char2) == symbol_t);
  character_rack r1 = (character_rack) rack_of(char1);
  character_rack r2 = (character_rack) rack_of(char2);
  return r1 -> character <= r2 -> character ? symbol_t : symbol_nil;
}

object
c_function_char_greater_than_or_equal_sign(object char1, object char2)
{
  assert(c_function_characterp(char1) == symbol_t);
  assert(c_function_characterp(char2) == symbol_t);
  character_rack r1 = (character_rack) rack_of(char1);
  character_rack r2 = (character_rack) rack_of(char2);
  return r1 -> character >= r2 -> character ? symbol_t : symbol_nil;
}

object
c_function_upper_case_p(object character)
{
  assert(c_function_characterp(character) == symbol_t);
  character_rack r = (character_rack) rack_of(character);
  char c = r -> character;
  return (c >= 65 && c <= 90) ? symbol_t : symbol_nil;
}

object
c_function_lower_case_p(object character)
{
  assert(c_function_characterp(character) == symbol_t);
  character_rack r = (character_rack) rack_of(character);
  char c = r -> character;
  return (c >= 97 && c <= 122) ? symbol_t : symbol_nil;
}

object
c_function_both_case_p(object character)
{
  assert(c_function_characterp(character) == symbol_t);
  character_rack r = (character_rack) rack_of(character);
  char c = r -> character;
  return ((c >= 97 && c <= 122) || (c >= 65 && c <= 90)) ? symbol_t : symbol_nil;
}

object
c_function_char_upcase(object character)
{
  assert(c_function_characterp(character) == symbol_t);
  character_rack r = (character_rack) rack_of(character);
  char c = r -> character;
  return (c >= 97 && c <= 122) ? characters[c - 32] : character;
}

object
c_function_char_downcase(object character)
{
  assert(c_function_characterp(character) == symbol_t);
  character_rack r = (character_rack) rack_of(character);
  char c = r -> character;
  return (c >= 65 && c <= 90) ? characters [c + 32] : character;
}

object 
c_function_char_equal(object char1, object char2)
{
  return c_function_char_equal_sign(c_function_char_upcase(char1), c_function_char_upcase(char2));
}

object
c_function_char_not_equal(object char1, object char2)
{
  return c_function_char_not_equal_sign(c_function_char_upcase(char1), c_function_char_upcase(char2));
}

object
c_function_char_lessp(object char1, object char2)
{
  return c_function_char_less_than_sign(c_function_char_upcase(char1), c_function_char_upcase(char2));
}

object
c_function_char_greaterp(object char1, object char2)
{
  return c_function_char_greater_than_sign(c_function_char_upcase(char1), c_function_char_upcase(char2));
}

object
c_function_char_not_lessp(object char1, object char2)
{
  return c_function_char_greater_than_or_equal_sign(c_function_char_upcase(char1), c_function_char_upcase(char2));
}

object
c_function_char_not_greaterp(object char1, object char2)
{
  return c_function_char_less_than_or_equal_sign(c_function_char_upcase(char1), c_function_char_upcase(char2));
}
