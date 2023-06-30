CC=g++
SRC=server.cpp client.cpp 
OBJ=$(SRC:.cpp=.o)
EXEC=server client

all: $(EXEC)

server: $(OBJ)
	$(CC) -o $@ $<

client: client.o
	$(CC) -o $@ $<

%.o: %.cpp
	$(CC) -o $@ -c $<

runserver: all 
	./server

runclient: all
	./client

clean:
	rm $(OBJ)
	rm $(EXEC)