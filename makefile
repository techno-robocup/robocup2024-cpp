SRC = main.cpp
all: $(SRC)
	docker run --rm -v .:/src rotarymars/ev3devcc-autobuild

