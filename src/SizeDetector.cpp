//
// Created by xizheng on 12/13/19.
//

#include <opencv2/imgcodecs.hpp>
#include <SquareExtractor.h>
#include <opencv2/highgui.hpp>
#include "SizeDetector.h"

Matcher* SizeDetector::MATCHER = new Matcher();

SizeDetector::SizeDetector() {
    smallImg = cv::imread("../Images/Sizes/small.png");
    mediumImg = cv::imread("../Images/Sizes/medium.png");
    largeImg = cv::imread("../Images/Sizes/large.png");
}

int SizeDetector::detectSize(const cv::Mat& i) {
    cv::Mat img = getSquare(i, 0, i.rows / 2, i.cols, i.rows / 2);
    imwrite("~/Desktop/Lowerhalf.png", img);
    int smallScore, mediumScore, largeScore;
    smallScore = MATCHER->surf(img, smallImg);
    mediumScore = MATCHER->surf(img, mediumImg);
    largeScore = MATCHER->surf(img, largeImg);
    if (smallScore < 5 && mediumScore < 5 && largeScore < 5) {
        return SizeDetector::NONE;
    } else if (smallScore > mediumScore && smallScore > largeScore) {
        return SizeDetector::SMALL;
    } else {
        return (mediumScore > largeScore) ? SizeDetector::MEDIUM : SizeDetector::LARGE;
    }
}

int SizeDetector::detectSize(const std::string &name) {
    cv::Mat img = cv::imread(name);
    return detectSize(img);
}

string SizeDetector::detectSizeStr(const cv::Mat& img) {
    int res = detectSize(img);
    if (res == SizeDetector::NONE)
        return "None";
    else if (res == SizeDetector::SMALL)
        return "Small";
    else if (res == SizeDetector::MEDIUM)
        return "Medium";
    else
        return "Large";
}
