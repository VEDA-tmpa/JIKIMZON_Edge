#ifndef JIKIMZON_ENCODEHANDLER_H
#define JIKIMZON_ENCODEHANDLER_H

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>

    // int avcodec_open2(AVCodecContext *avctx, AVCodec *codec, AVDictionary **options);
}

#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

class EncodeHandler {
public:
    EncodeHandler(const EncodeHandler&) = delete;
    EncodeHandler& operator=(const EncodeHandler&) = delete;

    static EncodeHandler& GetInstance();

    void EncodeFrame(cv::Mat& frame, std::vector<uint8_t>& encodedFrame);

private:
    EncodeHandler(int width, int height, int bitrate, int fps) = default;
    ~EncodeHandler() = default;
    static EncodeHandler* sInstance;

    void InitEncoder();
    SwsContext* mSwsContext;
    AVCodecContext* mCodecContext;
    int mWidth, mHeight, mBitrate, mFps;
    std::ofstream mFS;
};


#endif