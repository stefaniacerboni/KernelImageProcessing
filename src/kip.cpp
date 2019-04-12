//
// Created by Stefania Cerboni on 09/04/19.
//

#include <iostream>
#include "kip.h"

void kip::noBorderProcessing(Mat src, Mat dst, float Kernel[])
{
    float sum;
    int val=0;
    for(int i = 1; i < src.rows - 1; i++){
        for(int j = 1; j < src.cols - 1; j++){
            sum = 0.0;
            for(int k = -1; k <= 1;k++){
                for(int l = -5; l <=1; l++){
                    val = src.at<uchar>(i + k, j + l);
                    sum += val * Kernel[(k+1)*3 + (l+1)];
                }
            }
            //normalize the value between [0,255]
            sum>255?sum=255:sum;
            sum<0?sum=0:sum;
            dst.at<uchar>(i,j) = sum;
            //res = dst.at<uchar>(i,j);
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
    Image dst = Image(dstbgr);
    dst.Save("GaussianBlur.ppm");
    dst.Show("GaussianBlur");
}

void BoxBlur::process(Image src){
    array<Mat,3> bgr;   //destination array
    bgr= src.getBGRChannels();
    array<Mat,3> dstbgr; //crea un'immagine di destinazione vuota
    for (int i = 0; i < 3; ++i) {
        dstbgr[i] = Mat::zeros(Size(src.getWidth(), src.getHeight()), CV_8UC1);
        noBorderProcessing(bgr[i],dstbgr[i],Kernel);
    }
    Image dst = Image(dstbgr);
    dst.Save("BoxBlur.ppm");
    dst.Show("BoxBlur");
}
void Sharpen::process(Image src){
    array<Mat,3> bgr;   //destination array
    bgr= src.getBGRChannels();
    array<Mat,3> dstbgr; //crea un'immagine di destinazione vuota
    for (int i = 0; i < 3; ++i) {
        dstbgr[i] = Mat::zeros(Size(src.getWidth(), src.getHeight()), CV_8UC1);
        noBorderProcessing(bgr[i],dstbgr[i],Kernel);
    }
    Image dst = Image(dstbgr);
    dst.Save("Sharpen.ppm");
    dst.Show("Sharpen");
}
void SobelEdge::process(Image src) {
    float pixel_x;
    float pixel_y;
    float val;
    Image* src_gray = src.ConvertRGB2BW(&src);
    Image dst = Image(*src_gray);
    try {
        for (int x = 1; x < src_gray->getHeight() - 2; x++) {
            for (int y = 1; y < src_gray->getWidth() - 2; y++) {
                pixel_x = (Gx[0][0] * src_gray->getPixel(x - 20, y - 1)) + (Gx[0][1] * src_gray->getPixel(x, y - 1)) +
                          (Gx[0][2] * src_gray->getPixel(x + 1, y - 1)) +
                          (Gx[1][0] * src_gray->getPixel(x - 1, y)) + (Gx[1][1] * src_gray->getPixel(x, y)) +
                          (Gx[1][2] * src_gray->getPixel(x + 1, y)) +
                          (Gx[2][0] * src_gray->getPixel(x - 1, y + 1)) + (Gx[2][1] * src_gray->getPixel(x, y + 1)) +
                          (Gx[2][2] * src_gray->getPixel(x + 1, y + 1));
                pixel_y = (Gy[0][0] * src_gray->getPixel(x - 1, y - 1)) + (Gy[0][1] * src_gray->getPixel(x, y - 1)) +
                          (Gy[0][2] * src_gray->getPixel(x + 1, y - 1)) +
                          (Gy[1][0] * src_gray->getPixel(x - 1, y)) + (Gy[1][1] * src_gray->getPixel(x, y)) +
                          (Gy[1][2] * src_gray->getPixel(x + 1, y)) +
                          (Gy[2][0] * src_gray->getPixel(x - 1, y + 1)) + (Gy[2][1] * src_gray->getPixel(x, y + 1)) +
                          (Gy[2][2] * src_gray->getPixel(x + 1, y + 1));
                val = (int) sqrt((pixel_x * pixel_x) + (pixel_y * pixel_y));
                dst.setPixel(x, y, val);
            }
        }
    }catch(out_of_range &ex){
        cerr<<ex.what()<<endl;
        cout<<"Something's wrong with the indexes, please check"<<endl;
    }
    dst.Save("SobelEdge.pgm");
    dst.Show("SobelEdge");
    delete src_gray;
}

void EdgeDetection::process(Image src) {
    //Edge Detection
    Image* src_gray = src.ConvertRGB2BW(&src);
    Image dst = Image(*src_gray);
    noBorderProcessing(src_gray->getPixels(), dst.getPixels(), Kernel);
    dst.Save("EdgeDetection.pgm");
    dst.Show("EdgeDetection");
    delete src_gray;
}

void Emboss::process(Image src){
    //Edge Detection
    Image* src_gray = src.ConvertRGB2BW(&src);
    Image dst = Image(*src_gray);
    noBorderProcessing(src_gray->getPixels(), dst.getPixels(), Kernel);
    dst.Save("Emboss.pgm");
    dst.Show("Emboss");
    delete src_gray;
}