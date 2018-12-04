all: main.o func.o
	gcc -o out main.o func.o

func.o: func.c
	gcc -c func.c

main.o: main.c func.h
	gcc -c main.c

run:
	./out

clean:
	rm out
	rm *.o
