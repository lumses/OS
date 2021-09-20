.PHONY: all clean

all:
	g++ child.cpp -o child
	g++ parent.cpp -o main 
	./main
clean:
	rm child main