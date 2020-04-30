huffman: huffman.o main.o
	@gcc huffman.o main.o -o huffman && rm -f huffman.o && rm -f main.o && echo "Compilé, vous pouvez à présent utiliser la compression huffman\nPour plus d'informations utilisez l'option -h\n"

huffman.o: huffman.c
	@gcc -c huffman.c -W -Wall -pedantic -o huffman.o

main.o: main.c huffman.h
	@gcc -c main.c -W -Wall -pedantic -o main.o
