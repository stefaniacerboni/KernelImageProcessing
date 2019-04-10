#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include "kip.h"
#include "Image.h"

using namespace std;
using namespace cv;
int main() {
    string imageName( "/Users/giuliogambassi/Downloads/KernelImageProcessing-master/marbles1.pbm" ); // by default
    Image img;
    img.Load(imageName);
    Gaussian_Blur gb;
    gb.process(img);
    /*SobelEdge se;
    se.process(img);
    Sharpen s;
    s.process(img);
    EdgeDetection ed;
    ed.process(img);
    BoxBlur bb;
    bb.process(img);
    for (int i = 0; i < image.channels(); ++i) {
        kip::getChannelImage(image,i);
    }
    Mat gray_image;
    gray_image = imread(imageName, IMREAD_GRAYSCALE);
    imwrite( "Gray_Image.pbm", gray_image );
    imshow( "Gray image", gray_image );// Create a window for display.
    imshow("Original image", image);*/
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}