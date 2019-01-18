MAIN_O = src/obj/main.o
LUT_O = src/obj/lut.o
IMAGE_O = src/obj/image.o
HISTOGRAM_O = src/obj/histogram.o
OBJ = src/obj/main.o src/obj/lut.o src/obj/image.o src/obj/histogram.o

PROG = bin/minigimp

CC = gcc
CFLAGS = -Wall -O2 -g3


all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROG)
	@echo "*** to execute, type : ./bin/minigimp & ***"

$(MAIN_O) : src/main.c src/image.h src/lut.h  src/histogram.h
	@echo "compile main"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(IMAGE_O) : src/image.c src/image.h src/pixel.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(LUT_O) : src/lut.c src/lut.h src/image.h
	@echo "compile lut"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(HISTOGRAM_O) : src/histogram.c src/histogram.h src/image.h
	@echo "compile histogram"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"