#ifndef JIKIMZON_CAPTUREHANDLER_H
#define JIKIMZON_CAPTUREHANDLER_H

#include <iostream>

#define WIDTH   1280
#define HEIGHT  720

class CaptureHandler {
public:
    CaptureHandler(const CaptureHandler&) = delete;
    CaptureHandler& operator=(const CaptureHandler&) = delete;

    static CaptureHandler& GetInstance();
    void StartCapture();

private:
    CaptureHandler() = default;
    ~CaptureHandler() = default;
    static CaptureHandler* sInstance;
};

#endif