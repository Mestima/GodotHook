# GodotHook
 A lite custom event system for Godot Engine
 
## Supported versions
| Godot version | Supported | Branch |
| - | - | - |
| 3.x | yes | 3.x |
| 4.x | yes | main |

## Compilation
- Download GodotHook and place it to the Godot `modules` folder.
- Rename `GodotHook-master` to `GodotHook`
- Compile Godot like usual using one of [these guides](https://docs.godotengine.org/en/stable/development/compiling/index.html).

Example compilation `Windows` command: `scons p=windows tools=yes -j4`

## Methods
```gdscript
hook.GetTable()
hook.Add(event: String, uid: String, function: Callable)
hook.Call(event: String, args: Array = [], defer: bool = false)
hook.Remove(event: String, uid: String)
```

## Usage
`hook.Add` creates a new listening event and `hook.Call` executes all listening events of the same type, for example:

```gdscript
# autorun.gd

@onready var hook: Hook = Hook.new()

func printHookOutput1(a: String, b: String):
    print(a, " ", b)
    
func printHookOutput2(a: String, b: String):
    print(a, " ", b)

hook.Add("OnReady", "UniqueName1", Callable(self, "printHookOutput1"))
hook.Add("OnReady", "UniqueName2", Callable(self, "printHookOutput2"))
```
```gdscript
# any node script

func _ready():
    hook.Call("OnReady", ["Hey!", "It's OnReady hook!"])
    hook.Call("OnReady", ["Hey!", "It's OnReady hook, but deferred!"], true)
```

`hook.Remove` removes any listening event by its name and type:

```gdscript
# can be executed at any place

hook.Remove("OnReady", "UniqueName")
```

`hook.GetTable` returns a `Dictionary` with all added listening events

```gdscript
# can be executed at any place

var hookTable: Dictionary = hook.GetTable()
```

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=Mestima/GodotHook&type=Date)](https://star-history.com/#Mestima/GodotHook&Date)
