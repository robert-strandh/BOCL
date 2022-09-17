#ifndef FUNCTION_H
#define FUNCTION_H

#include "object.h"

typedef void (*entry_point)(object static_environment, object arguments);

extern entry_point entry(object function);
extern object environment(object function);

void ensure_function_initialized(void);

#endif
