#include "stream.h"
#include "symbol.h"
#include "character.h"
#include <stdio.h>

DEFINE_CLASS(class_stream);

typedef struct stream_rack *stream_rack;

struct stream_rack
{
  struct rack prefix;
  FILE *c_stream;
};

static int stream_rack_size = sizeof(struct stream_rack);

object standard_input;
object standard_output;

static object
make_stream(FILE *c_stream)
{
  object obj = (object) malloc(header_size);
  stream_rack r = (stream_rack) malloc(stream_rack_size);
  set_class_of(obj, class_stream);
  set_rack_of(obj, (rack) r);
  r -> c_stream = c_stream;
  return obj;
}

static int stream_initialized_p = 0;

void
ensure_stream_initialized(void)
{
  if (stream_initialized_p) return;
  standard_input = make_stream(stdin);
  standard_output = make_stream(stdout);
  stream_initialized_p = 1;
}

object
c_function_streamp(object maybe_stream)
{
  return class_of(maybe_stream) == class_stream ? symbol_t : symbol_nil;
}

object
c_function_stream_read_char(object stream)
{
  FILE *c_stream = ((stream_rack) rack_of(stream)) -> c_stream;
  char c_char = getc(c_stream);
  return c_function_char_to_character(c_char);
}

object
c_function_stream_write_char(object stream, object character)
{
  FILE *c_stream = ((stream_rack) rack_of(stream)) -> c_stream;
  char c_char = c_function_character_to_c_char(character);
  putc(c_char, c_stream);
  return character;
}
