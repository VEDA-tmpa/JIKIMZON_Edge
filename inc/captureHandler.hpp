#ifndef JIKIMZON_CAPTUREHANDLER_H
#define JIKIMZON_CAPTUREHANDLER_H

#include <iostream>

#define WIDTH   1280
#define HEIGHT  720

class CaptureHandler {
public:
    CaptureHandler();
    ~CaptureHandler();

    void StartCapture();

    static CaptureHandler* GetInstance()
    {
        if (instance == NULL)
        {
            instance = new CaptureHandler();
        }
        return instance;
    }

private:
    static CaptureHandler* instance;

};

#endif