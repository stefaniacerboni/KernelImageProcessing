
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <fstream>
#include "src/kip.h"
#include "src/Image.h"


using namespace std;
using namespace cv;
int main() {
    string imageName( "/Users/giuliogambassi/Downloads/KernelImageProcessing-master/building.pgm" ); // by default
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

    while(cin.fail()||option<0||option>5){
        cout<<"Not valid, please retry"<<endl;
        cin>>option;
    }
    switch(option) {
        case 0:
            gb.process(img);
            break;
        case 1:
            se.process(img);
            break;
        case 2:
            s.process(img);
            break;
        case 3:
            ed.process(img);
            break;
        case 4:
            bb.process(img);
            break;
        case 5:
            ess.process(img);
            break;
        default:
            exit(-2);
    }
    cout<<"Showing original image:"<<endl;



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
    img.Show("Original Image");
    waitKey(0);
    return 0;

}