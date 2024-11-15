#ifndef LIB_CAPTURE_H
#define LIB_CAPTURE_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void externalFunction(int value);
void InitCapture(void** cap, int camIdx, int width, int height, int fps);
void GetFrame(void* cap, unsigned char** buffer, int* rows, int* cols, int* channels);

#ifdef __cplusplus
}
#endif

#endif // LIB_CAPTURE_H
