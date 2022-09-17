#ifndef CLOS_H
#define CLOS_H

#include "object.h"

extern void initialize_clos(void);

extern object class_t;
extern object class_function;
extern object class_funcallable_standard_object;
extern object class_generic_function;
extern object class_standard_generic_function;
extern object class_standard_object;
extern object class_metaobject;
extern object class_method;
extern object class_standard_method;
extern object class_standard_accessor_method;
extern object class_standard_reader_method;
extern object class_standard_writer_method;
extern object class_slot_definition;
extern object class_direct_slot_definition;
extern object class_effective_slot_definition;
extern object class_standard_slot_definition;
extern object class_standard_direct_slot_definition;
extern object class_standard_effective_slot_definition;
extern object class_method_combination;
extern object class_specializer;
extern object class_eql_specializer;
extern object class_class;
extern object class_standard_class;
extern object class_funcallable_standard_class;
extern object class_built_in_class;
extern object class_forward_referenced_class;

#endif
