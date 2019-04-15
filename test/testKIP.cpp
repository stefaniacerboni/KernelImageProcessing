//
// Created by Giulio Gambassi on 2019-04-15.
//
#include <gtest/gtest.h>
#include "../src/Image.h"
#include "../src/kip.h"

using testing::Eq;

class testKIP : public testing::Test{
public:
    Mat src;
    int dim = 5; // r=c=dim=5
    testKIP(){
        vector< uchar> Vf{206,205,247,245,244,
                          244,161,137,244,254,
                          192,154, 75, 200, 249,
                          90, 109, 96, 143, 223,
                          67, 69, 107, 196, 236};
        src = Mat(dim,dim, CV_32FC1);
        for (int k = 0; k < dim; k++) {
            for (int i = 0; i < dim; i++) {
                src.at<uchar>(k,i)= Vf[(dim*k)+i];
            }
        }
    }
    virtual ~testKIP(){
        src.release();
    };

};
TEST_F(testKIP, ControllaSharpen){
    //print Mat
    float Kernel[9] = {
            0, -1, 0,
            -1, 5, -1,
            0, -1, 0
    };
    Mat dst = src.clone();
    vector<uchar> calc{206,205,247,245,244,
                       244,65,0,255,254,
                       192,233, 0, 255, 249,
                       90, 136, 46, 0, 223,
                       67, 69, 107, 196, 236};
    bool noteq = false;
    kip::noBorderProcessing(src,dst,Kernel);
    for (int j = 0; j < dim; ++j) {
        for (int i = 0; i < dim; ++i) {
            if(dst.at<uchar>(j,i)!=calc[(dim*j)+i])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
    dst.release();
}
TEST_F(testKIP, ControllaGaussianBlur){
    float Kernel[9] = {
            1/16.0, 2/16.0, 1/16.0,
            2/16.0, 4/16.0, 2/16.0,
            1/16.0, 2/16.0, 1/16.0
    };
    Mat dst = src.clone();
    vector<uchar> calc{206,205,247,245,244,
                       244,177,175,216,254,
                       192,141, 133, 183, 249,
                       90, 105, 116, 166, 223,
                       67, 69, 107, 196, 236};
    bool noteq = false;
    kip::noBorderProcessing(src,dst,Kernel);
    int val, a;
    for (int j = 0; j < dim; ++j) {
        for (int i = 0; i < dim; ++i) {
            val = dst.at<uchar>(j,i);
            a = calc[(dim*j)+i];
            if(dst.at<uchar>(j,i)!=calc[(dim*j)+i])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
    dst.release();
}
TEST_F(testKIP, ControllaBoxBlur){
    float Kernel[9] = {
            1/16.0, 2/16.0, 1/16.0,
            2/16.0, 4/16.0, 2/16.0,
            1/16.0, 2/16.0, 1/16.0
    };
    Mat dst = src.clone();
    vector<uchar> calc{206,205,247,245,244,
                       244,177,175,216,254,
                       192,141, 133, 183, 249,
                       90, 105, 116, 166, 223,
                       67, 69, 107, 196, 236};
    bool noteq = false;
    kip::noBorderProcessing(src,dst,Kernel);
    for (int j = 0; j < dim; ++j) {
        for (int i = 0; i < dim; ++i) {
            if(dst.at<uchar>(j,i)!=calc[(dim*j)+i])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
    dst.release();
}
TEST_F(testKIP, ControllaEmboss){
    float Kernel[9] = {
            -2, -1, 0,
            -1, 1, 1,
            0, 1, 2
    };
    Mat dst = src.clone();
    vector<uchar> calc{206,205,247,245,244,
                       244,0,38,255,254,
                       192,0, 44, 255, 249,
                       90, 0, 246, 255, 223,
                       67, 69, 107, 196, 236};
    bool noteq = false;
    kip::noBorderProcessing(src,dst,Kernel);
    for (int j = 0; j < dim; ++j) {
        for (int i = 0; i < dim; ++i) {
            if(dst.at<uchar>(j,i)!=calc[(dim*j)+i])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
    dst.release();
}
TEST_F(testKIP, ControllaEdgeDetection){
    float Kernel[9] = {
            -1, -1, -1,
            -1, 8, -1,
            -1, -1, -1
    };
    Mat dst = src.clone();
    vector<uchar> calc{206,205,247,245,244,
                       244,0,0,255,254,
                       192,128, 0, 179, 249,
                       90, 22, 0, 0, 223,
                       67, 69, 107, 196, 236};
    bool noteq = false;
    kip::noBorderProcessing(src,dst,Kernel);
    int val, a;
    for (int j = 0; j < dim; ++j) {
        for (int i = 0; i < dim; ++i) {
            val = dst.at<uchar>(j,i);
            a = calc[(dim*j)+i];
            if(dst.at<uchar>(j,i)!=calc[(dim*j)+i])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
    dst.release();
}