# sdl-fakeqwerty

This makes it so that your keyboard looks like a US-QWERTY keyboard to Allegro, SDL 1.2, SDL 2.0 and Unity games, while not changing any system settings.  This is ideal for games with difficult or impossible to change keybindings which get messed up using a non-QWERTY keyboard.

The problem is some games use `SDL_Keycode` (`event.keysym.sym`) instead of `SDL_Scancode` (`event.keysym.scancode`), and then set the key bindings so they are physically related on a QWERTY keyboard (for example, the common `W A S D` movement keys).

This library intercepts SDL's or Xlib's event system in order to rewrite the `sym` to be like what a US-QWERTY keyboard would return using.  When activated on a non-QWERTY keyboard, it means these games will have keyboard shortcuts with the same physical positions as a QWERTY keyboard.  eg: `W A S D` bindings become `Comma A O E` on US-Dvorak, or `Z Q S D` on a French AZERTY keyboard.

This means you no longer have to change keybindings to play a single game, and the remapping is isolated to a single application (window) and automated.

I've only tested this with some Introversion games.  It might fix some other games as well.

Key labels shown in game will probably be displayed incorrectly as a result of using this library.

> **Note:** This will only work on Linux systems, as it relies on `LD_PRELOAD` to work.  I don't have interest in porting this code to other platforms.

This code is released under the same open source licenses as SDL: zlib for SDL 2.0 and Xlib related code (see `COPYING-sdl2.txt`), and LGPLv2.1 for SDL 1.2 related code (see `COPYING-sdl1.2.txt`).  Each file has headers which indicate which license that particular code is shared under.

## Building / compiling the library
### Linux

Install required packages:

```
sudo apt install libsdl2-dev libsdl1.2-dev libx11-dev build-essential
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

### OSX

> Note: OSX support is experimental and incomplete. This currently only works with Prison Architect.

You'll need Homebrew and XCode installed.

Install required packages:

```
brew install sdl2
```

Then to build:

```
make osx
```

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

### Factorio

> **Note:** Factorio allows you to configure keybindings. If you use this library, these should be set to the defaults (based on a QWERTY layout).

Copy the compiled `xlib-hooks-amd64.so` file into `SteamLibrary/SteamApps/common/Factorio/bin/x64`.

Rename `factorio` to `factorio.bin`.

Create a new file called `factorio` with this content, and make it executable (`chmod +x`):

```sh
#!/bin/sh
BASE=`dirname $0`
LD_PRELOAD="$BASE/xlib-hooks-amd64.so" "$BASE"/factorio.bin
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

Prison Architect keybindings suffer this problem.  According to the [public forums](http://forums.introversion.co.uk/viewtopic.php?t=19330) and the (private) bug tracker, the issue is known, but an official fix doesn't look like it will ever come.

With this library loaded, text fields still work correctly (in your native layout, not QWERTY).

#### Linux

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

#### OSX

**Note:** This is experimental, and you need to run `make install-osx` first (per the build instructions above).

First, open `Prison Architect.app/Contents/Info.plist`, and find the attribute:

```xml
	<key>CFBundleExecutable</key>
  <string>Prison Architect</string>
```

Replace it with:

```xml
	<key>CFBundleExecutable</key>
  <string>prison.sh</string>
```

Create a new, executable (`chmod +x`) file `Prison Architect.app/Contents/MacOS/prison.sh` with the contents:

```sh
#!/bin/bash
cd "${0%/*}"
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=/usr/local/lib/sdl2-hooks.dylib ./Prison\ Architect "$@"
```

Finally, refresh the `launchctl` cache with:

```
/System/Library/Frameworks/CoreServices.framework/Frameworks/LaunchServices.framework/Support/lsregister -v -f ${HOME}/Library/Application\ Support/Steam/steamapps/common/Prison\ Architect/Prison\ Architect.app
```

And then you can launch the game through Steam as normal.

### SUPERHOT

> **Note:** SUPERHOT does not support changing keybindings, and the tutorial will assume a QWERTY keymap.

Copy the compiled `xlib-hooks-amd64.so` file into `SteamLibrary/SteamApps/common/SUPERHOT`.

Rename `SUPERHOT.x86_64` to `SUPERHOT.bin`. If you choose a different name with more dots in it, then SUPERHOT will fail to start with `There is no data folder`.

Create a new file called `SUPERHOT.x86_64` with this content, and make it executable (`chmod +x`):

```sh
#!/bin/sh
BASE=`dirname $0`
LD_PRELOAD="$BASE/xlib-hooks-amd64.so" "$BASE"/SUPERHOT.bin
```

Then run SUPERHOT through Steam as normal.  Note that running it directly will cause the game to segfault when you select `superhot.exe` from the game menu.

## Other games

### Linux

This library works with games which dynamically link to SDL 1.2, SDL 2.0 or Xlib.  It doesn't matter if the game supplies its own version of libSDL.so.  This won't work with games which statically link SDL.

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

There is also an xlib version which can be used as a fallback for games with other engines (eg: Allegro and Unity).

You then need to figure out what architecture the game runs on, which can be done with `file`.

Once you know this, copy the appropriate `*-hooks-*.so` file into the game's folder, and then edit the game's startup script (or make a new startup script), which invokes the game with the appropriate `LD_PRELOAD` environment variable.  For example, this will run the game with the SDL 2.0 hooks for amd64:

```
LD_PRELOAD=./sdl2-hooks-amd64.so ./exampleGameBinary
```

### OSX

Steam on OSX appears to support neither the `%COMMAND%` options that the Linux client does, nor the `LSEnvironment` attribute.

Currently only the SDL2 library has been set up for OSX support.

There may be some issues with the `rpath` on other games.  But this may be difficult to address in a generic way.
