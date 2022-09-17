#ifndef CONS_H
#define CONS_H

#include "object.h"

extern void ensure_cons_initialized(void);
extern object c_function_consp(object maybe_cons);
extern object c_function_cons(object car, object cdr);
extern object c_function_car(object cons);
extern object c_function_cdr(object cons);
extern object c_function_rplaca(object cons, object obj);
extern object c_function_rpldca(object cons, object obj);

extern object list1(object element);
extern object list2(object element1, object element2);
extern object list3(object element1, object element2, object element3);
extern object list4(object element1, object element2, object element3, object element4);
extern object list5(object element1, object element2, object element3, object element4, object element5);

extern object class_cons;

#endif
