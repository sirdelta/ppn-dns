#

CC=gcc
CFLAGS=-Wconversion -Wall -Wextra
HEAD=-I include -I include/config

#
all: setup src_obj tests_obj exec

setup:
	mkdir -p build build/bin doc

#
src_obj: parser.o compress.o dns_proto.o io.o serialize.o \
alloc.o rand.o main.o

tests_obj: tests_packet.o

exec: p2i

#
%.o: src/database/%.c
	$(CC) $(CFLAGS) -c $< -o build/$@ $(HEAD)

%.o: src/layers/%.c
	$(CC) $(CFLAGS) -c $< -o build/$@ $(HEAD)

%.o: src/packets/%.c
	$(CC) $(CFLAGS) -c $< -o build/$@ $(HEAD)

%.o: src/tools/%.c
	$(CC) $(CFLAGS) -c $< -o build/$@ $(HEAD)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o build/$@ $(HEAD)

%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o build/$@ $(HEAD)

#
p2i: build/parser.o build/compress.o build/dns_proto.o build/io.o \
build/serialize.o build/alloc.o build/rand.o \
build/main.o
	$(CC) $(CFLAGS) $^ -o build/bin/$@ $(HEAD)

#
clean:
	rm -Rf build/*
