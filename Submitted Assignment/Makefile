CC = gcc
CFLAGS = -Wall

COMPILE = $(CC) $(CFLAGS)

autocomplete1 : StageOne.o create_and_insert.o io-one.o find_and_traverse.o
	$(COMPILE) -o autocomplete1 StageOne.o create_and_insert.o io-one.o find_and_traverse.o

autocomplete2 : StageTwo.o create_and_insert2.o io-two.o find_and_traverse2.o sort.o
	$(COMPILE) -o autocomplete2	StageTwo.o create_and_insert2.o io-two.o find_and_traverse2.o sort.o

StageOne.o : StageOne.c
	$(COMPILE) -c StageOne.c

StageTwo.o : StageTwo.c
	$(COMPILE) -c StageTwo.c

create_and_insert.o : create_and_insert.c autocomplete1.h
	$(COMPILE) -c create_and_insert.c 

create_and_insert2.o : create_and_insert2.c autocomplete2.h
	$(COMPILE) -c create_and_insert2.c 

find_and_traverse.o : find_and_traverse.c autocomplete1.h
	$(COMPILE) -c find_and_traverse.c 	

find_and_traverse2.o : find_and_traverse2.c autocomplete2.h
	$(COMPILE) -c find_and_traverse2.c 	

io-one.o : io-one.c autocomplete1.h
	$(COMPILE) -c io-one.c

io-two.o : io-two.c autocomplete2.h
	$(COMPILE) -c io-two.c

sort.o : sort.c autocomplete2.h
	$(COMPILE) -c sort.c