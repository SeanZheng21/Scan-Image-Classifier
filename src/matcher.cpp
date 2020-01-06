//
// Created by xizheng on 11/28/19.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "matcher.h"
#include <vector>
#include <map>
#include <iterator>
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

float Matcher::DEFAULT_RATIO = 0.7f;
int Matcher::DEFAULT_HESS = 400;


int Matcher::surf(const cv::Mat& mat, const cv::Mat& img2) {
//    Mat img1 = imread(ref + ".png", 0);    // Load as gray scale
    const Mat& img1 = mat;
//    Mat img2= imread(qry, 0);    // Load as gray scale

    int minHessian = hess;
    Ptr<SURF> detector = SURF::create( minHessian );
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    detector->detectAndCompute( img1, noArray(), keypoints1, descriptors1 );
    detector->detectAndCompute( img2, noArray(), keypoints2, descriptors2 );

    //-- Step 2: Matching descriptor vectors with a FLANN based matcher
    // Since SURF is a floating-point descriptor NORM_L2 is used
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<DMatch> > knn_matches;
    matcher->knnMatch( descriptors1, descriptors2, knn_matches, 2 );

    //-- Filter matches using the Lowe's ratio surfTest
    const float thresh = this->ratio_thresh;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++) {
        if (knn_matches[i][0].distance < thresh * knn_matches[i][1].distance)
            good_matches.push_back(knn_matches[i][0]);
    }

    //-- Draw matches
//    Mat img_matches;
//    drawMatches( img1, keypoints1, img2, keypoints2, good_matches, img_matches, Scalar::all(-1),
//                 Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    //-- Show detected matches
//    imshow("Good Matches", img_matches );

    return good_matches.size();
}

string Matcher::classifyImage(const cv::Mat& img) {
    string classNames[] = {"accident", "bomb", "car", "casualty", "electricity", "fire", "firebrigade", "flood", "gas",
                           "injury", "paramedics", "police",
                           "person", "roadblock"};

    map<string, int> matches;
    for (int i = 0; i < 14; ++i) {
        int _matches = surf(img, "../Images/Icons/"+ classNames[i] +".png");
        matches.insert(pair<string, int>(classNames[i], _matches));
    }
//    cout << "Classification result of " << path << ": " << endl;
    map<string, int>::iterator itr;
    int maxMatch = 0;
    string maxCls;
    for(itr = matches.begin(); itr != matches.end(); ++itr) {
//        cout << '\t' << itr->first << "\t---\t" << itr->second << " matches" << endl;
        if (maxMatch <= itr->second) {
            maxCls = itr->first;
            maxMatch = itr->second;
        }
    }
//    cout << "Best match: " << maxMatch << " " << maxCls << " matches" << endl;
//    cv::Mat _img = cv::imread(path);
//    imwrite("../ImageResult/" + maxCls + "/" + path.substr(14, path.size()), _img);
    return maxCls;
}

int Matcher::surf(const cv::Mat &mat, const std::string &qry) {
    const cv::Mat img = cv::imread(qry, 0);
    return surf(mat, img);
}


void performSift() {

//    Mat queryImg = imread("../Images/query.png", 0);    // Load as gray scale
//    Mat trainImg = imread("../Images/train.png", 0);    // Load as gray scale
    Mat queryImg = imread("../Images/a.jpeg", 0);    // Load as gray scale
    Mat trainImg = imread("../Images/a.jpeg", 0);    // Load as gray scale

    imshow("query image", queryImg);
    imshow("train gray", trainImg);

    // Detect keypoints in both images.
//    xfeatures2d::SiftFeatureDetector detector;
//    vector<KeyPoint> queryKeypoints, trainKeypoints;
//    detector.detect(queryImg, queryKeypoints);
//    detector.detect(trainImg, trainKeypoints);

    Ptr<cv::xfeatures2d::SIFT> detector = SiftFeatureDetector::create();
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(trainImg, keypoints);
    cout << "Found " << keypoints.size() << " keypoints" << endl;



    // Print how many keypoints were found in each image.
//    printf("Found %d and %d keypoints.\n", queryKeypoints.size(), trainKeypoints.size());




}