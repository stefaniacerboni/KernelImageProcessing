//
// Created by Stefania Cerboni on 09/04/19.
//

#include <iostream>
#include "kip.h"

int kip::reflect(int M, int x)
{
    if(x < 0)
    {
        return -x - 1;
    }
    if(x >= M)
    {
        return 2*M - x - 1;
    }
    return x;
}

int kip::circular(int M, int x)
{
    if (x<0)
        return x+M;
    if(x >= M)
        return x-M;
    return x;
}


void kip::noBorderProcessing(Mat src, Mat dst, float Kernel[][3])
{

    float sum;
    for(int y = 1; y < src.rows - 1; y++){
        for(int x = 1; x < src.cols - 1; x++){
            sum = 0.0;
            for(int k = -1; k <= 1;k++){
                for(int j = -1; j <=1; j++){
                    sum = sum + Kernel[j+1][k+1]*src.at<uchar>(y - j, x - k);
                }
            }
            dst.at<uchar>(y,x) = sum;
        }
    }
}

void kip::refletedIndexing(Mat src, Mat dst, float Kernel[][3])
{
    float sum, x1, y1;
    for(int y = 0; y < src.rows; y++){
        for(int x = 0; x < src.cols; x++){
            sum = 0.0;
            for(int k = -1;k <= 1; k++){
                for(int j = -1;j <= 1; j++ ){
                    x1 = reflect(src.cols, x - j);
                    y1 = reflect(src.rows, y - k);
                    sum = sum + Kernel[j+1][k+1]*src.at<uchar>(y1,x1);
                }
            }
            dst.at<uchar>(y,x) = sum;
        }
    }
}

void kip::circularIndexing(Mat src, Mat dst, float Kernel[][3])
{
    float sum, x1, y1;
    for(int y = 0; y < src.rows; y++){
        for(int x = 0; x < src.cols; x++){
            sum = 0.0;
            for(int k = -1;k <= 1; k++){
                for(int j = -1;j <= 1; j++ ){
                    x1 = circular(src.cols, x - j);
                    y1 = circular(src.rows, y - k);
                    sum = sum + Kernel[j+1][k+1]*src.at<uchar>(y1,x1);
                }
            }
            dst.at<uchar>(y,x) = sum;
        }
    }
}

void kip::getChannelImage(Mat src, int channel) {
    Mat bgr[3];
    split(src, bgr);
    switch(channel){
        case 0:
            imwrite( "BlueChannel.pbm", bgr[0]);
            imshow("Blue Channel", bgr[0]);
            break;
        case 1:
            imwrite( "GreenChannel.pbm", bgr[1]);
            imshow("Green Channel", bgr[1]);
            break;
        case 2:
            imwrite( "RedChannel.pbm", bgr[2]);
            imshow("Red Channel", bgr[2]);
            break;
        default:
            cout << "That channel isn’t valid\n";
    }
}

void kip::gaussianBlur(Mat image) {
    Mat dst;
    Mat bgr[3];   //destination array
    split(image,bgr);//split source in three channels
    Mat dstbgr[3]; //crea un'immagine di destinazione vuota

    //Gaussian Blur
    float Kernel[3][3] = {
        {1/16.0, 2/16.0, 1/16.0},
        {2/16.0, 4/16.0, 2/16.0},
        {1/16.0, 2/16.0, 1/16.0}
    };
    for (int i = 0; i < 3; ++i) {
        dstbgr[i] = Mat::zeros(Size(image.cols, image.rows), CV_8UC1);
        noBorderProcessing(bgr[i],dstbgr[i],Kernel);
    }
    vector<Mat> channels;
    channels.push_back(dstbgr[0]);
    channels.push_back(dstbgr[1]);
    channels.push_back(dstbgr[2]);
    merge(channels, dst);
    imwrite( "GaussianBlur.pbm", dst);
    imshow("GaussianBlur", dst);
}

