/* hook.cpp */

#include "hook.h"

Dictionary Hook::GetTable() {
	return table;
}

void Hook::Create(String name) {
	Dictionary newHook = Dictionary();
	table[name] = newHook;
}

void Hook::Add(String event, String uid, Ref<FuncRef> function) {
	Dictionary tmp = table[event];
	tmp[uid] = function;
	table[event] = tmp;
}

void Hook::Call(String event, Array args = Array()) {
	for (int i = 0; i < table.size(); i++) {
		Dictionary tmp = table.get(event, Dictionary());
		if (!tmp.empty()) {
			Array keys = tmp.keys();
			for (int key_i = 0; key_i < keys.size(); key_i++) {
				Ref<FuncRef> function = tmp[keys[key_i]];
				function->call_funcv(args);
			}
		} else {
			ERR_PRINT("Hook event '" + event + "' cannot be found or empty.");
		}
	}
}

void Hook::Remove(String event, String uid) {
	Dictionary tmp = table.get(event, Dictionary());
	if (!tmp.empty()) {
		if (tmp.erase(uid)) {
			table[event] = tmp;
		} else {
			ERR_PRINT("Hook '" + uid + "' cannot be found.");
		}
	} else {
		ERR_PRINT("Hook event '" + event + "' cannot be found or empty.");
	}
}

void Hook::_bind_methods() {
	ClassDB::bind_method(D_METHOD("GetTable"), &Hook::GetTable);
	ClassDB::bind_method(D_METHOD("Create", "name"), &Hook::Create);
	ClassDB::bind_method(D_METHOD("Add", "event", "uid", "function"), &Hook::Add);
	ClassDB::bind_method(D_METHOD("Call", "event", "args"), &Hook::Call);
	ClassDB::bind_method(D_METHOD("Remove", "event", "uid"), &Hook::Remove);
};

Hook::Hook() {
	table = Dictionary();
}