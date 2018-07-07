# SUPERHOT

> **Note:** SUPERHOT does not support changing keybindings, and the tutorial will assume a QWERTY keymap.

## Linux

Copy the compiled `xlib-hooks-amd64.so` file into `SteamLibrary/SteamApps/common/SUPERHOT`.

Set the Steam launch options:

```
LD_PRELOAD="./xlib-hooks-amd64.so" %COMMAND%
```

Then run SUPERHOT through Steam as normal.  Note that running it directly will cause the game to segfault when you select `superhot.exe` from the game menu.

