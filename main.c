#include <stdio.h>


#ifdef _WIN32
    // Windows-specific header files
    #include <windows.h>
    #include "windows_proxy_server.h"
#elif __linux__
    // Linux-specific header files
    #include <unistd.h>
    #include "linux_proxy_server.h"
#else
    #error "Unsupported operating system"
#endif

int main() {
    #ifdef _WIN32
        // Windows-specific code
        printf("This is Windows.\n");
    #elif __linux__
        // Linux-specific code
        printf("This is Linux.\n");
    #endif
    proxy_server();
    return 0;
}
