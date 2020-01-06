//
// Created by xizheng on 12/4/19.
//

#ifndef PROJET_OPENCV_CMAKE_SQUAREEXTRACTOR_H
#define PROJET_OPENCV_CMAKE_SQUAREEXTRACTOR_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <string>

std::vector<cv::Mat> extract(cv::Mat input, int ur_X, int ur_Y, int ll_X, int ll_Y);
cv::Mat getSquare(cv::Mat src, int x, int y, int disX, int disY);

#endif //PROJET_OPENCV_CMAKE_SQUAREEXTRACTOR_H