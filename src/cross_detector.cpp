//
// Created by brdaniel on 11/12/19.
//

#include "cross_detector.h"

#include <iostream>
#include <thresholding.h>

using namespace std;

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

#define CROSS_SIZE 100
#define SIDE_LIMIT 50
#define STEP 100

//Do the average of the position of every coloured pixel around init after transforming it in a binary image with the threshold step
Point trimming(const Mat &src, Point init, bool cross = true, int step = STEP, int half_square_length = CROSS_SIZE) {

    //Convert the src to a binary image
    Mat gray, bw;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(~gray, bw, step, 255, 0);

    //Remove Noise
    Mat block = getStructuringElement(MORPH_RECT, Size(2, 2));
    erode(bw, bw, block);
    dilate(bw, bw, block);


    if (cross) {
        // Evaluate the cross position
        int count = 0;
        for (int x = init.x - 5; x < init.x + 5; x++)if (bw.at<bool>(init.y, x)) count++;
        for (int y = init.y - 5; y < init.y + 5; y++)if (bw.at<bool>(y, init.x)) count++;

        if (count > 16) {
            return init;
        }
    }

    //Store the sum of the position of all blanck pixel in buffer_x and buffer_y
    int limit_x = min(init.x + half_square_length, bw.cols - 1);
    int limit_y = min(init.y + half_square_length, bw.rows - 1);
    int buffer_x = 0; int buffer_y = 0;
    int count = 0;
    for (int x = max(init.x - CROSS_SIZE, 1); x <= limit_x && x > 0; x++) {
        for (int y = max(init.y - CROSS_SIZE, 1); y <= limit_y && y > 0; y++) {
            if (bw.at<bool>(y, x)) {
                buffer_x += x;
                buffer_y += y;
                count++;
            }
        }
    }

    if (cross && count < 10) {
        return init;
    }

    if (count == 0) return init;
    //Compute the average position of all the black pixel
    Point corrected = Point(buffer_x / count, buffer_y / count);
    ~bw;
    //Return the average position
    return corrected;
}


Point searchCrossCenter(const Mat &src, const bool top) {

    Mat crossMat, edgesImage, block;
    //Frame approximately localized on the cross position in the image
    int xWindow, yWindow;
    Rect Window;
    if (top) {
        xWindow = 2 * src.cols / 3;
        yWindow =  2 * src.rows / 7;
        Window = Rect(xWindow, SIDE_LIMIT, src.cols - (xWindow) - SIDE_LIMIT, (yWindow) - 2* SIDE_LIMIT);
    } else {
        xWindow = 1 * src.cols / 3;
        yWindow= 5 * src.rows /7;
        Window = Rect(SIDE_LIMIT, yWindow, xWindow - 2* SIDE_LIMIT, src.rows - yWindow - 2* SIDE_LIMIT);
    }
    crossMat = src(Window);
    //Applying Canny threshold
    Canny(crossMat, edgesImage, 250, 500);
    //Noise deletion
    block = getStructuringElement(MORPH_RECT, Size(4, 4));
    dilate(edgesImage, edgesImage, block);
    erode(edgesImage, edgesImage, block);
    //Edge detection
    vector<Vec4i> lines;
    HoughLinesP(edgesImage, lines, 1, CV_PI/90, 80, 30, 10);

    //Lines drawing used to tune
    /*Mat color_dst=crossMat.clone();
    for (auto & i : lines){
        line(color_dst, Point(i[0], i[1]), Point(i[2], i[3]), Scalar(0, 0, 255), 3, 8);
    }
    if(top) imshow("lines", color_dst);*/

    float crossY, crossX;
    if (top) {
        crossY = edgesImage.rows;
        crossX = edgesImage.cols;
    } else {
        crossY = SIDE_LIMIT;
        crossX = SIDE_LIMIT;
    }
    circle(crossMat,Point(crossX,crossY),2,Scalar(255,0,0),2);
    for (auto & line : lines) {
        //Centre de la ligne suivant y
        float ptx = (line[0] + line[2]) / 2.f;
        float pty = (line[1] + line[3]) / 2.f;
        if ((top && (pty < crossY && pty > 0)) || (!top && (pty>crossY))) {
            crossY = pty;
            crossX = ptx;
        }
    }

    if(top){
        crossX += xWindow;
    }else{
        crossY += yWindow;
    }

    return {(int)crossX, (int)crossY};
}

tuple<Point,Point> searchCross (const Mat& src) {
    Point bottomCross = trimming(src, searchCrossCenter(src, false));
    Point topCross = trimming(src, searchCrossCenter(src, true));

    return make_tuple(bottomCross,topCross);
}


