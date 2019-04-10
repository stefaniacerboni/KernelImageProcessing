#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include "kip.h"

using namespace std;
using namespace cv;
int main() {
    string imageName( "/Users/stefaniacerboni/CLionProjects/PBM/marbles1.pbm" ); // by default
    Mat image;
    image = imread( imageName, IMREAD_COLOR );

    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    kip::gaussianBlur(image);
    kip::boxBlur(image);
    kip::sharpen(image);
    kip::sobelEdge(image);
    kip::edgeDetection(image);
    for (int i = 0; i < image.channels(); ++i) {
        kip::getChannelImage(image,i);
    }
    Mat gray_image;
    gray_image = imread(imageName, IMREAD_GRAYSCALE);
    imwrite( "Gray_Image.pbm", gray_image );
    imshow( "Gray image", gray_image );// Create a window for display.
    imshow("Original image", image);
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}