void kip::boxBlur(Mat image){
    //Box Blur
    float Kernel[3][3] = {
        {1/9.0, 1/9.0, 1/9.0},
        {1/9.0, 1/9.0, 1/9.0},
        {1/9.0, 1/9.0, 1/9.0}
    };
    Mat dst;
    Mat bgr[3];   //destination array
    split(image,bgr);//split source in three channels
    Mat dstbgr[3]; //crea un'immagine di destinazione vuota
    for (int i = 0; i < 3; ++i) {
        dstbgr[i] = Mat::zeros(Size(image.cols, image.rows), CV_8UC1);
        noBorderProcessing(bgr[i],dstbgr[i],Kernel);
    }
    vector<Mat> channels;
    channels.push_back(dstbgr[0]);
    channels.push_back(dstbgr[1]);
    channels.push_back(dstbgr[2]);
    merge(channels, dst);
    imwrite( "BoxBlur.pbm", dst);
    imshow("Box Blur", dst);
}
void kip::sharpen(Mat image){
    //Sharpen
    float Kernel[3][3] = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };
    Mat dst;
    Mat bgr[3];   //destination array
    split(image,bgr);//split source in three channels
    Mat dstbgr[3]; //crea un'immagine di destinazione vuota
    for (int i = 0; i < 3; ++i) {
        dstbgr[i] = Mat::zeros(Size(image.cols, image.rows), CV_8UC1);
        noBorderProcessing(bgr[i],dstbgr[i],Kernel);
    }
    vector<Mat> channels;
    channels.push_back(dstbgr[0]);
    channels.push_back(dstbgr[1]);
    channels.push_back(dstbgr[2]);
    merge(channels, dst);
    imwrite( "Sharpen.pbm", dst);
    imshow("Sharpen", dst);
}
void kip::sobelEdge(Mat src) {
    Mat src_gray;
    float pixel_x;
    float pixel_y;
    float val;
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
    cvtColor(src, src_gray, CV_BGR2GRAY );
    Mat dst = src_gray.clone();
    for (int x = 1; x < src_gray.rows -2; x++) {
        for (int y = 1; y < src_gray.cols -2; y++) {
            pixel_x = (Gx[0][0] * src_gray.at<uchar>(x-1,y-1)) + (Gx[0][1] * src_gray.at<uchar>(x,y-1)) + (Gx[0][2] * src_gray.at<uchar>(x+1,y-1))+
                    (Gx[1][0] * src_gray.at<uchar>(x-1,y)) + (Gx[1][1] * src_gray.at<uchar>(x,y)) + (Gx[1][2] * src_gray.at<uchar>(x+1,y))+
                    (Gx[2][0] * src_gray.at<uchar>(x-1,y+1)) + (Gx[2][1] * src_gray.at<uchar>(x,y+1)) + (Gx[2][2] * src_gray.at<uchar>(x+1,y+1));
            pixel_y = (Gy[0][0] * src_gray.at<uchar>(x-1,y-1)) + (Gy[0][1] * src_gray.at<uchar>(x,y-1)) + (Gy[0][2] * src_gray.at<uchar>(x+1,y-1))+
                      (Gy[1][0] * src_gray.at<uchar>(x-1,y)) + (Gy[1][1] * src_gray.at<uchar>(x,y)) + (Gy[1][2] * src_gray.at<uchar>(x+1,y))+
                      (Gy[2][0] * src_gray.at<uchar>(x-1,y+1)) + (Gy[2][1] * src_gray.at<uchar>(x,y+1)) + (Gy[2][2] * src_gray.at<uchar>(x+1,y+1));
            val = (int)sqrt((pixel_x * pixel_x) + (pixel_y * pixel_y));
            dst.at<uchar>(x,y) = val;
        }
    }
    imwrite( "SobelEdge.pbm", dst);
    imshow("SobelEdge", dst);
}
void kip::edgeDetection(Mat src) {
    //Edge Detection
    float Kernel[3][3] = {
            {1, 0, -1},
            {0, 0, 0},
            {-1, 0, 1}
    };
    Mat src_gray;
    cvtColor(src, src_gray, CV_BGR2GRAY );
    Mat dst = src_gray.clone();
    noBorderProcessing(src_gray, dst, Kernel);
    imwrite( "EdgeDetection.pbm", dst);
    imshow("Edge Detection", dst);

}