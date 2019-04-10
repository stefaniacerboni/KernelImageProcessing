//
// Created by Stefania Cerboni on 09/04/19.
//

#include <iostream>
#include "kip.h"

kip::noBorderProcessing(Mat src, Mat dst, float Kernel[][3])
{

float sum;
for(int i = 1; i < src.rows - 1; i++){
for(int j = 1; j < src.cols - 1; j++){
sum = 0.0;
for(int k = -1; k <= 1;k++){
for(int l = -1; l <=1; l++){
sum = sum + src.at<uchar>(i + k, j + l) * Kernel[k+1][l+1];
}
}
dst.at<uchar>(i,j) = sum;
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

void Gaussian_Blur::process(Image src) {
    array<Mat,3> bgr;   //destination array
    bgr= src.getBGRChannels();
    array<Mat,3> dstbgr; //crea un'immagine di destinazione vuota

    for (int i = 0; i < 3; ++i) {
        dstbgr[i] = Mat::zeros(Size(src.getWidth(), src.getHeight()), CV_8UC1);
        noBorderProcessing(bgr[i],dstbgr[i],Kernel);
    }
    Image* dst = new Image(dstbgr);
    dst->Save("GaussianBlur.ppm");
    dst->Show();
}

void BoxBlur::process(Mat image){
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
    imwrite( "BoxBlur.ppm", dst);
    imshow("Box Blur", dst);
}
void Sharpen::process(Mat image){
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
    imwrite( "Sharpen.ppm", dst);
    imshow("Sharpen", dst);
}
void SobelEdge::process(Mat src) {
    Mat src_gray;
    float pixel_x;
    float pixel_y;
    float val;
    cvtColor(src, src_gray, COLOR_BGR2GRAY );
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
void EdgeDetection::process(Mat src) {
    //Edge Detection
    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY );
    Mat dst = src_gray.clone();
    noBorderProcessing(src_gray, dst, Kernel);
    imwrite( "EdgeDetection.pbm", dst);
    imshow("Edge Detection", dst);

}