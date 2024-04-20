# Determine the operating system
ifeq ($(OS),Windows_NT)
    # For Windows
    TARGET = windowsBuild/build.exe
    LIBS = -lws2_32
    COMPILE_PROXY_FILE = windows_proxy_server.c
else
    # For Linux
    TARGET = linuxBuild/build
    LIBS =
    COMPILE_PROXY_FILE = linux_proxy_server.c
endif

# Rules for building the target
all: $(TARGET)

$(TARGET): main.o proxy_server.o
	gcc -Wall main.o proxy_server.o -o $(TARGET) $(LIBS)

# Rules for compiling individual source files
main.o: main.c
	gcc -Wall -c main.c

proxy_server.o: $(COMPILE_PROXY_FILE)
	gcc -Wall -c $(COMPILE_PROXY_FILE) -o proxy_server.o

# Rule for cleaning up generated files
clean:
	rm -f *.o $(TARGET)
