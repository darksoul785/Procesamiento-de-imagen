#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{
    // se agrega la imagen
    Mat image = imread("sample.jpg", IMREAD_COLOR);
    imshow("Window", image);

    // se crea una matriz de la imagen original
    Mat imgGris(image.rows, image.cols, CV_8UC1);
    Mat imgGrisLuma1(image.rows, image.cols, CV_8UC1);
    Mat imgGrisLuma2(image.rows, image.cols, CV_8UC1);
    Mat imgGrisLuma3(image.rows, image.cols, CV_8UC1);
    Mat imgGrisDES(image.rows, image.cols, CV_8UC1);

    // se crean punteros a las matrices, vec3b es para 3 capaz de color y uchar unsigned char
    Vec3b *pImage;
    uchar vector[3], *pMax, *pMin;
    uchar *pImageGris_Promedio, *pImageGris_Luma1, *pImageGris_Luma2, *pImageGris_Luma3;
    uchar *pImageGris_DES;
    // con un ciclo for se pasan los valores de la imagen original a la nueva
    for (int i = 0; i < image.rows; i++)
    {
        pImage = image.ptr<Vec3b>(i);
        pImageGris_Promedio = imgGris.ptr<uchar>(i);
        pImageGris_Luma1 = imgGrisLuma1.ptr<uchar>(i);
        pImageGris_Luma2 = imgGrisLuma2.ptr<uchar>(i);
        pImageGris_Luma3 = imgGrisLuma3.ptr<uchar>(i);

        pImageGris_DES = imgGrisDES.ptr<uchar>(i);
        for (int j = 0; j < image.cols; j++)
        {
            pImageGris_Promedio[j] = ((pImage[j][0] + pImage[j][1] + pImage[j][2]) / 3);
            pImageGris_Luma1[j] = (0.11 * pImage[j][0] + 0.59 * pImage[j][1] + 0.3 * pImage[j][2]);
            pImageGris_Luma2[j] = (0.0722 * pImage[j][0] + 0.7152 * pImage[j][1] + 0.2126 * pImage[j][2]);
            pImageGris_Luma3[j] = (0.114 * pImage[j][0] + 0.587 * pImage[j][1] + 0.299 * pImage[j][2]);

            for (int k = 0; k < 3; k++)
            {
                vector[k] = pImage[j][k];
            }
            pMax = std::max_element(vector, vector + 3);
            pMin = std::min_element(vector, vector + 3);
            pImageGris_DES[j] = (*pMax + *pMin) / 2;
        }
    }
    imshow("Promedio", imgGris);
    imshow("Photoshop", imgGrisLuma1);
    imshow("Luma2", imgGrisLuma2);
    imshow("Luma3", imgGrisLuma3);
    imshow("Des", imgGrisDES);
    waitKey(0);

    return 0;
}