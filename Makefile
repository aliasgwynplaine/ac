CC = gcc
SRCFILES = ac.c
OBJ = $(SRCFILES:.c=.o)
INC_FLAGS = -g -D_DEBUG -Wall
LDFLAGS = 

ex1.exe: ac.o outils.o
	$(CC) $(@:.exe=.c) $^ -o $@ $(INC_FLAGS) -g $(LDFLAGS)

ex3.exe: ac.o outils.o
	$(CC) $(@:.exe=.c) $^ -o $@ $(INC_FLAGS) -g $(LDFLAGS)

ex4.exe: ac.o outils.o
	$(CC) $(@:.exe=.c) $^ -o $@ $(INC_FLAGS) -g $(LDFLAGS)

ac.o: outils.o
	$(CC) -c $(@:.o=.c) $^ -o $@ $(INC_FLAGS) -g

outils.o:
	$(CC) -c $(@:.o=.c) -o $@ $(INC_FLAGS) -g $(LDFLAGS)

.PHONY: clean
clean:
	rm *.exe *.o

.PHONY: clean_all