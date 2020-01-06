//
// Created by rguill on 19/12/19.
//
#include "textscan.h"
#include <string>
#include <iostream>
#include <opencv2/core/cvdef.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

bool textscan(Mat src){
    Mat  edgesImage,block;
    Canny(src, edgesImage, 250, 500);
    //Noise deletion
    block = getStructuringElement(MORPH_RECT, Size(4, 4));
    dilate(edgesImage, edgesImage, block);
    erode(edgesImage, edgesImage, block);
    //Edge detection
    std::vector<Vec4i> lines;
    HoughLinesP(edgesImage, lines, 1, CV_PI/90, 80, 30, 10);
    Mat color_dst=src.clone();
    int cnt = 0;
    for (auto & l : lines){
        if(norm(Point(l[0], l[1]) - Point(l[2], l[3]))>1000){
            //line(color_dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 8);
            cnt ++;
        }
    }
//    std::cout <<cnt;
//    double reduction = 3.8;
//    Size reduite(color_dst.cols/reduction, color_dst.rows/reduction);
//    Mat reducted = Mat(reduite,CV_8UC3);
//    resize(color_dst,reducted,reduite);
//    imshow("lines",reducted);
    return cnt > 5;
}