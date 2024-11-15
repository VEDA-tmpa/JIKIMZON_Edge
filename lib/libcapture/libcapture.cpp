#include "tmp.h"

#include <opencv2/opencv.hpp>

namespace
{

void internalFunction(int value)
{

}

void _initCapture(cv::VideoCapture* cap, int camIdx, int width, int height, int fps)
{
    cap = new cv::VideoCapture(camIdx, cv::CAP_V4L2);

    if (!cap->isOpened())
    {
        std::cerr << "cap is not opened" << std::endl;
        exit(EXIT_FAILURE);
    }

    cap->set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap->set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap->set(cv::CAP_PROP_FPS, fps);
}

}


// 외부 노출 함수
extern "C" void InitCapture(cv::VideoCapture* cap, int camIdx, int width, int height, int fps)
{
    _initCapture(cap, camIdx, width, height, fps);
}

extern "C" void externalFunction(int value)
{
    internalFunction(value);
}