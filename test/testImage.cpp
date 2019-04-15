//
// Created by Giulio Gambassi on 2019-04-11.
//

#include <gtest/gtest.h>
#include "../src/Image.h"
#include "../src/kip.h"

using testing::Eq;

class testImage : public testing::Test{
public:

    Image * img;

        testImage(){
            img = new Image();
        }
        virtual ~testImage() {
            delete img;
        }
};

TEST_F(testImage, TestCostruttoreBase){
    ASSERT_EQ(img->getWidth(), 0);
}

TEST_F(testImage, ControllaLetturaExc){
    try{
        img->Load("NotValidPath.pbm");
    }
    catch(invalid_argument const &ex){
        cerr<<ex.what()<<endl;
        EXPECT_EQ(ex.what(),std::string("Couldn't find any image, please check the path"));
    }

}
TEST_F(testImage, ControllaGetPixel){
    try{
        img->getPixel(-2,-2);
    }
    catch(out_of_range const &ex){
        EXPECT_EQ(ex.what(),std::string("Index i=-2, j=-2 out of bound"));
    }
}