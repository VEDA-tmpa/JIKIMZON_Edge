#include "v4l2Handler.hpp"
#include "tcpHandler.hpp"

#include <opencv2/opencv.hpp>

V4L2Handler* V4L2Handler::instance = nullptr;

V4L2Handler::V4L2Handler() {}
V4L2Handler::~V4L2Handler() {}

void V4L2Handler::StartCapture()
{
    cv::VideoCapture cap(0, cv::CAP_V4L2);
    
    if (!cap.isOpened()) {
        std::cerr << "cap is not opened" << std::endl;
        exit(EXIT_FAILURE);
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);

    TcpHandler::GetInstance()->InitSocket();

    cv::Mat frame;

    while (true) {
        if (!cap.read(frame)) {
            //std::cerr << "Failed to capture frame" << std::endl;
            continue;
        }

        if (frame.empty()) {
            std::cerr << "Empty frame" << std::endl;
            continue;
        }

        // 전처리
        
        // h.264 압축

        // tcp 전송
        TcpHandler::GetInstance()->SendFrame(frame);
    }

}