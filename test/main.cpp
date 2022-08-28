#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{

    Mat image;

    image = imread("sample.png", IMREAD_COLOR);

    if (!image.data)
    {

        std::cout << "Could not open or find the image" << std::endl;

        return -1;
    }

    namedWindow("Display window", WINDOW_AUTOSIZE);

    resize(image, image, Size(1200, 800), INTER_LINEAR);

    imshow("Display window", image);

    waitKey(0);

    return 0;
}