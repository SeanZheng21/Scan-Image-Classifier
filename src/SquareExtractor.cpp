//
// Created by xizheng on 12/4/19.
//

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "SquareExtractor.h"
using namespace cv;

std::vector<cv::Mat> extract(Mat input, int ur_X, int ur_Y, int ll_X, int ll_Y) {
    //std::string path = basePath + name + ".png";
    //                reference: 2145, 548, 294, 3162
    const int SIZE_X = 2480;     // Same size for all images
    const int SIZE_Y = 3508;

    int spanX = ur_X - ll_X;
    int spanY = ll_Y - ur_Y;
    double scaleX = (spanX + 0.0) / 1851;
    double scaleY = (spanY + 0.0) / 2614;

    const int WINDOW_X = 230.0 * scaleX;
    const int WINDOW_Y = 230.0 * scaleY;
    
    int icon_offset = 0 - 35;
    int xOffsets[5] = {330, 666, 988, 1320, 1660};
    int yOffsets[7] = {228, 554, 883, 1220, 1544, 1875, 2205};

    //cv::Mat input = cv::imread(path);
//    cv::Mat croppedImage = getSquare(input, ll_X , ur_Y, (ur_X - ll_X) * scaleX, (ll_Y - ur_Y) * scaleY);

    //        cv::imshow("input", input);
//            cv::imshow("croped", croppedImage);
    std::vector<cv::Mat> resVec;
    std::vector<cv::Mat> iconVec;
    // Generate vector of handwritten images
    for (int j = 0; j < 7; ++j) {
        for (int i = 0; i < 5; ++i) {
            int squareX = ll_X + 7.0 + (xOffsets[i]) * scaleX;
            int squareY = ur_Y + 10.0 + (yOffsets[j]) * scaleY;
            cv::Mat firstSquare = getSquare(input,
                                        squareX,
                                        squareY,
                                        WINDOW_X,
                                        WINDOW_Y - 20);
        //            cv::imshow("Square" + std::to_string(i)+", " + std::to_string(j)+" : ", firstSquare);
//        imwrite("../ImageResult/Square " + std::to_string(i)+" " + std::to_string(j)+" - "+
//        std::to_string(squareX)+"-"+std::to_string(squareY)+"-"+std::to_string(int(WINDOW_X))+"-"+std::to_string(int(WINDOW_Y))+".png ", firstSquare);
        resVec.push_back(firstSquare);
        }
    }

    // Generate vector of icon images
    for (int j = 0; j < 7; ++j) {
        int squareX = ll_X + (icon_offset) * scaleX;
        int squareY = ur_Y + (yOffsets[j]) * scaleY;
        cv::Mat firstSquare = getSquare(input,
                                        squareX,
                                        squareY,
                                        WINDOW_X,
                                        WINDOW_Y + 100);
        //            cv::imshow("Square" + std::to_string(i)+", " + std::to_string(j)+" : ", firstSquare);
//        imwrite("../ImageResult/Square " + std::to_string(i)+" " + std::to_string(j)+" - "+
//        std::to_string(squareX)+"-"+std::to_string(squareY)+"-"+std::to_string(int(WINDOW_X))+"-"+std::to_string(int(WINDOW_Y))+".png ", firstSquare);
        iconVec.push_back(firstSquare);
    }


//    // Produce extracted handwritten images
//    for (int k = 0; k < resVec.size(); ++k) {
//        cv::Mat _img = resVec[k];
//        std::string pathToWrite = "../ImageResult/Unclassified/" + name.substr(0, 3) + "/Square" + std::to_string(k) + ".png";
//        imwrite(pathToWrite, _img);
//    }
//
//    // Produce detected icons
//    for (int k = 0; k < iconVec.size(); ++k) {
//        cv::Mat _img = iconVec[k];
//        imwrite("../ImageResult/Unclassified/" + name.substr(0, 3) + "/Icon" + std::to_string(k) + ".png", _img);
//    }

    iconVec.insert(std::end(iconVec), std::begin(resVec), std::end(resVec));
    return iconVec;
}

cv::Mat getSquare(cv::Mat src, int x, int y, int disX, int disY) {
    cv::Rect myROI(x, y, disX, disY);
    cv::Mat croppedImage = src(myROI);
    return croppedImage;
}
