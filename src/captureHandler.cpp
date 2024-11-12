#include "../inc/captureHandler.hpp"
#include "../inc/tcpHandler.hpp"
#include "../inc/encodeHandler.hpp"

#include <opencv2/opencv.hpp>

CaptureHandler* CaptureHandler::instance = nullptr;

CaptureHandler::CaptureHandler() {}
CaptureHandler::~CaptureHandler() {}

void CaptureHandler::StartCapture()
{
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cerr << "cap is not opened" << std::endl;
        exit(EXIT_FAILURE);
    }


    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    std::vector<uint8_t> encodedFrame;

    cv::Mat frame;
    // cap >> frame;
    // std::cout << frame.type() << std::endl;

    while (true) {
        cap >> frame;

        // 전처리
        
        // h.264 압축
        EncodeHandler::GetInstance(width, height, 1000000, 30)->encodeFrame(frame, encodedFrame);

        // tcp 전송
        // TcpHandler::GetInstance()->SendFrame(encodedFrame);
    }
}