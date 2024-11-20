#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
#define MIN_RED cv::Scalar(0, 128, 192)
#define MAX_RED cv::Scalar(7, 255, 255)
#define MIN_RED1 cv::Scalar(173, 128, 192)
#define MAX_RED1 cv::Scalar(180, 255, 255)
#define MIN_GREEN cv::Scalar(50, 152, 128)
#define MAX_GREEN cv::Scalar(100, 255, 255)
#define MIN_YELLOW cv::Scalar(12, 128, 183)
#define MAX_YELLOW cv::Scalar(30, 255, 216)

cv::Mat mian(cv::Mat img) {
    cv::Mat img_hsv, maskR1, maskR2, maskR, maskG, maskY, mask, image;
    cv::cvtColor(img, img_hsv, cv::COLOR_BGR2HSV);
    cv::inRange(img_hsv, MIN_RED, MAX_RED, maskR1);
    cv::inRange(img_hsv, MIN_RED1, MAX_RED1, maskR2);
    cv::bitwise_or(maskR1, maskR2, maskR);
    cv::inRange(img_hsv, MIN_GREEN, MAX_GREEN, maskG);
    cv::inRange(img_hsv, MIN_YELLOW, MAX_YELLOW, maskY);
    cv::bitwise_or(maskR, maskG, mask);
    cv::bitwise_or(mask, maskY, mask);
    image = img.clone();
    bool isEmp = true;
    std::vector<std::vector<cv::Point>> nengjinshou_g;
    std::vector<cv::Vec4i> successhaonan_g;
    cv::findContours(maskG, nengjinshou_g, successhaonan_g, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto& bear : nengjinshou_g){
        cv::Rect rect = cv::boundingRect(bear);
        int x = rect.x;
        int y = rect.y;
        int w = rect.width;
        int h = rect.height;
        if (w > 35 && h > 35){
            isEmp = false;
            cv::rectangle(img, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), 2);
            cv::putText(image, "GREEN", cv::Point(10, 120), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(239, 175, 47), 2);
        }
    }
    std::vector<std::vector<cv::Point>> nengjinshou_r;
    std::vector<cv::Vec4i> successhaonan_r;
    cv::findContours(maskR, nengjinshou_r, successhaonan_r, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto& bear : nengjinshou_r){
        cv::Rect rect = cv::boundingRect(bear);
        int x = rect.x;
        int y = rect.y;
        int w = rect.width;
        int h = rect.height;
        if (w > 25 && h > 25){
            isEmp = false;
            cv::rectangle(img, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 0, 255), 2);
            cv::putText(image, "RED", cv::Point(10, 80), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(239, 175, 47), 2);
        }
    }
    std::vector<std::vector<cv::Point>> nengjinshou_y;
    std::vector<cv::Vec4i> successhaonan_y;
    cv::findContours(maskY, nengjinshou_y, successhaonan_y, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto& bear : nengjinshou_y){
        cv::Rect rect = cv::boundingRect(bear);
        int x = rect.x;
        int y = rect.y;
        int w = rect.width;
        int h = rect.height;
        if (w > 25 && h > 25){
            isEmp = false;
            cv::rectangle(img, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 255), 2);
            cv::putText(image, "YELLOW", cv::Point(10, 160), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(239, 175, 47), 2);
        }
    }
    if(isEmp) cv::putText(image, "NOT", cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(239, 175, 47), 2);
    return image;
}

int main() {
    // cv::Mat img = cv::imread("C:/Users/33554/Documents/learn/homew/cppopencv/image/random - frame at 0m11s.jpg");
    // img = mian(img);
    // cv::imshow("img", img);
    // cv::waitKey(0);
    // cv::destroyAllWindows();
    // cv::VideoCapture cap("C:/Users/33554/Documents/learn/homew/cppopencv/video/move_red_yellow.avi");
    // cv::VideoCapture cap("C:/Users/33554/Documents/learn/homew/cppopencv/video/move_green.avi");
    cv::VideoCapture cap("C:/Users/33554/Documents/learn/homew/cppopencv/video/random.avi");
    // cv::VideoCapture cap(0, cv::CAP_DSHOW);
    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }
    while (1) {
        cv::Mat frame_ori, frame;
        cap >> frame_ori;
        if (frame_ori.empty()) {
            break;
        }
        cv::resize(frame_ori, frame, cv::Size(640, 480));
        frame = mian(frame);
        cv::imshow("Frame", frame);
        if (cv::waitKey(10) == 'q') {
            break;
        }
    }
    return 0;
}