all: setup compile run

dev: compile run

setup:
	meson setup build

compile:
	meson compile -C ./build/

run:
	./build/bin $(ARGS)
