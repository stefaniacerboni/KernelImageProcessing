//
// Created by Stefania Cerboni on 2019-04-11.
//

#include <iostream>
#include "Image.h"
void Image::Load(String path) {
    Mat temp = imread(path, IMREAD_COLOR );

    if( temp.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
    }
    pixels = imread( path, IMREAD_COLOR );
    channels = pixels.channels();
    width = pixels.cols;
    height = pixels.rows;
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
void Image::Show(){
    imshow("GaussianBlur", pixels);
}