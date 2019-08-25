PROGRAM = cm
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL 

$(PROGRAM): ChoreoMaker.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) ChoreoMaker.o $(LDLIBS)

