# sdl-fakeqwerty

This makes it so that your keyboard looks like a US-QWERTY keyboard to Allegro, SDL 1.2, SDL 2.0 and Unity games, while not changing any system settings.  This is ideal for games with difficult or impossible to change keybindings [which get messed up using a non-QWERTY keyboard](./background.md).

This library intercepts SDL's or Xlib's event system in order to rewrite the `sym` to be like what a US-QWERTY keyboard would return using.  When activated on a non-QWERTY keyboard, it means these games will have keyboard shortcuts with the same physical positions as a QWERTY keyboard.  eg: `W A S D` bindings become `Comma A O E` on US-Dvorak, or `Z Q S D` on a French AZERTY keyboard.

This means you no longer have to change keybindings to play a single game, and the remapping is isolated to a single application (window) and automated.

I've mainly tested this with some Introversion games.  It might fix some other games as well.

Key labels shown in game will probably be displayed incorrectly as a result of using this library.

> **Note:** This will only work on Linux systems, as it relies on `LD_PRELOAD` to work.  There is limited support on OSX (Prison Architect).  I don't have interest in porting this code to other platforms.

## Documentation

* [Building this library](./building.md)
* [Games list](./games/README.md)
* [License agreement](./COPYING.md)
