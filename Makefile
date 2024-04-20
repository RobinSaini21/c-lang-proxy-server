all: buildfile/build

buildfile/build: main.o windows_proxy_server.o
	gcc -Wall main.o windows_proxy_server.o -o buildfile/build -lws2_32

main.o: main.c
	gcc -Wall -c main.c

windows_proxy_server.o: windows_proxy_server.c
	gcc -Wall -c windows_proxy_server.c

clean:
	rm -f *.o buildfile/build
