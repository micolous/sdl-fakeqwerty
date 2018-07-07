# Background on sdl-fakeqwerty

## How do applications see key presses?

When you press a key on your keyboard, the operating system (or windowing environment) typically passes three pieces of information to the current application:

1. The scan code for the key that you pressed, supplied by your keyboard.

   These correspond to the physical location of the key you pressed, and are mostly the same for every keyboard layout.

2. Any modifier keys that have been held (eg: shift, AltGr).

3. The key code (or keysym) for the key that you pressed, supplied by your operating system.

   Your operating system builds this from the configured keyboard layout, the scan code and modifier keys.

   This corresponds to the letter printed on the key that you pressed.

> _Note:_ An [input method editor (IME)](https://en.wikipedia.org/wiki/Input_method) is more complex than this -- it will typically intercept the keystrokes before it reaches the application, and then send an IME event containing composed characters.

> _Note:_ Some keyboards support "hardware layout switching", which moves keyboard layout selection from the OS into hardware. This typically results in the OS always beliving it has a US-QWERTY keyboard attached.

## How can games handle keyboard input?

A game developer can choose how to interpret a key press when assigning it to an action (like move forward):

1. The developer can assign an action to a _key code_ (letter).

   This will assign the action to a specific letter (eg: W).

2. The developer can assign an action to a _scan code_.

   This will assign the action to a specific key position (eg: 25).

If they use _scan codes_, they can:

1. Look up the operating system's key map, and display the key in the UI correctly, or,

2. Use a hard-coded key map -- normally whatever the developer uses (typically US-QWERTY).

## What's wrong with key codes?

Using key codes (letters) to assign actions makes the games largely unplayable if you don't have the same keyboard layout as the developer.

The fact that the options menu of a game shows letters, or has QWERTY bindings by default, doesn't indicate whether they use scan codes or key codes.  They could also use scan codes without correctly consulting the operating system's keymap.

A developer can make this worse by not allowing you to modify keybindings on first start-up, or _inconsistently_ use scan codes and key codes (eg: the options menu uses key codes, but the game uses scan codes).

## How does this library solve it?

This library rewrites incoming input events before it reaches the game, so that it is like the system keymap was set to QWERTY.

There are a few different versions of the library (SDL 1.2, SDL 2.0 and Xlib) which use slightly different approaches to solving the issue.

In effect, any game which assigns actions to _key code_ will now have them assigned to _scan codes_ with a hard-coded keymap.

This does mean the UI will still _show_ the wrong key, but the position of the keys won't be jumbled anymore.

## Does this make 

## How should games handle keyboard input?

The correct way to handle keyboard input is to assign all actions to scan codes, and then reference the operating system's keymap when displaying a key label in the UI.

This way, when you start playing a game for the first time, it doesn't matter what your keyboard layout is, all the tutorials and menus will display it correctly.  Most of the time, the key positions will be what the developer intended (eg: WASD-style movement keys will be in an equivalent inverse-T orientation on the 2nd and 3rd row).

All games should support changing the key bindings, even before entering a tutorial.  Some players prefer different orientations of movement keys, either because they use a mouse with their left hand, or may otherwise find it difficult to use a default key configuration.

Some developers use scan codes but _don't reference the operating system's keymap_ (or do so incorrectly).  The game is mostly playable, but it does mean that keyboard shortcuts in tutorials displayed are incorrectly.  This library _does not_ attempt to resolve that issue.

## Providing a keyboard layout switch in-game

This is a hack around the problem, and doesn't address the issue correctly.

Additionally, it's not possible for one to anticipate all of the layouts that _might_ be used with a game.

## What other alternatives are there for players?

You could manually change the keymap before starting each game.

This is tedious, and this library aims to be a "set and forget" solution.

