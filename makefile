SRC = main.cpp
all:
	docker run --rm -v .:/src rotarymars/ev3devcc-autobuild

