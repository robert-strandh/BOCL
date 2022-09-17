#include "object.h"
#include "package.h"
#include "symbol.h"
#include "character.h"
#include "string.h"
#include "cons.h"

DEFINE_CLASS(class_package);

object package_common_lisp;

object package_keyword;

object package_common_lisp_user;

static int package_initialized_p = 0;

typedef struct package_rack *package_rack;

struct package_rack
{
  struct rack prefix;
  object name;
  object nicknames;
  object used_packages;
  object internal_symbols;
  object external_symbols;
};

static int package_rack_size = sizeof(struct package_rack);

object
make_package()
{
  object result = make_object();
  package_rack r = (package_rack) malloc(package_rack_size);
  r -> used_packages = symbol_nil;
  r -> internal_symbols = symbol_nil;
  r -> external_symbols = symbol_nil;
  set_class_of(result, class_package);
  set_rack_of(result, (rack) r);
  return result;
}

void
make_common_lisp_package()
{
  package_common_lisp = make_package();
  package_rack r = (package_rack) rack_of(package_common_lisp);
  r -> name = c_function_string_to_string("COMMON-LISP");
  r -> nicknames = c_function_cons(c_function_string_to_string("CL"), symbol_nil);
}

void
make_keyword_package()
{
  package_keyword = make_package();
  package_rack r = (package_rack) rack_of(package_keyword);
  r -> name = c_function_string_to_string("KEYWORD");
}

void
make_common_lisp_user_package()
{
  package_common_lisp_user = make_package();
  package_rack r = (package_rack) rack_of(package_common_lisp_user);
  r -> name = c_function_string_to_string("COMMON-LISP-USER");
  r -> nicknames = c_function_cons(c_function_string_to_string("CL-USER"), symbol_nil);
}

void
ensure_package_initialized(void)
{
  if(package_initialized_p) return;
  make_common_lisp_package();
  make_keyword_package();
  make_common_lisp_user_package();
  package_initialized_p = 1;
}

object
c_function_packagep(object maybe_package)
{
  return class_of(maybe_package) == class_package ? symbol_t : symbol_nil;
}

extern void
package_add_external_symbol(object package, object symbol)
{
  package_rack r = (package_rack) rack_of(package);
  r -> external_symbols = c_function_cons(symbol, r -> external_symbols);
}
