//
// Created by Giulio Gambassi on 2019-04-11.
//

#include <gtest/gtest.h>
#include "../src/Image.h"

using testing::Eq;

class testImage : public testing::Test{
    public:
        testImage(){
        }
        ~testImage() {
        }
};

TEST_F(testImage, name1){
    Image a;
    ASSERT_EQ(a.getWidth(), 0);
}

TEST_F(testImage, name2){
    ASSERT_EQ("","");
}
int prova(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}