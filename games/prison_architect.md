# Prison Architect

Prison Architect keybindings suffer this problem.  According to the [public forums](http://forums.introversion.co.uk/viewtopic.php?t=19330) and the (private) bug tracker, the issue is known, but an official fix doesn't look like it will ever come.

With this library loaded, text fields still work correctly (in your native layout, not QWERTY).

## Linux

Copy the compiled `sdl2-hooks-*.so` file into `SteamLibrary/SteamApps/common/Prison Architect`.

[Set the Steam launch options][steam-launch-opts].  If you are on an `amd64` system, set:

```
LD_PRELOAD="./sdl2-hooks-amd64.so" %COMMAND%
```

If you are on an `i686` system, set:


```
LD_PRELOAD="./sdl2-hooks-i686.so" %COMMAND%
```

Then run Prison Architect through Steam as normal.

[steam-launch-opts]: https://support.steampowered.com/kb_article.php?ref=5623-QOSV-5250

## OSX

**Note:** This is experimental, and you need to run `make install-osx` first (per the build instructions in [README.md](../README.md)).

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

