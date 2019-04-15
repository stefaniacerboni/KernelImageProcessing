//
// Created by Stefania Cerboni on 2019-04-11.
//

#include <iostream>
#include "Image.h"
void Image::Load(const String &path) {
    Mat temp = imread(path, IMREAD_COLOR);
    if (temp.empty())                      // Check for invalid input
    {
        throw invalid_argument("Couldn't find any image, please check the path");
    }
    pixels = imread( path, IMREAD_COLOR );
    channels = pixels.channels();
    width = pixels.cols;
    height = pixels.rows;
}
void Image::Save(const String &name) {
    imwrite(name, this->pixels);
}
uchar Image::getPixel(int i, int j){
    if(i<0||i>height||j<0||j>width)
        throw out_of_range("Index i="+to_string(i)+", j="+to_string(j)+" out of bound");
    else
        return pixels.at<uchar>(i,j);
}
array<Mat,3> Image::getBGRChannels() {
    array<Mat,3> bgr;
    split(pixels, bgr);
    return bgr;
}
void Image::Show(const String &imName){
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