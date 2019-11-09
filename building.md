# Building / compiling the library

## Linux

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

## OSX

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