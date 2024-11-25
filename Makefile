CC=g++

FLAGS=-c

all: hello
		hello1

hello: main.o tree.o akinator.o recovery.o reader.o
	$(CC) main.o tree.o akinator.o recovery.o reader.o -o hello1

tree.o: tree.cpp
	$(CC) $(FLAGS) tree.cpp

akinator.o: akinator.cpp
	$(CC) $(FLAGS) akinator.cpp
	
recovery.o: recovery.cpp
	$(CC) $(FLAGS) recovery.cpp

reader.o: reader.cpp
	$(CC) $(FLAGS) reader.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp