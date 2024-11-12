#include "../inc/encodeHandler.hpp"

EncodeHandler* EncodeHandler::instance = nullptr;

EncodeHandler::EncodeHandler(int width, int height, int bitrate, int fps)
                    : mCodecContext(nullptr), mWidth(width), mHeight(height), mBitrate(bitrate), mFps(fps) {
    initEncoder();
    mOutputFile.open("output.h264", std::ios::binary);
    if (!mOutputFile.is_open()) {
        perror("Cannot open output file");
    }
}

EncodeHandler::~EncodeHandler() {
    if (mCodecContext) {
        avcodec_free_context(&mCodecContext);
    }
    if (mOutputFile.is_open()) {
        mOutputFile.close();
    }
}

void EncodeHandler::initEncoder() {
    const AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!codec) {
        perror("Codec not found");
    }

    mCodecContext = avcodec_alloc_context3(codec);
    if (!mCodecContext) {
        perror("Cannot allocate codec context");
    }

    mCodecContext->bit_rate = 400000;
    mCodecContext->width = mWidth;
    mCodecContext->height = mHeight;
    mCodecContext->time_base = {1, mFps};
    mCodecContext->framerate = {mFps, 1};
    mCodecContext->gop_size = 10;
    mCodecContext->max_b_frames = 1;
    mCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;

    if (avcodec_open2(mCodecContext, codec, nullptr) < 0) {
        perror("Cannot open codec");
    }
}

void EncodeHandler::encodeFrame(cv::Mat& frame, std::vector<uint8_t>& encodedFrame) {
    AVFrame* avFrame = av_frame_alloc();
    avFrame->format = mCodecContext->pix_fmt;
    avFrame->width = mCodecContext->width;
    avFrame->height = mCodecContext->height;
    av_image_alloc(avFrame->data, avFrame->linesize, mCodecContext->width, mCodecContext->height, mCodecContext->pix_fmt, 32);

    cv::Mat yuvFrame;
    cv::cvtColor(frame, yuvFrame, cv::COLOR_BGR2YUV_I420);
    memcpy(avFrame->data[0], yuvFrame.data, mCodecContext->width * mCodecContext->height);
    memcpy(avFrame->data[1], yuvFrame.data + mCodecContext->width * mCodecContext->height, mCodecContext->width * mCodecContext->height / 4);
    memcpy(avFrame->data[2], yuvFrame.data + mCodecContext->width * mCodecContext->height * 5 / 4, mCodecContext->width * mCodecContext->height / 4);

    AVPacket pkt;
    av_init_packet(&pkt);
    pkt.data = nullptr;
    pkt.size = 0;

    int ret = avcodec_send_frame(mCodecContext, avFrame);
    if (ret < 0) {
        perror("Error: send frame to encoder");
    }

    ret = avcodec_receive_packet(mCodecContext, &pkt);
    if (ret == 0) {
        encodedFrame.assign(pkt.data, pkt.data + pkt.size);
        mOutputFile.write(reinterpret_cast<const char*>(pkt.data), pkt.size);
        av_packet_unref(&pkt);
    }

    av_freep(&avFrame->data[0]);
    av_frame_free(&avFrame);
}