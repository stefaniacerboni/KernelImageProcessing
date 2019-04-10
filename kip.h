//
// Created by Stefania Cerboni on 09/04/19.
//

#ifndef PBM_KIP_H
#define PBM_KIP_H
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;

class kip {
public:
    static int reflect(int M, int x);
    static int circular(int M, int x);
    static void noBorderProcessing(Mat src, Mat dst, float Kernel[][3]);
    static void refletedIndexing(Mat src, Mat dst, float Kernel[][3]);
    static void circularIndexing(Mat src, Mat dst, float Kernel[][3]);

    //Kernel image processing:

    static void edgeDetection(Mat src, Mat dst, float Kernel[][3]);
    static void gaussianBlur(Mat src);
    static void boxBlur(Mat src);
    static void sharpen(Mat src);
    static void getChannelImage(Mat src, int channel);
    static void sobelEdge(Mat src);
    static void edgeDetection(Mat src);
};


#endif //PBM_KIP_H
