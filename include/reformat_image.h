//
// Created by brdaniel on 11/12/19.
//

#ifndef PROJET_OPENCV_CMAKE_REFORMAT_IMAGE_H
#define PROJET_OPENCV_CMAKE_REFORMAT_IMAGE_H

#include <iostream>
#include <math.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#define PI 3.14159265
#define HEIGHT 2650.0
#define WIDTH 2200.0
using namespace std;
using namespace cv;

void rotateImage(Mat src, Mat dst, Point rot_pt, double angle);
double computeRotationAngle(Point bas, Point haut);

#endif //PROJET_OPENCV_CMAKE_REFORMAT_IMAGE_H
