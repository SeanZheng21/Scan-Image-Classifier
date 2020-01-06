//
// Created by xizheng on 11/28/19.
//

#ifndef PROJET_OPENCV_CMAKE_MATCHER_H
#define PROJET_OPENCV_CMAKE_MATCHER_H

#include <iostream>
using namespace std;

#include "opencv2/imgproc.hpp"
using namespace cv;

void performSift();


class Matcher {
private:
    static float DEFAULT_RATIO;
    static int DEFAULT_HESS;

    float ratio_thresh;
    int hess;

public:
    Matcher(float ratio, int hessMin) : ratio_thresh(ratio), hess(hessMin) {};
    Matcher() : Matcher(DEFAULT_RATIO, DEFAULT_HESS) {};
    string classifyImage( const cv::Mat& img);
    int surf(const cv::Mat& mat, const std::string& qry);
    int surf(const cv::Mat& mat, const cv::Mat& img);
};


#endif //PROJET_OPENCV_CMAKE_MATCHER_H