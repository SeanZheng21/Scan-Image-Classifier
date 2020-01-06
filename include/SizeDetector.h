//
// Created by xizheng on 12/13/19.
//

#ifndef PROJET_OPENCV_CMAKE_SIZEDETECTOR_H
#define PROJET_OPENCV_CMAKE_SIZEDETECTOR_H

#include <string>
#include <opencv2/core/mat.hpp>
#include <matcher.h>

class SizeDetector {
public:
    const static int NONE = 0;
    const static int SMALL = 1;
    const static int MEDIUM = 2;
    const static int LARGE = 3;
    SizeDetector();
    int detectSize(const std::string& name);
    int detectSize(const cv::Mat& img);
    string detectSizeStr(const cv::Mat& img);

private:
    cv::Mat smallImg;
    cv::Mat mediumImg;
    cv::Mat largeImg;
    static Matcher* MATCHER;

};


#endif //PROJET_OPENCV_CMAKE_SIZEDETECTOR_H
