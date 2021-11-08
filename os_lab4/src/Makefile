.PHONY: all clean

all:
	gcc -pthread child.c -o child -lrt -fsanitize=address
	gcc -pthread parent.c -lrt -fsanitize=address
clean:
	rm child