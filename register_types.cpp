/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "hook.h"

void register_hook_types() {
    ClassDB::register_class<Hook>();
}

void unregister_hook_types() {
   // Nothing to do here in this example.
}