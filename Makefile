all: mywords
mywords: activity2.o
	gcc activity2.o -o mywords
activity2.o: activity2.c
	gcc -c activity2.c -o activity2.o
clean:
	rm -f mywords activity2.o core *~

