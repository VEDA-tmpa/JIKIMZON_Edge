#include "libcapture.h"
#include <stdio.h>

int main() {
    void* cap;
    InitCapture(&cap, 0, 640, 480, 30);

    unsigned char* buffer;
    int rows, cols, channels;

    GetFrame(cap, &buffer, &rows, &cols, &channels);

    if (buffer) {
        printf("Frame captured: %dx%d with %d channels\n", rows, cols, channels);
    } else {
        printf("Failed to capture frame\n");
    }

    //externalFunction(42);

    free(cap);

    return 0;
}

// g++ -c libcapture.cpp -o libcapture.o `pkg-config --cflags opencv4`
// g++ -shared -o libcapture.so libcapture.o `pkg-config --libs opencv4`
// gcc -o main main.c -L. -lcapture