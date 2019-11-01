# SpaceChem

## Linux

Copy the compiled `sdl1-peep-hooks-i686.so` (even if you are on `amd64` -- there is no native binary on the Steam version) into `SteamLibrary/SteamApps/common/SpaceChem`.

Modify ``spacechem-launcher.sh`` file from:

```
#!/bin/sh
MONO_CFG_DIR=etc MONO_PATH=monolib ./mono SpaceChem.exe
```

To 

```
#!/bin/sh
LD_PRELOAD="${LD_PRELOAD}:./sdl1-peep-hooks-i686.so" MONO_CFG_DIR=etc MONO_PATH=monolib ./mono SpaceChem.exe
```

Then run SpaceChem through Steam as normal.

