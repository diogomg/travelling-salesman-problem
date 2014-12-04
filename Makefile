CC = g++
CPPFLAGS = -Wall -g3
LDFLAGS = -lm
PNAME = caixeiro

all: compile clean run

compile: $(PNAME).cpp
	$(CC) ${CPPFLAGS} $(PNAME).cpp grafo.cpp ${LDFLAGS} -o $(PNAME)

valgrind: compile clean
	valgrind --tool=memcheck --leak-check=yes -v ./$(PNAME)

run:
	./$(PNAME)

clean: *.o
	rm *.o
