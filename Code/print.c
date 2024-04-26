#include "stream.h"
#include "string.h"
#include "character.h"
#include "symbol.h"
#include "cons.h"
#include "integer.h"
#include "print.h"

void
c_function_print_symbol(object symbol, object stream)
{
  object name = c_function_symbol_name(symbol);
  object length = c_function_string_total_length(name);
  signed long int c_length = c_function_integer_to_c_integer(length);
  for(int i = 0; i < c_length; i++)
    {
      object index = c_function_integer_to_integer(i);
      object character = c_function_char(name, index);
      c_function_stream_write_char(stream, character);
    }
}

void
c_function_print_string(object string, object stream)
{
  object length = c_function_string_total_length(string);
  signed long int c_length = c_function_integer_to_c_integer(length);
  object double_quote = c_function_char_to_character('"');
  c_function_stream_write_char(stream, double_quote);
  for(int i = 0; i < c_length; i++)
    {
      object index = c_function_integer_to_integer(i);
      object character = c_function_char(string, index);
      c_function_stream_write_char(stream, character);
    }
  c_function_stream_write_char(stream, double_quote);
}

void
c_function_print_cons(object cons, object stream)
{
  object left_parenthesis = c_function_char_to_character('(');
  object right_parenthesis = c_function_char_to_character(')');
  object space = c_function_char_to_character(' ');
  object remaining = cons;
  c_function_stream_write_char(stream, left_parenthesis);
  while(c_function_consp(remaining) == symbol_t)
    {
      c_function_print(c_function_car(remaining), stream);
      c_function_stream_write_char(stream, space);
      remaining = c_function_cdr(remaining);
    }
  if(remaining == symbol_nil)
    c_function_stream_write_char(stream, right_parenthesis);
  else
    {
      object dot = c_function_char_to_character('.');
      c_function_stream_write_char(stream, space);
      c_function_stream_write_char(stream, dot);
      c_function_stream_write_char(stream, space);
      c_function_print(remaining, stream);
      c_function_stream_write_char(stream, right_parenthesis);
    }
}

void
c_function_print_integer(__attribute__((unused)) object integer, object stream)
{
  object zero = c_function_char_to_character('0');
  c_function_stream_write_char(stream, zero);
}

void
c_function_print_unknown(__attribute__((unused)) object unknoen, object stream)
{
  object questionmark = c_function_char_to_character('?');
  c_function_stream_write_char(stream, questionmark);
}

object
c_function_print(object obj, object stream)
{
  if(c_function_symbolp(obj) == symbol_t)
    c_function_print_symbol(obj, stream);
  else if(c_function_stringp(obj) == symbol_t)
    c_function_print_string(obj, stream);
  else if(c_function_consp(obj) == symbol_t)
    c_function_print_cons(obj, stream);
  else if(c_function_integerp(obj) == symbol_t)
    c_function_print_integer(obj, stream);
  else
    c_function_print_unknown(obj, stream);
  return obj;
}
