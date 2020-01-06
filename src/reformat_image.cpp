//
// Created by brdaniel on 11/12/19.
//

#include "reformat_image.h"


/**
 * Rotate the source image using the getRotationMatrix2D and warpAffine from OpenCV
 * @param src source image matrix
 * @param dst destination image matrix
 * @param pt the point around which the image is going to rotate
 * @param angle the angle in degrees of rotation to apply
 */
void rotateImage(Mat src, Mat dst, Point pt, double angle){
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
}




/**
 * This function returns the rotation angle in degrees necessary to re-calibrate an image based on it's cross position
 * @param bottomCross
 * @param upperCross
 * @return
 */
double computeRotationAngle(Point bottomCross, Point upperCross){
    //Here are the reference image's (OOOOO.png) cross centers positions
    //upperCross(x,y)=(2145,545)
    //bottomcross(x,y)=(293,3161)
    double ref_angle = atan((2145.-293.)/(545.-3161.));
    return -(ref_angle-atan((double)(double)((double)upperCross.x-(double)bottomCross.x)/(double)((double)upperCross.y-(double)bottomCross.y)))*(180/CV_PI)/2.;
}
