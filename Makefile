CC=g++

CFLAGS=-c -Wall

LDFLAGS=-lglfw -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp -lGLEW -lEGL -lGL -lGLU -lOpenGL 

SOURCES=house.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=parametric_house

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
