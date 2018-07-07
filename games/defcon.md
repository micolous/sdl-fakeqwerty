# DEFCON

> **Note:** DEFCON allows you to choose QZERTY, AZERTY and Dvorak keyboard layouts in "Other" settings.  If you use this library, this option must be set to QWERTY (the default).

## Linux

Copy the compiled `sdl1-hooks-i686.so` (even if you are on `amd64` -- there is no native binary on the Steam version) into `SteamLibrary/SteamApps/common/Defcon`.

Set the Steam launch options:

```
LD_PRELOAD="./sdl1-hooks-i686.so" %COMMAND%
```

Then run DEFCON through Steam as normal.

