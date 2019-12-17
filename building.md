# Building / compiling the library

## Linux

Install required packages:

```sh
# Debian, Ubuntu and friends:
sudo apt install libsdl2-dev libsdl1.2-dev libx11-dev build-essential

# Fedora, OpenSUSE and friends:
sudo dnf install SDL2-devel SDL-devel libX11-devel '@Development Tools'
```

If you're on an `amd64` (aka `x86_64`, Intel 64), and you want to build the
`i686` version of this library (because the game is only built for i686),
you'll _also_ need:

```sh
# Debian, Ubuntu and friends:
sudo apt install gcc-multilib

# Fedora, OpenSUSE and friends:
sudo dnf install glibc-devel.i686 SDL2-devel.i686 SDL-devel.i686 libX11-devel.i686
```

Then to build:

```sh
# Build amd64 version of the library:
make amd64

# Build i686 version of the library:
make i686
```

## macOS

> Note: macOS support is experimental and incomplete. This currently only works
> with [Prison Architect](./games/prison_architect.md).

You'll need [Homebrew][] and [Xcode][] installed.

Install required additional packages:

```sh
brew install sdl2
```

Build the library:

```sh
make osx
```

Install the library to `/usr/local/lib`:

```sh
sudo make install-osx
```

[Homebrew]: https://brew.sh/
[Xcode]: https://developer.apple.com/xcode/resources/