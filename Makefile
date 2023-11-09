CC=g++

CFLAGS=-c -Wall -std=c++11

LDFLAGS=-lglfw -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp -lGLEW -lEGL -lGL -lGLU -lOpenGL 

SOURCES=camera.cpp house.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=parametric_house

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
