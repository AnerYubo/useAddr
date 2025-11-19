CC=gcc

all: libsourceip.so useAddr

libsourceip.so:
	$(CC) -shared -fPIC -o libsourceip.so src/sourceip.c -ldl

useAddr:
	$(CC) -o useAddr src/useAddr.c

install:
	cp libsourceip.so /usr/local/lib/
	cp useAddr /usr/local/bin/

clean:
	rm -f libsourceip.so useAddr
