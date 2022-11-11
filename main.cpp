#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{

    Mat image = imread("sample.jpg", IMREAD_COLOR);
    imshow("Window", image);



    waitKey(0);

    return 0;
}