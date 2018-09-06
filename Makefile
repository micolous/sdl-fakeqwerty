# -*- mode: makefile; indent-tabs-mode: tabs; tab-width: 2 -*-
PREFIX ?= /usr/local
STRIP = strip -sgxX
# This line disables stripping debug symbols:
# STRIP = echo

all: amd64 i686

# SDL 1.2
AMD64_LIBS += sdl1-hooks-amd64.so
sdl1-hooks-amd64.so: sdl1-hooks.c
	gcc -m64 -march=k8 -shared -fPIC -g -o $@ $< -ldl
	$(STRIP) $@

I686_LIBS += sdl1-hooks-i686.so
sdl1-hooks-i686.so: sdl1-hooks.c
	gcc -m32 -march=i686 -shared -fPIC -g -o $@ $< -ldl
	$(STRIP) $@

# SDL 2.0
AMD64_LIBS += sdl2-hooks-amd64.so
sdl2-hooks-amd64.so: sdl2-hooks.c
	gcc -m64 -march=k8 -shared -fPIC -g -o $@ $< -ldl
	$(STRIP) $@

I686_LIBS += sdl2-hooks-i686.so
sdl2-hooks-i686.so: sdl2-hooks.c
	gcc -m32 -march=i686 -shared -fPIC -g -o $@ $< -ldl
	$(STRIP) $@

OSX_LIBS += sdl2-hooks.dylib
sdl2-hooks.dylib: sdl2-hooks.c
	clang -o $@ -dynamiclib -ldl `sdl2-config --libs` -rpath @rpath/SDL2.framework/Versions/A/SDL2 -install_name ${PREFIX}/lib/$@ $<

# xlib
AMD64_LIBS += xlib-hooks-amd64.so
xlib-hooks-amd64.so: xlib-hooks.c
	gcc -m64 -march=k8 -shared -fPIC -g -o $@ $< -ldl
	$(STRIP) $@

I686_LIBS += xlib-hooks-i686.so
xlib-hooks-i686.so: xlib-hooks.c
	gcc -m32 -march=i686 -shared -fPIC -g -o $@ $< -ldl
	$(STRIP) $@

.PHONY: clean linux i686 amd64 osx install-osx

# Linux
amd64: $(AMD64_LIBS)
i686: $(I686_LIBS)

# OSX (EXPERIMENTAL!)
osx: $(OSX_LIBS)
install-osx: $(OSX_LIBS)
	install -m0644 $< "${PREFIX}/lib/"

clean:
	rm -f $(AMD64_LIBS) $(I686_LIBS) $(OSX_LIBS)

