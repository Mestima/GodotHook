/* hook.h */

#ifndef HOOK_H
#define HOOK_H

#include "core/object/ref_counted.h"
#include "core/string/ustring.h"
#include "core/variant/variant.h"
#include "core/variant/callable.h"
#include "core/variant/array.h"
#include "core/variant/dictionary.h"

class Hook : public RefCounted {
    GDCLASS(Hook, RefCounted);

    Dictionary table;

protected:
    static void _bind_methods();

public:
	Dictionary GetTable();
	void Add(String event, String uid, Callable function);
	void Call(String event, Array args, bool defer);
	void Remove(String event, String uid);
    Hook();
};

#endif // HOOK_H