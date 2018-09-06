/* -*- mode: c; indent-tabs-mode: nil; tab-width: 2
  sdl-fakeqwerty/helper.h
  Copyright 2018 Michael Farrell <micolous+git@gmail.com>
 
  Helper functions for sdl-fakeqwerty

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

#if defined(__APPLE__) && !defined(WRAPPED_RPATH)
#error "Must define WRAPPED_RPATH on OSX!"
#endif

#ifdef __APPLE__
#define dlsym_handle dlopen(WRAPPED_RPATH, RTLD_NOW)
#else
#define dlsym_handle RTLD_NEXT
#endif

#define GET_ORIG(FN) \
  static sig_ ## FN orig_ ## FN = NULL; \
  if (orig_ ## FN == NULL) { \
    orig_ ## FN = (sig_ ## FN)dlsym(dlsym_handle, #FN); \
  }

