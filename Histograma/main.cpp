#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
// P7
void histograma(Mat img, Mat* grafica, int* h){
    uchar* pImg;
    for (int i = 0; i < img.rows; i++)
    {
        /* code */
        pImg = img.ptr<uchar>(i);
        for (int j = 0; j < img.cols; j++){
            h[pImg[j]] ++;
        }
    }
    for (int i = 0; i < 256; i++)
    {
        std::cout << "h["<<i<<"] = "<< h[i] << std::endl;
    }
    
    int *intensidadMax = std::max_element(h,h+256);
  
    std::cout << *intensidadMax;
    grafica ->create(256,256, CV_8UC1);
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < h[i]*256/(*intensidadMax); j++)
        {
            pImg = grafica->ptr<uchar>(grafica->rows-j-1);
            pImg[i] = 255;
        }
    }
        
}

// P8
void adaptacionContraste(Mat img_src, Mat *img_dst){
    Mat grafica;
    int h[256] = {0};
    histograma(img_src, &grafica, h);
    int pMin=0,pMax = 255, pHigh, pLow;
    for (int i = 0; i < 256; i++)
    {
        if(h[i]!=0){
            pLow = i;
            break;
        }
    }
    for (int i = 255; i >= 0; i--)
    {
        if(h[i]!=0){
            pHigh = i;
            break;
        }
    }
    uchar p;
    for (int i = 0; i < img_src.rows; i++)
    {
        for (int j = 0; j < img_src.cols; j++)
        {
            p = img_src.at<uchar>(i,j);
            img_dst->at<uchar>(i,j) = (p-pLow)*(pMax-pMin)/(pHigh-pLow) + pMin;
        }
        
    }
    
    
}   


int main(int argc, char **argv)
{

    Mat image = imread("jill.jpg", IMREAD_GRAYSCALE);
    imshow("Window", image);
    Mat grafica;
    int h[256] = {0};
    histograma(image, &grafica, h);
    imshow("histograma", grafica);


    //contraste p8!!!
    Mat imgContraste(image.rows,image.cols, image.type());
    adaptacionContraste(image, &imgContraste);
    imshow ("adaptacion contraste", imgContraste);


    Mat grafica2;
    int h2[256] = {0};
    histograma(imgContraste, &grafica2, h2);
    imshow("histograma 2",grafica2);
    // p8


    waitKey(0);

    return 0;
}