#include "clos.h"

DEFINE_CLASS(class_t);
DEFINE_CLASS(class_function);
DEFINE_CLASS(class_funcallable_standard_object);
DEFINE_CLASS(class_generic_function);
DEFINE_CLASS(class_standard_generic_function);
DEFINE_CLASS(class_standard_object);
DEFINE_CLASS(class_metaobject);
DEFINE_CLASS(class_method);
DEFINE_CLASS(class_standard_method);
DEFINE_CLASS(class_standard_accessor_method);
DEFINE_CLASS(class_standard_reader_method);
DEFINE_CLASS(class_standard_writer_method);
DEFINE_CLASS(class_slot_definition);
DEFINE_CLASS(class_direct_slot_definition);
DEFINE_CLASS(class_effective_slot_definition);
DEFINE_CLASS(class_standard_slot_definition);
DEFINE_CLASS(class_standard_direct_slot_definition);
DEFINE_CLASS(class_standard_effective_slot_definition);
DEFINE_CLASS(class_method_combination);
DEFINE_CLASS(class_specializer);
DEFINE_CLASS(class_eql_specializer);
DEFINE_CLASS(class_class);
DEFINE_CLASS(class_standard_class);
DEFINE_CLASS(class_funcallable_standard_class);
DEFINE_CLASS(class_built_in_class);
DEFINE_CLASS(class_forward_referenced_class);

void
assign_metaclasses(void)
{
  set_class_of(class_t, class_built_in_class);
  set_class_of(class_function, class_built_in_class);
  set_class_of(class_funcallable_standard_object, class_standard_class);
  set_class_of(class_generic_function, class_funcallable_standard_class);
  set_class_of(class_standard_generic_function, class_funcallable_standard_class);
  set_class_of(class_standard_object, class_standard_class);
  set_class_of(class_metaobject, class_standard_class);
  set_class_of(class_method, class_standard_class);
  set_class_of(class_standard_method, class_standard_class);
  set_class_of(class_standard_accessor_method, class_standard_class);
  set_class_of(class_standard_reader_method, class_standard_class);
  set_class_of(class_standard_writer_method, class_standard_class);
  set_class_of(class_slot_definition, class_standard_class);
  set_class_of(class_direct_slot_definition, class_standard_class);
  set_class_of(class_effective_slot_definition, class_standard_class);
  set_class_of(class_standard_slot_definition, class_standard_class);
  set_class_of(class_standard_direct_slot_definition, class_standard_class);
  set_class_of(class_standard_effective_slot_definition, class_standard_class);
  set_class_of(class_method_combination, class_standard_class);
  set_class_of(class_specializer, class_standard_class);
  set_class_of(class_eql_specializer, class_standard_class);
  set_class_of(class_class, class_standard_class);
  set_class_of(class_standard_class, class_standard_class);
  set_class_of(class_funcallable_standard_class, class_standard_class);
  set_class_of(class_built_in_class, class_standard_class);
  set_class_of(class_forward_referenced_class, class_standard_class);
}

void
initialize_clos(void)
{
  assign_metaclasses();
}
