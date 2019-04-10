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
#include "Image.h"
using namespace cv;
using namespace std;

class kip {
public:
    static void noBorderProcessing(Mat src, Mat dst, float Kernel[][3]);

    //Kernel image processing:
    virtual void process(Mat src) = 0;
    static void getChannelImage(Mat src, int channel);
};

class Gaussian_Blur : public kip{
public:
    void process(Image src);
    void process(Mat src) override{}
private:
    float Kernel[3][3] = {
            {1/16.0, 2/16.0, 1/16.0},
            {2/16.0, 4/16.0, 2/16.0},
            {1/16.0, 2/16.0, 1/16.0}
    };
};

class BoxBlur : public kip{
public:
    void process(Mat src) override;
private:
    float Kernel[3][3] = {
            {1/9.0, 1/9.0, 1/9.0},
            {1/9.0, 1/9.0, 1/9.0},
            {1/9.0, 1/9.0, 1/9.0}
    };
};

class Sharpen : public kip{
public:
    void process(Mat src) override;
private:
    float Kernel[3][3] = {
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
    };
};

class SobelEdge : public kip{
public:
    void process(Mat src) override;
private:
    float Gx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };
    float Gy[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
    };
};

class EdgeDetection : public kip{
public:
    void process(Mat src) override;
private:
    float Kernel[3][3] = {
            {1, 0, -1},
            {0, 0, 0},
            {-1, 0, 1}
    };
};
#endif //PBM_KIP_H
