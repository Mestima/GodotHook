/* register_types.cpp */

#include "register_types.h"
#include "core/object/class_db.h"
#include "hook.h"

void initialize_hook_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<Hook>();
	}
}

void uninitialize_hook_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}