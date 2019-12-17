# Game-specific documentation

This is a list of all the games that have been tested with `sdl-fakeqwerty`:

Game                                      | Library | Linux              | macOS
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

```console
$ ldd ./exampleGameBinary | grep -i sdl
	libSDL2-2.0.so.0 => /.../SteamApps/common/example/./lib64/libSDL2-2.0.so.0 (0x0000xxxxxxxxxxxx)
```

This game uses SDL 1.2:

```console
$ ldd ./exampleGameBinary | grep -i sdl
	libSDL-1.2.so.0 => /.../SteamApps/common/example/./lib/libSDL-1.2.so.0 (0xf7xxxxxx)
```

Additional versions:

* `sdl1-peep-hooks`: alternative SDL1.2 version that uses `SDL_PeepEvents`
* `xlib-hooks`: alternative Xlib version for games with other engines (eg: Allegro and Unity)

You then need to figure out what architecture the game runs on, which can be done with `file`.

Once you know this, copy the appropriate `*-hooks-*.so` file into the game's folder, and then [edit the game's launch options in Steam][steam-launch-opts].  For example, this will run the game with the SDL 2.0 hooks for amd64:

```sh
LD_PRELOAD="./sdl2-hooks-amd64.so" %COMMAND%
```

Alternatively, you can use a shell script to wrap the game's binary.

### macOS

Steam on macOS appears to support neither 
[the `%COMMAND%` options that the Linux client does][mac-command], nor the
[LSEnvironment][] attribute, so you need a startup script like:

```bash
#!/bin/bash
cd "${0%/*}"
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=/usr/local/lib/sdl2-hooks.dylib ./Example "$@"
```

At present, only the SDL2 library has been set up for macOS support.
Patches welcome! :)

You can check which libraries a game uses with `objdump -macho -dylibs-used`:

```console
$ objdump -macho -dylibs-used Example.app/Contents/MacOS/Example | grep -i sdl
	@rpath/SDL2.framework/Versions/A/SDL2 (compatibility version 1.0.0, current version 1.0.0)
```

There may be some issues with the `rpath` on other games.  But this may be
difficult to address in a generic way.

[LSEnvironment]: https://developer.apple.com/documentation/bundleresources/information_property_list/lsenvironment
[mac-command]: https://github.com/ValveSoftware/steam-for-linux/issues/5548
[steam-launch-opts]: https://support.steampowered.com/kb_article.php?ref=5623-QOSV-5250
