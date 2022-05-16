/* hook.cpp */

#include "hook.h"

Dictionary Hook::GetTable() {
	return table;
}

void Hook::Add(String event, String uid, Callable function) {
	Dictionary tmp = table.get(event, Dictionary());
	tmp[uid] = function;
	table[event] = tmp;
}

void Hook::Call(String event, Array args, bool defer = false) {
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
					function.call(argptrs, args.size(), Variant(), call_error);
				} else {
					function.call_deferred(argptrs, args.size());
				}
			}
		} else {
			ERR_PRINT("Hook event '" + event + "' cannot be found or empty.");
		}
	}
}

void Hook::Remove(String event, String uid) {
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
	ClassDB::bind_method(D_METHOD("GetTable"), &Hook::GetTable);
	ClassDB::bind_method(D_METHOD("Add", "event", "uid", "function"), &Hook::Add);
	ClassDB::bind_method(D_METHOD("Call", "event", "args", "defer"), &Hook::Call, DEFVAL(false));
	ClassDB::bind_method(D_METHOD("Remove", "event", "uid"), &Hook::Remove);
};

Hook::Hook() {
	table = Dictionary();
}