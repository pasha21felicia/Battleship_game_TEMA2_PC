build: 
	gcc -Wall -o battleship battleship.c main.c -lncurses
run:
	./battleship test1.data test2.data test3.data
clean:
	rm battleship