
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <fstream>
#include "src/kip.h"
#include "src/Image.h"


using namespace std;
using namespace cv;
int main() {
    string imageName( "/Users/giuliogambassi/Downloads/KernelImageProcessing-master/marbles1.pbm" ); // by default
    cout<<"Loading image located at "<< imageName<<"..."<<endl;
    Image img;
    try {
        img.Load(imageName);
    }
    catch(invalid_argument &ex){
        cout<<"Exiting the program"<<endl;
        exit(-1);
    }
    int option = -1;
    cout<<"Choose which effect you would like to apply:"<<endl;
    cout<<"0:Gaussian Blur|1:Sobel Edge|2:Sharpen|3:Edge Detection|4:Box Blur|5:Emboss"<<endl;
    cin>>option;

    Gaussian_Blur gb;
    SobelEdge se;
    Sharpen s;
    EdgeDetection ed;
    BoxBlur bb;
    Emboss ess;
    Image dst;

    while(cin.fail()||option<0||option>5){
        cout<<"Not valid, please retry"<<endl;
        cin>>option;
    }
    switch(option) {
        case 0:
            dst = gb.process(img);
            if(dst.getChannels()>1)
                dst.Save("GaussianBlur.ppm");
            else
                dst.Save("GaussianBlur.pgm");
            break;
        case 1:
            dst = se.process(img);
            dst.Save("SobelEdge.pgm");
            break;
        case 2:
            dst = s.process(img);
            if(dst.getChannels()>1)
                dst.Save("Sharpen.ppm");
            else
                dst.Save("Sharpen.pgm");
            break;
        case 3:
            dst = ed.process(img);
            dst.Save("EdgeDetection.pgm");
            break;
        case 4:
            dst = bb.process(img);
            if(dst.getChannels()>1)
                dst.Save("BoxBlur.ppm");
            else
                dst.Save("BoxBlur.pgm");
            break;
        case 5:
            dst = ess.process(img);
            if(dst.getChannels()>1)
                dst.Save("Emboss.ppm");
            else
                dst.Save("Emboss.pgm");
            break;
        default:
            exit(-2);
    }
    cout<<"Showing original image:"<<endl;
    img.Show("Original Image");
    dst.Show("Processed Image");



    /*se.process(img);

    s.process(img);

    ed.process(img);

    bb.process(img);

    ess.process(img);
    Image * gray_image=img.ConvertRGB2BW(&img);
    gray_image->Save("GrayImage.pgm");
    gray_image->Show("GrayImage");

    //Aggiungere campo nome nella classe Immagine

    waitKey(0); // Wait for a keystroke in the window
    delete gray_image;*/

    waitKey(0);
    return 0;

}