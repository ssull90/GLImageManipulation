all: main.cpp HW0

SOURCES    = main.cpp
OBJECTS    = $(SOURCES:.cpp=.o)

.cpp.o:
	g++ -c -Wall $< -o $@

HW0: main.o
	g++ $(OBJECTS) -lGL -lGLU -lglut $(LDFLAGS) -o $@

clean:
	rm -f *.o

