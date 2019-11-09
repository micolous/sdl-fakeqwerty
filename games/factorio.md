# Factorio

> **Note:** Factorio allows you to configure keybindings. If you use this library, these should be set to the defaults (based on a QWERTY layout).

## Linux

Copy the compiled `xlib-hooks-amd64.so` file into `SteamLibrary/SteamApps/common/Factorio/`.

[Set the Steam launch options][steam-launch-opts]:

```
LD_PRELOAD="./xlib-hooks-amd64.so" %COMMAND%
```

Then run Factorio through Steam as normal.

[steam-launch-opts]: https://support.steampowered.com/kb_article.php?ref=5623-QOSV-5250
