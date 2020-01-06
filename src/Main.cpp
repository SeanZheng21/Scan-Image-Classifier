//////////////////////////////////////////////////////////////////////////
// Option Images
// Projet, s�ance 1
// th�me : premier pas en OpenCV
// contenu : charge, affiche, r�duction, calcul et affichage d'histogramme
// version : 17.1128
//////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <thresholding.h>
#include <SquareExtractor.h>
#include <matcher.h>


using namespace std;

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include <iostream>
#include <fstream>
#include <cross_detector.h>
#include <sys/stat.h>
#include "histogram.hpp"
#include "reformat_image.h"
#include "SizeDetector.h"
#include "textscan.h"



void generateUnclassifiedIcons() {
    int count = 0;
    string basePath = "/home-info/commun/p/p12/5info/irfBD/NicIcon/";
    for (int k = 0; k < 3/*35*/; ++k) {
        /* i: number of page*/
        for (int i = 0; i < 23; ++i) {
            string imagePath = basePath + "w0" + (k < 10 ? "0" + to_string(k) : to_string(k)) + "-scans/";
            string imageName = "0" + (k < 10 ? "0" + to_string(k) : to_string(k)) +
                               (i < 10 ? "0" + to_string(i) : to_string(i));
            Mat src = imread(imagePath+imageName+".png");
            cout << "Parsing file: " << imagePath + imageName << endl;
            cout << "\t\t" << to_string(k * 22 + i) << "/" << to_string(35 * 22) <<
                 "files\t\t\t" <<  (k * 22 + i) * 100 / (35 * 22) << "% completed " << endl;
            std::vector<cv::Mat> extractedVec = extract(src, 2201, 468, 257, 3232);
            int _i = 0;
            for(int z = 0; z < 7; z++) {
                string p = "../ImageResult/UnclassifiedIcons/" + to_string(count++) + ".png";
                imwrite(p, extractedVec[z]);
            }
        }
    }
}

void classifyIcons( float f, int i) {
    Matcher matcher(f, i);
    std::ofstream out("../ImageResult/ClassifiedIcons/result.txt");
    for (int i = 0; i < 482/*5635*/; ++i) {
        cv::Mat img = imread("../ImageResult/UnclassifiedIcons/" + to_string(i) + ".png");
        string cls = matcher.classifyImage(img);
        string name = "../ImageResult/ClassifiedIcons/" + cls + "-" + to_string(i) + ".png";
        out << name << endl;
        cout << name << endl;
        imwrite(name, img);
    }
    out.close();
}

void testSizeDetector() {
    SizeDetector detector;
    cout << detector.detectSize("../ImageResult/ClassifiedIcons/accident-0.png") << endl;
    cout << detector.detectSize("../ImageResult/ClassifiedIcons/bomb-239.png") << endl;
    cout << detector.detectSize("../ImageResult/ClassifiedIcons/accident-85.png") << endl;
    cout << detector.detectSize("../ImageResult/ClassifiedIcons/accident-71.png") << endl;
}

void testClassifyIcon() {
    generateUnclassifiedIcons();
    classifyIcons(0.7f, 400);
}

void test() {
    String basePath="../Images/donnees/";
    Matcher matcher;
    SizeDetector detector;
    int k = 0;
    for (int i = 0;  i< 12; i++) {
        Mat src,dst;
        string imagePath = basePath;
        string imageName = "000" + (i < 10 ? "0" + to_string(i) : to_string(i));
        src = imread(imagePath+imageName+".png");
        dst = src.clone();
        tuple<Point,Point> crosses = searchCross(src);
        Point bottomCross = get<0>(crosses);
        Point topCross = get<1>(crosses);
        //Image rotation
        double rotationAngle = computeRotationAngle(bottomCross, topCross);
        Point rotationCenter = Point ((topCross.x-bottomCross.x)/2.,(bottomCross.y-topCross.y)/2.);
        rotateImage(src, dst, rotationCenter, rotationAngle);
        crosses = searchCross(dst);
        bottomCross = get<0>(crosses);
        topCross = get<1>(crosses);
        if (!textscan(dst)) {
            std::vector<cv::Mat> extractedVec = extract(dst, topCross.x, topCross.y,
                                                        bottomCross.x, bottomCross.y);

            // number of icon
            for (int j = 0; j < 7; ++j) {
                cv::Mat img = extractedVec[j];
                string maxCls = matcher.classifyImage(img);
                string sz = detector.detectSizeStr(img);

                // number of handwritten image
                for (int l = 7 + j * 5; l < 7 + (j + 1) * 5; l++) {
                    cv::Mat _img = extractedVec[l];
                    string name = maxCls + "_0" + (k < 10 ? "0" + to_string(k) : to_string(k)) + "_" +
                                  (i < 10 ? "0" + to_string(i) : to_string(i)) + "_" + to_string(j) +
                                  to_string((l - 7) % 5);
                    //                    cout << "Generate " << name << endl;
                    imwrite("../ImageResult/" + maxCls + "/" + name + ".png", _img);
                    // Write the txt file
                    std::ofstream out("../ImageResult/" + maxCls + "/" + name + ".txt");
                    out << "label " << maxCls << endl;
                    out << "form 0" << (k < 10 ? "0" + to_string(k) : to_string(k)) <<
                        (i < 10 ? "0" + to_string(i) : to_string(i)) << endl;
                    out << "scripter 0" << (k < 10 ? "0" + to_string(k) : to_string(k)) << endl;
                    out << "page " << (i < 10 ? "0" + to_string(i) : to_string(i)) << endl;
                    out << "row " << i << endl;
                    out << "column " << (l - 7) % 5 << endl;
                    out << "size " << sz << endl;
                    out.close();
                }
            }
        }
    }

}

