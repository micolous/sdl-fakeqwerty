# sdl-fakeqwerty

This makes it so that your keyboard looks like a US-QWERTY keyboard to Allegro, SDL 1.2, SDL 2.0 and Unity games, while not changing any system settings.  This is ideal for games with difficult or impossible to change keybindings [which get messed up using a non-QWERTY keyboard](./BACKGROUND.md).

This library intercepts SDL's or Xlib's event system in order to rewrite the `sym` to be like what a US-QWERTY keyboard would return using.  When activated on a non-QWERTY keyboard, it means these games will have keyboard shortcuts with the same physical positions as a QWERTY keyboard.  eg: `W A S D` bindings become `Comma A O E` on US-Dvorak, or `Z Q S D` on a French AZERTY keyboard.

This means you no longer have to change keybindings to play a single game, and the remapping is isolated to a single application (window) and automated.

I've mainly tested this with some Introversion games.  It might fix some other games as well.

Key labels shown in game will probably be displayed incorrectly as a result of using this library.

> **Note:** This will only work on Linux systems, as it relies on `LD_PRELOAD` to work.  There is limited support on OSX (Prison Architect).  I don't have interest in porting this code to other platforms.

## Building / compiling the library

### Linux

Install required packages:

```
# Debian, Ubuntu and friends:
sudo apt install libsdl2-dev libsdl1.2-dev libx11-dev build-essential

# Fedora, OpenSUSE and friends:
sudo dnf install SDL2-devel SDL-devel libX11-devel '@Development Tools'
```

If you're on an `amd64` (aka `x86_64`, Intel 64), and you want to build the `i686` version of this library (because the game is only built for i686), you'll also need:

```
# Debian, Ubuntu and friends:
sudo apt install gcc-multilib

# Fedora, OpenSUSE and friends:
sudo dnf install glibc-devel.i686 SDL2-devel.i686 SDL-devel.i686 libX11-devel.i686
```

Then to build:

```
# Build amd64 version of the library:
make amd64

# Build i686 version of the library:
make i686
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

See [the games list](./games/README.md).
