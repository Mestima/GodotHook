/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "hook.h"

void register_GodotHook_types() {
    ClassDB::register_class<Hook>();
}

void unregister_GodotHook_types() {
   // Nothing to do here in this example.
}