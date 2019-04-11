//
// Created by Stefania Cerboni on 2019-04-11.
//

#ifndef PBM_IMAGE_H
#define PBM_IMAGE_H
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <array>
using namespace cv;
using namespace std;

class Image {
public:
    void Load(String path);

    void Save(String name);

    void Show(String imName);

    Image * ConvertRGB2BW(Image * src);

    Image(const Image& src){
        this->pixels = src.pixels.clone();
        this->width = src.width;
        this->height = src.height;
        this->channels = src.channels;
    }
    uchar getPixel(int i, int j);
    void setPixel(int i, int j, int value);
    array<Mat,3> getBGRChannels();
    Mat getPixels();
    explicit Image(array<Mat,3> ch){
        Mat dst;
        merge(ch, dst);
        this->pixels = dst.clone();
        this->channels = pixels.channels();
        this->width = pixels.cols;
        this->height = pixels.rows;
    }
    explicit Image(Mat pix){
        this->pixels = pix.clone();
        this->channels = pixels.channels();
        this->width = pixels.cols;
        this->height = pixels.rows;
    }
    Image(){
        this->pixels= NULL;
    }
    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        Image::width = width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        Image::height = height;
    }

    int getChannels() const {
        return channels;
    }

    void setChannels(int ch) {
        Image::channels = ch;
    }
    ~Image(){
        pixels.release();
    }

private:
    int width=0;
    int height=0;
    Mat pixels;
    int channels=1;


};


#endif //PBM_IMAGE_H
