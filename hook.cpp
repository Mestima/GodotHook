/* hook.cpp */

#include "hook.h"

Dictionary Hook::getTable() {
	return table;
}

void Hook::add(String event, String uid, Callable function) {
	Dictionary tmp = table.get(event, Dictionary());
	tmp[uid] = function;
	table[event] = tmp;
}

void Hook::call(String event, Array args = Array(), bool defer = false) {
	const Variant **argptrs = nullptr;
	if (args.size() > 0) {
		argptrs = (const Variant **)alloca(sizeof(Variant *) * args.size());
		for (int i = 0; i < args.size(); i++) {
			argptrs[i] = &args[i];
		}
	}
	
	for (int i = 0; i < table.size(); i++) {
		Dictionary tmp = table.get(event, Dictionary());
		if (!tmp.is_empty()) {
			Array keys = tmp.keys();
			for (int key_i = 0; key_i < keys.size(); key_i++) {
				Callable function = tmp[keys[key_i]];
				if (!defer) {
					Callable::CallError call_error;
					function.callp(argptrs, args.size(), Variant(), call_error);
				} else {
					function.call_deferredp(argptrs, args.size());
				}
			}
		} else {
			ERR_PRINT("Hook event '" + event + "' cannot be found or empty.");
		}
	}
}

void Hook::remove(String event, String uid) {
	Dictionary tmp = table.get(event, Dictionary());
	if (!tmp.is_empty()) {
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
	ClassDB::bind_method(D_METHOD("getTable"), &Hook::getTable);
	ClassDB::bind_method(D_METHOD("add", "event", "uid", "function"), &Hook::add);
	ClassDB::bind_method(D_METHOD("call", "event", "args", "defer"), &Hook::call, DEFVAL(Array()), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("remove", "event", "uid"), &Hook::remove);
};

Hook::Hook() {
	table = Dictionary();
}