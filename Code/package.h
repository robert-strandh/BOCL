#ifndef PACKAGE_H
#define PACKAGE_H

#include "object.h"

extern void ensure_package_initialized(void);

extern object package_slot_name(object package);
extern void set_package_slot_name(object package, object name);
extern object package_slot_nicknames(object package);
extern void set_package_slot_nicknames(object package, object name);
extern object c_function_packagep(object maybe_package);

extern void package_add_external_symbol(object package, object symbol);
extern void intern(object string, object package);

extern object class_package;

extern object package_common_lisp;

extern object package_keyword;

#endif
