/* -*- mode: c; indent-tabs-mode: nil; tab-width: 2
  sdl-fakeqwerty/sdl2-hooks.c
  Copyright 2017 Michael Farrell <micolous+git@gmail.com>
 
  Hook some SDL2 related input functionality and make it look like there is a
  QWERTY keyboard attached for applications which read the "sym" (SDL_Keycode).

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
  
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
     
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
     
  3. This notice may not be removed or altered from any source distribution.
*/

#define _GNU_SOURCE
#include <dlfcn.h>
#include <SDL2/SDL_events.h>

typedef int (*orig_SDL_PollEvent_sig)(SDL_Event* event);

int SDL_PollEvent(SDL_Event* event) {
  static orig_SDL_PollEvent_sig orig_SDL_PollEvent = NULL;

  if (orig_SDL_PollEvent == NULL) {
#ifdef __APPLE__
    // EXPERIMENTAL!
    void *handle = dlopen("@rpath/SDL2.framework/Versions/A/SDL2", RTLD_NOW);
    orig_SDL_PollEvent = (orig_SDL_PollEvent_sig)dlsym(handle, "SDL_PollEvent");
#else
    orig_SDL_PollEvent = (orig_SDL_PollEvent_sig)dlsym(RTLD_NEXT, "SDL_PollEvent");
#endif
  }

  int ret = orig_SDL_PollEvent(event);
  if (ret == 1) {
    // There is an event which we should try to mangle.
    if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
      SDL_Keycode fixed_sym = SDL_GetKeyFromName(SDL_GetScancodeName(event->key.keysym.scancode));

      event->key.keysym.sym = fixed_sym;
    }
  }

  return ret;
}

