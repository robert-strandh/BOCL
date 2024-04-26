#include "object.h"
#include "package.h"
#include "symbol.h"
#include "string.h"
#include "cons.h"
#include "integer.h"
#include "substandard-reader.h"
#include <stdio.h>

int
next_interesting_character(FILE *stream)
{
  int c;
  for(c = getc(stream);
      c == 9 || c == 10 || c == ' ';
      c = getc(stream))
    ;
  return c;
}

object
substandard_list_reader(FILE *stream)
{
  int c = next_interesting_character(stream);
  if(c == ')')
    return symbol_nil;
  {
    ungetc(c, stream);
    object element = substandard_reader(stream);
    return c_function_cons(element, substandard_list_reader(stream));
  }
}

int
is_digit(char c)
{
  return c >= '0' && c <= '9';
}

int
all_digits_p(char *s)
{
  int i;
  for(i = 0; is_digit(s[i]); i++)
    ;
  return s[i] == 0;
}

signed long int
parse_positive_integer(char *s)
{
  signed long int result = 0;
  for(int i = 0; s[i] != 0; i++)
    result = result * 10 + s[i] - '0';
  return result;
}

char constituent[128] =
  {0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0,
   0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0,
   0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0
  };

object
substandard_reader(FILE *stream)
{
  int c = next_interesting_character(stream);
  if(c == ';')
    {
      for(c = getc(stream); c != 10; c = getc(stream))
        ;
      return substandard_reader(stream);
    }
  else if(c == '(')
    {
      return substandard_list_reader(stream);
    }
  else
    {
      char buffer[1000];
      buffer[0] = c;
      int next = 1;
      for(c = getc(stream);
          c != -1 && c < 128 && constituent[c];
          c = getc(stream))
        buffer[next++] = c;
      ungetc(c, stream);
      buffer[next] = 0;
      if(all_digits_p(buffer + 1) && (buffer[0] == '-' || is_digit(buffer[0])))
        {
          if(buffer[0] == '-')
            return c_function_integer_to_integer(-parse_positive_integer(buffer + 1));
          else
            return c_function_integer_to_integer(parse_positive_integer(buffer));
        }
      else
        {
          for(int i = 0; buffer[i] != 0; i++)
            if(buffer[i] >= 'a' && buffer[i] <= 'z')
              buffer[i] -= 32;
          object string = c_function_string_to_string(buffer);
          return c_function_intern(string, current_package);
        }
   }
}
