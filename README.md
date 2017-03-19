# sdl-fakeqwerty

This makes it so that your keyboard looks like a US-QWERTY keyboard to SDL 2.0 games, while not changing any system settings.  This is ideal for games with difficult or impossible to change keybindings which get messed up using a non-QWERTY keyboard.

The problem is some games use `SDL_Keycode` (`event.keysym.sym`) instead of `SDL_Scancode` (`event.keysym.scancode`), and then set the key bindings so they are physically related on a QWERTY keyboard (for example, the common `W A S D` movement keys).

This library intercepts SDL's event system in order to rewrite the `sym` to be like what a US-QWERTY keyboard would return using.  When activated on a non-QWERTY keyboard, it means these games will have keyboard shortcuts with the same physical positions as a QWERTY keyboard.  eg: `W A S D` bindings become `Comma A O E` on US-Dvorak, or `Z Q S D` on a French AZERTY keyboard.

This means you no longer have to change keybindings to play a single game, and the remapping is isolated to a single application (window) and automated.

I've only tested this with some Introversion games.  It might fix some other games as well.

Key labels shown in game may be "wrong" as a result of using this library.

> **Note:** This will only work on Linux systems, as it relies on `LD_PRELOAD` to work.  I don't have interest in porting this code to other platforms.

This code is released under the same open source licenses as SDL: zlib for SDL 2.0 related code (see `COPYING-sdl2`), and LGPLv2.1 for SDL 1.2 related code (see `COPYING-sdl1.2`).  Each file has headers which indicate which license that particular code is shared under.

## Building / compiling the library

Install required packages:

```
sudo apt install libsdl2-dev libsdl1.2-dev build-essential
```

If you're on an `amd64` (aka `x86_64`, Intel 64), and you want to build the `i686` version of this library (because the game is only built for i686), you'll also need:

```
sudo apt install gcc-multilib
```

Then to build:

```
make
```

You can also build just the `amd64` (aka `x86_64`, Intel 64) version with `make amd64`, and build just the `i686` (aka `x86_32`) version with `make i686`.

## Setting up

### Darwinia

> **Note:** Darwinia allows you to customise most (but not all) keyboard shortcuts.  If you use this library, these should be set to the defaults (based on a QWERTY layout).

Copy the compiled `sdl1-hooks-i686.so` (even if you are on `amd64` -- there is no native binary on the Steam version) into `SteamLibrary/SteamApps/common/Darwinia`.

Edit the shell script `run_steam.sh`, and change the line that says:

```sh
    ./darwinia.bin.x86
```

to:

```sh
    LD_PRELOAD="./sdl1-hooks-i686.so" ./darwinia.bin.x86
```

### DEFCON

> **Note:** DEFCON allows you to choose QZERTY, AZERTY and Dvorak keyboard layouts in "Other" settings.  If you use this library, this option must be set to QWERTY (the default).

Copy the compiled `sdl1-hooks-i686.so` (even if you are on `amd64` -- there is no native binary on the Steam version) into `SteamLibrary/SteamApps/common/Defcon`.

Edit the shell script `run_steam.sh`, and change the line that says:

```sh
    ./defcon.bin.x86
```

to:

```sh
    LD_PRELOAD="./sdl1-hooks-i686.so" ./defcon.bin.x86
```


### Multiwinia

Copy the compiled `sdl1-hooks-i686.so` (even if you are on `amd64` -- there is no native binary on the Steam version) into `SteamLibrary/SteamApps/common/Multiwinia`.

Edit the shell script `run_steam.sh`, and change the line that says:

```sh
    ./multiwinia.bin.x86
```

to:

```sh
    LD_PRELOAD="./sdl1-hooks-i686.so" ./multiwinia.bin.x86
```

### Prison Architect

Prison Architect keybindings suffer this problem.  According to the [public forums](http://forums.introversion.co.uk/viewtopic.php?t=19330) and the (private) bug tracker, the issue is known but a fix doesn't look like it an official fix will ever come.

With this library loaded, text fields still work correctly (in your native layout, not QWERTY).

Copy the compiled `sdl2-hooks-*.so` file into `SteamLibrary/SteamApps/common/Prison Architect`.

Then edit the shell script `PrisonArchitect` in this directory, and go to the end of the file.

If you are running on an `amd64` system, change:

```sh
    "$base"/PrisonArchitect.x86_64 "$@"
```

to:

```sh
    LD_PRELOAD=./sdl2-hooks-amd64.so "$base"/PrisonArchitect.x86_64 "$@"
```

If you are running on an `i686` system, change:

```sh
    "$base"/PrisonArchitect.i686 "$@"
```

to:

```sh
    LD_PRELOAD=./sdl2-hooks-i686.so "$base"/PrisonArchitect.i686 "$@"
```

Then run Prison Architect through Steam as normal.

## Other games

This library works with games which dynamically link to SDL 1.2 or SDL 2.0.  It doesn't matter if the game supplies its own version of libSDL.so.  This won't work with games which statically link SDL.

In order to determine which version is in use, use `ldd`.

For example, this game uses SDL 2.0, with a library which ships with the game:

```
$ ldd ./exampleGameBinary | grep -i sdl
	libSDL2-2.0.so.0 => /mnt/raid1/SteamLibrary/SteamApps/common/example/./lib64/libSDL2-2.0.so.0 (0x0000xxxxxxxxxxxx)
```

This game uses SDL 1.2:

```
$ ldd ./exampleGameBinary | grep -i sdl
	libSDL-1.2.so.0 => /mnt/raid1/SteamLibrary/SteamApps/common/example/./lib/libSDL-1.2.so.0 (0xf7xxxxxx)
```

You then need to figure out what architecture the game runs on, which can be done with `file`.

Once you know this, copy the appropriate `sdl*-hooks-*.so` file into the game's folder, and then edit the game's startup script (or make a new startup script), which invokes the game with the appropriate `LD_PRELOAD` environment variable.  For example, this will run the game with the SDL 2.0 hooks for amd64:

```
LD_PRELOAD=./sdl2-hooks-amd64.so ./exampleGameBinary
```

