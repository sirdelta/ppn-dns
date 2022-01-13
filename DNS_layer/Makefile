CC=gcc
CXX=g++
LD_FLAGS=-Wl,-rpath=$(PWD)

all: client server

libio.so: io.c
	$(CC) -shared -fpic $^ -o $@ 


server: server.cpp libio.so
	$(CXX) server.cpp -o $@ -lpthread -L. -lio $(LD_FLAGS)


client: client.c libio.so
	$(CC) client.c -o $@ -lpthread -L. -lio $(LD_FLAGS)

clean:
	rm -f client server libio.so