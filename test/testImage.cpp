//
// Created by Giulio Gambassi on 2019-04-11.
//

#include <gtest/gtest.h>
#include "../src/Image.h"
#include "../src/kip.h"

using testing::Eq;

class testImage : public testing::Test{
public:

    Image a;

        testImage(){
            a;
        }
        ~testImage() {
        }
};

TEST(testImage, TestCostruttoreBase){
    Image a;
    ASSERT_EQ(a.getWidth(), 0);
}

TEST(testImage, ControllaValiditàConvoluzione){
    int r=3;
    int c=4;
    vector< uchar> Vf{197,15,32,208,173,72,191,243,200,79,103,222};

    //insert value
    //create Mat
    Mat M=Mat(r,c,CV_32FC1);
    //copy vector to mat
    for (int k = 0; k < r; k++) {
        for (int i = 0; i < c; i++) {
            M.at<uchar>(k,i)= Vf[(c*k)+i];
        }
    }
    //print Mat
    float Kernel[9] = {
            0, -1, 0,
            -1, 5, -1,
            0, -1, 0
    };
    int val;
    Mat dst = M.clone();
    vector<uchar> calc{197,15,32,208,173,0,255,243,200,79,103,222};
    bool noteq = false;
    kip::noBorderProcessing(M, dst, Kernel);
    for (int j = 0; j < r; ++j) {
        for (int i = 0; i < c; ++i) {
            val = dst.at<uchar>(j,i);
            if(dst.at<uchar>(j,i)!=calc[(c*j)+i])
                noteq=true;
        }
    }
    ASSERT_EQ(noteq,false);
    M.release();
    dst.release();
}
TEST(testImage, ControllaLetturaExc){
    Image img;
    try{
        img.Load("NotValidPath.pbm");
    }
    catch(invalid_argument const &ex){
        EXPECT_EQ(ex.what(),std::string("Wrong Path!"));
    }
}
int prova(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}