# Darwinia

> **Note:** Darwinia allows you to customise most (but not all) keyboard shortcuts.  If you use this library, these should be set to the defaults (based on a QWERTY layout).

## Linux

Copy the compiled `sdl1-hooks-i686.so` (even if you are on `amd64` -- there is no native binary on the Steam version) into `SteamLibrary/SteamApps/common/Darwinia`.

Set the Steam launch options:

```
LD_PRELOAD="./sdl1-hooks-i686.so" %COMMAND%
```

Then run Darwinia through Steam as normal.

