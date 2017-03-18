.PHONY: clean

all: sdl2-hooks.so

sdl2-hooks.so: sdl2-hooks.c
	gcc -shared -fPIC sdl2-hooks.c -o sdl2-hooks.so -ldl

clean:
	rm -f sdl2-hooks.so