int main () {

//    system("../src/clean.sh");


//    test();
//    return 0;

//    testClassifyIcon();
//    testSizeDetector();
    string basePath = "/home-info/commun/p/p12/5info/irfBD/NicIcon/";
    Matcher matcher;
    SizeDetector detector;

    // k: number of scriptor
    for (int k = 0; k < 35; ++k) {
        // i: number of page
        for (int i = 0; i < 23; ++i) {
            Mat src,dst;
            string imagePath = basePath + "w0" + (k < 10 ? "0" + to_string(k) : to_string(k)) + "-scans/";
            string imageName = "0" + (k < 10 ? "0" + to_string(k) : to_string(k)) +
                    (i < 10 ? "0" + to_string(i) : to_string(i));
            cout << "Parsing file: " << imagePath + imageName << endl;
            cout << "\t\t" << to_string(k * 22 + i) << "/" << to_string(35 * 22) <<
            "files\t\t\t" <<  (k * 22 + i) * 100 / (35 * 22) << "% completed " << endl;
            src = imread(imagePath+imageName+".png");
            dst = src.clone();
            tuple<Point,Point> crosses = searchCross(src);
            Point bottomCross = get<0>(crosses);
            Point topCross = get<1>(crosses);
            //Image rotation
            double rotationAngle = computeRotationAngle(bottomCross, topCross);
            Point rotationCenter = Point ((topCross.x-bottomCross.x)/2.,(bottomCross.y-topCross.y)/2.);
            rotateImage(src, dst, rotationCenter, rotationAngle);
            crosses = searchCross(dst);
            bottomCross = get<0>(crosses);
            topCross = get<1>(crosses);
            if (!textscan(dst)) {
                std::vector<cv::Mat> extractedVec = extract(dst, topCross.x, topCross.y,
                                                            bottomCross.x, bottomCross.y);
                //            int _i = 0;
                //            for(int z = 0; z < 7; z++) {
                //                string p = "../ImageResult/Unclassified/0" + (k < 10 ? "0" + to_string(k) : to_string(k))
                //                           + "/"+ to_string(i) + "-" +to_string(_i++) + ".png";
                //                imwrite(p, extractedVec[z]);
                //            }
                // number of icon
                for (int j = 0; j < 7; ++j) {
                    cv::Mat img = extractedVec[j];
                    string maxCls = matcher.classifyImage(img);
                    string sz = detector.detectSizeStr(img);
                    imwrite("../ImageResult/ClassifiedIcons/" + maxCls + "-" + to_string(k) + "-" + to_string(i) + "-" +
                            to_string(j) + "-" + sz + ".png", img);
                    // number of handwritten image
                    for (int l = 7 + j * 5; l < 7 + (j + 1) * 5; l++) {
                        cv::Mat _img = extractedVec[l];
                        string name = maxCls + "_0" + (k < 10 ? "0" + to_string(k) : to_string(k)) + "_" +
                                      (i < 10 ? "0" + to_string(i) : to_string(i)) + "_" + to_string(j) +
                                      to_string((l - 7) % 5);
                        //                    cout << "Generate " << name << endl;
                        imwrite("../ImageResult/" + maxCls + "/" + name + ".png", _img);
                        // Write the txt file
                        std::ofstream out("../ImageResult/" + maxCls + "/" + name + ".txt");
                        out << "label " << maxCls << endl;
                        out << "form 0" << (k < 10 ? "0" + to_string(k) : to_string(k)) <<
                            (i < 10 ? "0" + to_string(i) : to_string(i)) << endl;
                        out << "scripter 0" << (k < 10 ? "0" + to_string(k) : to_string(k)) << endl;
                        out << "page " << (i < 10 ? "0" + to_string(i) : to_string(i)) << endl;
                        out << "row " << i << endl;
                        out << "column " << (l - 7) % 5 << endl;
                        out << "size " << sz << endl;
                        out.close();
                    }
                }
            } // else unclassified ?
        }
    }
    /*
    Mat src,dst;
    src=imread("../Images/Rotation\ tests/");
     */
	return EXIT_SUCCESS;
}
