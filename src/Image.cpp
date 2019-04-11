//
// Created by Stefania Cerboni on 2019-04-11.
//

#include <iostream>
#include "Image.h"
void Image::Load(String path) {
    try {
        Mat temp = imread(path, IMREAD_COLOR);

        if (temp.empty())                      // Check for invalid input
        {
            throw invalid_argument("Wrong Path!");
        }
        pixels = imread( path, IMREAD_COLOR );
        channels = pixels.channels();
        width = pixels.cols;
        height = pixels.rows;
    }
    catch(invalid_argument const &ex) {
        cerr << ex.what() << endl;
    }
}
void Image::Save(String name) {
    imwrite(name, this->pixels);
}
uchar Image::getPixel(int i, int j){
    return pixels.at<uchar>(i,j);
}


array<Mat,3> Image::getBGRChannels() {
    array<Mat,3> bgr;
    split(pixels, bgr);
    return bgr;
}
void Image::Show(String imName){
    imshow(imName, pixels);
}
Image* Image::ConvertRGB2BW(Image *src){
    Mat src_gray;
    cvtColor(src->pixels, src_gray, COLOR_BGR2GRAY );
    return new Image(src_gray);
}
void Image::setPixel(int i, int j, int value){
    this->pixels.at<uchar>(i,j) = value;
}
Mat Image::getPixels() {
    return this->pixels;
}