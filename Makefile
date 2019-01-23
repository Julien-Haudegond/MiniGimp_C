MAIN_O = src/obj/main.o
ARGUMENTS_O = src/obj/arguments.o
LUT_O = src/obj/lut.o
FILTERS_O = src/obj/filters.o
IMAGE_O = src/obj/image.o
HISTOGRAM_O = src/obj/histogram.o
OBJ = src/obj/main.o src/obj/arguments.o src/obj/lut.o src/obj/filters.o src/obj/image.o src/obj/histogram.o

PROG = bin/minigimp

CC = gcc
CFLAGS = -Wall -O2 -g3


all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROG)
	@echo "*** to execute, type : ./bin/minigimp lake_P6.ppm ADDLUM 30 ADDCON 45 FLIPFLOP -h -o lake_final.ppm ***"

$(MAIN_O) : src/main.c src/arguments.h src/image.h src/lut.h src/filters.h src/histogram.h
	@echo "compile main"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(ARGUMENTS_O) : src/arguments.c src/arguments.h
	@echo "compile arguments"
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

$(FILTERS_O) : src/filters.c src/filters.h src/image.h
	@echo "compile filters"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(HISTOGRAM_O) : src/histogram.c src/histogram.h src/image.h
	@echo "compile histogram"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"