all: mate

mate: mate_plier.c
	$(CC) -o mate mate_plier.c -lm

install: mate
	sudo cp mate /usr/local/bin

clean:
	rm -f mate
