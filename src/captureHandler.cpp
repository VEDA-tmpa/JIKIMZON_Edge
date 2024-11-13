#include "../inc/captureHandler.hpp"
#include "../inc/tcpHandler.hpp"
#include "../inc/encodeHandler.hpp"

#include <opencv2/opencv.hpp>

CaptureHandler* CaptureHandler::instance = nullptr;

CaptureHandler::CaptureHandler() {}
CaptureHandler::~CaptureHandler() {}

void CaptureHandler::StartCapture()
{
    cv::VideoCapture cap(0, cv::CAP_V4L2);
    
    if (!cap.isOpened()) {
        std::cerr << "cap is not opened" << std::endl;
        exit(EXIT_FAILURE);
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);
    cap.set(cv::CAP_PROP_FPS, 30);

    TcpHandler::GetInstance()->InitSocket();

    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    std::vector<uint8_t> encodedFrame;

    cv::Mat frame;

    while (true) {
        if (!cap.read(frame))
        {
            // std::cerr << "Failed to capture frame" << std::endl;
            continue;
        }

        if (frame.empty())
        {
            //std::cerr << "Empty frame" << std::endl;
            continue;
        }

        // 전처리
        
        // h.264 압축
        EncodeHandler::GetInstance(width, height, 1000000, 30)->encodeFrame(frame, encodedFrame);

        // tcp 전송
        TcpHandler::GetInstance()->SendFrame(encodedFrame);
    }
}