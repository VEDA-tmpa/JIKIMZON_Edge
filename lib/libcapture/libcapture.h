#ifndef TMP_LIBRARY_H
#define TMP_LIBRARY_H

#ifndef __cplusplus
extern "C" {
#endif

void externalFunction(int value);
void InitCapture(cv::VideoCapture* cap, int camIdx);

#ifndef __cplusplus
}
#endif

#endif