# Multiwinia

## Linux

Copy the compiled `sdl1-hooks-i686.so` (even if you are on `amd64` -- there is no native binary on the Steam version) into `SteamLibrary/SteamApps/common/Multiwinia`.

Set the Steam launch options:

```
LD_PRELOAD="./sdl1-hooks-i686.so" %COMMAND%
```

Then run Multiwinia through Steam as normal.

