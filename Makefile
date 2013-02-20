UNAME := $(shell uname)

MacGLFramework = -framework Carbon -framework OpenGL -framework GLUT
LinuxGLFramework = -lglut -lGLU -lGL
GLFramework = NOTYETSET

Include = -I/usr/include/GL -I/usr/include
Link = -L/usr/local/lib -lm
Flags = -g -o
Sources = src/*.cpp

CC = g++
ExeName = pa1

# Define proper GL framework
ifeq ($(UNAME), Linux)
	GLFramework = $(LinuxGLFramework)
endif
ifeq ($(UNAME), Darwin)
	GLFramework = $(MacGLFramework)
endif

all: main

# Compiling
main:
	$(CC) $(Flags) $(ExeName) $(Include) $(Link) $(Sources) $(GLFramework) 
	./$(ExeName)



clean:
	rm -f $(ExeName)
