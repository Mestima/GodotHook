/* hook.h */

#ifndef HOOK_H
#define HOOK_H

#include "core/reference.h"
#include "core/func_ref.h"
#include "core/ustring.h"
#include "core/dictionary.h"
#include "core/array.h"

class Hook : public Reference {
	GDCLASS(Hook, Reference);
	
	Dictionary table;
	
protected:
	static void _bind_methods();
	
public:
	Dictionary GetTable();
	void Create(String name);
	void Add(String event, String uid, Ref<FuncRef> function);
	void Call(String event, Array args);
	void Remove(String event, String uid);
	Hook();
};

#endif // HOOK_H