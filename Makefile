CC=g++

FLAGS=-c

all: hello
		akinator

hello: main.o tree/tree.o akinator.o readrecover/recovery.o readrecover/reader.o
	$(CC) main.o tree/tree.o akinator.o readrecover/recovery.o readrecover/reader.o -o akinator

tree.o: tree/tree.cpp
	$(CC) $(FLAGS) tree/tree.cpp

akinator.o: akinator.cpp
	$(CC) $(FLAGS) akinator.cpp
	
recovery.o: readrecover/recovery.cpp
	$(CC) $(FLAGS) readrecover/recovery.cpp

reader.o: readrecover/reader.cpp
	$(CC) $(FLAGS) readrecover/reader.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp