
#include <iostream>
#include <fstream>
#include "src/kip.h"
#include "src/Image.h"


using namespace std;
using namespace cv;
int main() {
    string imageName( "/Users/giuliogambassi/Downloads/KernelImageProcessing-master/building.pgm" ); // by default
    Image img;
    img.Load(imageName);
    Gaussian_Blur gb;
    gb.process(img);
    SobelEdge se;
    se.process(img);
    Sharpen s;
    s.process(img);
    EdgeDetection ed;
    ed.process(img);
    BoxBlur bb;
    bb.process(img);
    Emboss ess;
    ess.process(img);
    Image * gray_image=img.ConvertRGB2BW(&img);
    gray_image->Save("GrayImage.pgm");
    gray_image->Show("GrayImage");

    //Aggiungere campo nome nella classe Immagine

    waitKey(0); // Wait for a keystroke in the window
    delete gray_image;
    return 0;

}