//
// Created by xizheng on 11/27/19.
//

#include <opencv2/highgui.hpp>
#include "thresholding.h"
#define IMAGE_HEIGHT
#define IMAGE WIDTH


void calc_threshold(const string& histTitle,const Mat& img) {
    // INIT

    int threshold_value = 200;
    /* Threshold type
     * 0: Binary
   1: Binary Inverted
   2: Threshold Truncated
   3: Threshold to Zero
   4: Threshold to Zero Inverted
 */
    int threshold_type = 0;
    int const max_value = 255;
    int const max_type = 4;
    int const max_BINARY_value = 255;

    Mat src = img;
    Mat src_gray, dst;
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    imshow("image gray", src_gray);

    threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
    imshow("binary image", dst);
}