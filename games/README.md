# Game-specific documentation

This is a list of all the games that have been tested with `sdl-fakeqwerty`:

Game                                      | Library | Linux              | OSX
----------------------------------------- |---------|--------------------|----------------
[Darwinia](./darwinia.md)                 | SDL 1.2 | :heavy_check_mark: | :no_entry_sign:
[DEFCON](./defcon.md)                     | SDL 1.2 | :heavy_check_mark: | :no_entry_sign:
[Factorio](./factorio.md)                 | xlib    | :heavy_check_mark: | :no_entry_sign:
[Multiwinia](./multiwinia.md)             | SDL 1.2 | :heavy_check_mark: | :no_entry_sign:
[Prison Architect](./prison_architect.md) | SDL 2.0 | :heavy_check_mark: | :heavy_check_mark:
[SpaceChem](./spacechem.md)               | SDL 1.2 (peep) | :heavy_check_mark: | :no_entry_sign:
[SUPERHOT](./superhot.md)                 | xlib    | :heavy_check_mark: | :no_entry_sign:

## Other games

These instructions are specific to things on Steam.

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

Once you know this, copy the appropriate `*-hooks-*.so` file into the game's folder, and then edit the game's launch options in Steam.  For example, this will run the game with the SDL 2.0 hooks for amd64:

```
LD_PRELOAD="./sdl2-hooks-amd64.so" %COMMAND%
```

Alternatively, you can use a shell script to wrap the game's binary.

### OSX

Steam on OSX appears to support neither [the `%COMMAND%` options that the Linux client does](https://github.com/ValveSoftware/steam-for-linux/issues/5548), nor the `LSEnvironment` attribute, so you need a startup script like:

```bash
#!/bin/bash
cd "${0%/*}"
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=/usr/local/lib/sdl2-hooks.dylib ./Example "$@"
```

Currently only the SDL2 library has been set up for OSX support.

There may be some issues with the `rpath` on other games.  But this may be difficult to address in a generic way.
