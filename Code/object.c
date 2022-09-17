#include "object.h"

size_t header_size = sizeof(struct header);

object
make_object(void)
{
  return (object) malloc(header_size);
}

size_t rack_size = sizeof(struct rack);

rack
make_rack(size_t size)
{
  return (rack) malloc(rack_size + size);
}

object
class_of(object obj)
{
  return obj -> class;
}

rack
rack_of(object obj)
{
  return obj -> rack;
}

void
set_class_of(object obj, object class)
{
  obj -> class = class;
}

void
set_rack_of(object obj, rack r)
{
  obj -> rack = r;
}
