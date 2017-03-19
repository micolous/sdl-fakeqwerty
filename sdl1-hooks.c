/* -*- mode: c; indent-tabs-mode: nil; tab-width: 2
  sdl-fakeqwerty/sdl1-hooks.c
  Copyright 2017 Michael Farrell <micolous+git@gmail.com>
 
  Hook some SDL1.2 related input functionality and make it look like there is a
  QWERTY keyboard attached for applications which read the "sym" (SDL_Keycode).

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define _GNU_SOURCE
#include <dlfcn.h>
#include <SDL/SDL_events.h>

const char* qwerty_syms = "1234567890-=\0\0qwertyuiop[]\\\0asdfghjkl;'`\0\0zxcvbnm,./";


typedef int (*orig_SDL_PollEvent_sig)(SDL_Event* event);

int SDL_PollEvent(SDL_Event* event) {
  orig_SDL_PollEvent_sig orig_SDL_PollEvent = (orig_SDL_PollEvent_sig)dlsym(RTLD_NEXT, "SDL_PollEvent");

  int ret = orig_SDL_PollEvent(event);
  
  if (ret == 1) {
    // There is an event which we should try to mangle.
    if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {

      if (event->key.keysym.scancode >= 0x0A && event->key.keysym.scancode <= 0x3d) {
        uint16_t new_sym = (uint8_t)qwerty_syms[event->key.keysym.scancode - 0x0a];

        if (new_sym != 0) {
          event->key.keysym.sym = new_sym;
        }
      }

    }
  }

  return ret;
}

