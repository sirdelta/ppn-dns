CC=gcc
LDFLAGS	=-L/usr/lib/x86_64-linux-gnu -I/usr/include -lcmocka -lm
all : test
test:  test.c table.c table.h  
	$(CC) $(LDFLAGS) test.c table.c -o $@
clean :
	rm -Rf *.o test
	
