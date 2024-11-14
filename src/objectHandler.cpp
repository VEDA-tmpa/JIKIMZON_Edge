#include "objectHandler.hpp"

#include <opencv2/opencv.hpp>

ObjectHandler* ObjectHandler::sInstance = nullptr;

ObjectHandler& ObjectHandler::GetInstance()
{
    if (sInstance == nullptr)
    {
        sInstance = new ObjectHandler;
    }
    return *sInstance;
}

void ObjectHandler::InitModel(std::string path)
{
    mMobileNet = cv::dnn::readNetFromTensorflow(path);
}

cv::Mat ObjectHandler::DetectObject(cv::Mat& frame)
{
    // 이미지를 모델 입력 크기에 맞추기
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300), cv::Scalar(127.5, 127.5, 127.5), false, false);
    
    // 모델에 이미지 입력
    mMobileNet.setInput(blob);

    // 모델 추론
    cv::Mat output = mMobileNet.forward();

    return output;
}