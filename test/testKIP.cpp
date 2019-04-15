//
// Created by Giulio Gambassi on 2019-04-15.
//
#include <gtest/gtest.h>
#include "../src/Image.h"
#include "../src/kip.h"

using testing::Eq;

class testKIP : public testing::Test{
public:
    Image *src;
    int dim = 5; // r=c=dim=5
    testKIP(){
        vector< uchar> Vf{206,205,247,245,244,
                          244,161,137,244,254,
                          192,154, 75, 200, 249,
                          90, 109, 96, 143, 223,
                          67, 69, 107, 196, 236};
        Mat M = Mat(dim,dim, CV_32FC1);
        for (int k = 0; k < dim; k++) {
            for (int i = 0; i < dim; i++) {
                M.at<uchar>(k,i)= Vf[(dim*k)+i];
            }
        }
        src = new Image(M);
    }
    virtual ~testKIP(){
    };

};
TEST_F(testKIP, ControllaSharpen){
    Sharpen s;
    Image dst = s.process(*src);
    vector<uchar> calc{0,0,0,0,0,
                       0,65,0,255,0,
                       0,233, 0, 255, 0,
                       0, 136, 46, 0, 0,
                       0, 0, 0, 0, 0};
    bool noteq = false;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if( dst.getPixel(i,j)!=calc[(dim*i)+j])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
}
TEST_F(testKIP, ControllaGaussianBlur){
    Gaussian_Blur gb;
    Image dst = gb.process(*src);
    vector<uchar> calc{0,0,0,0,0,
                       0,177,175,216,0,
                       0,141, 133, 183, 0,
                       0, 105, 116, 166, 0,
                       0, 0, 0, 0, 0};
    bool noteq = false;
    int val, a;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            val = dst.getPixel(i,j);
            a = calc[(dim*i)+j];
            if( dst.getPixel(i,j)!=calc[(dim*i)+j])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
}
TEST_F(testKIP, ControllaEmboss){
    Emboss ess;
    Image dst = ess.process(*src);
    vector<uchar> calc{206,205,247,245,244,
                       244,0,38,255,254,
                       192,0, 44, 255, 249,
                       90, 0, 246, 255, 223,
                       67, 69, 107, 196, 236};
    bool noteq = false;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if( dst.getPixel(i,j)!=calc[(dim*i)+j])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
}
TEST_F(testKIP, ControllaEdgeDetection){
    EdgeDetection ed;
    Image dst = ed.process(*src);
    vector<uchar> calc{206,205,247,245,244,
                       244,0,0,255,254,
                       192,128, 0, 179, 249,
                       90, 22, 0, 0, 223,
                       67, 69, 107, 196, 236};
    bool noteq = false;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if( dst.getPixel(i,j)!=calc[(dim*i)+j])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
}
TEST_F(testKIP, ControllaSobel){
    SobelEdge se;
    Image dst = se.process(*src);
    vector<uchar> calc{206,205,247,245,244,
                       244,152,251,244,254,
                       192,193, 58, 200, 249,
                       90, 109, 96, 143, 223,
                       67, 69, 107, 196, 236};
    bool noteq = false;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if( dst.getPixel(i,j)!=calc[(dim*i)+j])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
}
TEST_F(testKIP, ControllaBoxBlur){
    BoxBlur bb;
    Image dst = bb.process(*src);
    vector<uchar> calc{0,0,0,0,0,
                       0,180,185,210,0,
                       0,139, 146, 180, 0,
                       0, 106, 127, 169, 0,
                       0, 0, 0, 0, 0};
    bool noteq = false;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if( dst.getPixel(i,j)!=calc[(dim*i)+j])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
}