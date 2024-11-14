#ifndef JIKIMZON_OBJECTHANDLER_H
#define JIKIMZON_OBJECTHANDLER_H

#include <opencv2/opencv.hpp>

class ObjectHandler {
public:
    ObjectHandler(const ObjectHandler&) = delete;
    ObjectHandler& operator=(const ObjectHandler&) = delete;

    static ObjectHandler& GetInstance();
    void InitModel(std::string);
    cv::Mat DetectObject(cv::Mat&);

private:
    ObjectHandler() = default;
    ~ObjectHandler() = default;
    static ObjectHandler* sInstance;
    cv::dnn::Net mMobileNet;
};

#endif