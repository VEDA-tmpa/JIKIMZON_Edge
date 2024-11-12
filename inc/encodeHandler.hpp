#ifndef JIKIMZON_ENCODEHANDLER_H
#define JIKIMZON_ENCODEHANDLER_H

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/imgutils.h>
}

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

class EncodeHandler {
public:
    EncodeHandler(int width, int height, int bitrate, int fps);
    ~EncodeHandler();

    static EncodeHandler* GetInstance(int width, int height, int bitrate, int fps)
    {
        if (instance == NULL)
        {
            instance = new EncodeHandler(width, height, bitrate, fps);
        }
        return instance;
    }

    void encodeFrame(cv::Mat& frame, std::vector<uint8_t>& encodedFrame);
private:
    void initEncoder();

    AVCodecContext* mCodecContext;
    int mWidth, mHeight, mBitrate, mFps;
    static EncodeHandler* instance;
    std::ofstream mOutputFile;
};


#endif