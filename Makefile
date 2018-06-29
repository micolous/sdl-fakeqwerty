PREFIX ?= /usr/local

all: i686 amd64

i686: sdl1-hooks-i686.so sdl2-hooks-i686.so xlib-hooks-i686.so

amd64: sdl1-hooks-amd64.so sdl2-hooks-amd64.so xlib-hooks-amd64.so

sdl1-hooks-amd64.so: sdl1-hooks.c
	gcc -m64 -march=k8 -shared -fPIC -g -o $@ $< -ldl

sdl1-hooks-i686.so: sdl1-hooks.c
	gcc -m32 -march=i686 -shared -fPIC -g -o $@ $< -ldl

sdl2-hooks-amd64.so: sdl2-hooks.c
	gcc -m64 -march=k8 -shared -fPIC -g -o $@ $< -ldl

sdl2-hooks-i686.so: sdl2-hooks.c
	gcc -m32 -march=i686 -shared -fPIC -g -o $@ $< -ldl

xlib-hooks-amd64.so: xlib-hooks.c
	gcc -m64 -march=k8 -shared -fPIC -g -o $@ $< -ldl

xlib-hooks-i686.so: xlib-hooks.c
	gcc -m32 -march=i686 -shared -fPIC -g -o $@ $< -ldl

clean:
	rm -f sdl1-hooks-amd64.so sdl1-hooks-i686.so
	rm -f sdl2-hooks-amd64.so sdl2-hooks-i686.so sdl2-hooks.dylib
	rm -f xlib-hooks-amd64.so xlib-hooks-i686.so

# OSX (EXPERIMENTAL!)
osx: sdl2-hooks.dylib

sdl2-hooks.dylib: sdl2-hooks.c
	clang -o $@ -dynamiclib -ldl `sdl2-config --libs` -rpath @rpath/SDL2.framework/Versions/A/SDL2 -install_name ${PREFIX}/lib/$@ $<

install-osx: sdl2-hooks.dylib
	install -m0644 $< "${PREFIX}/lib/"

.PHONY: all clean i686 amd64 osx install-osx
