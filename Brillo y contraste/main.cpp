#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

void copia(Mat img_src, Mat *img_dst) {
    uchar* pImg_src, *pImg_dst; //puntero para apuntar a las filas
    img_dst->create(img_src.rows, img_src.cols, img_src.type()); //se genera una copia de las filas y columnas de la imagen fuente

    for (int i = 0; i < img_src.rows; i++) {
        pImg_src = img_src.ptr<uchar>(i);
        pImg_dst = img_dst->ptr<uchar>(i);

        for (int j = 0; j < img_src.cols; j++) {
            pImg_dst[j] = pImg_src[j];
        }
    }

}


//El contraste de una imagen se modifica multiplicando los pixeles de una imagen por una constante.
// fc >1 +
// fc < 1 -     (fc = factor de contraste)
void contraste(Mat img_src, Mat* img_dst, float fc) {
    uchar* pImg_src, * pImg_dst; //puntero para apuntar a las filas

    double pixel;
    img_dst->create(img_src.rows, img_src.cols, img_src.type()); //se genera una copia de las filas y columnas de la imagen fuente

    for (int i = 0; i < img_src.rows; i++) {
        pImg_src = img_src.ptr<uchar>(i);
        pImg_dst = img_dst->ptr<uchar>(i);

        for (int j = 0; j < img_src.cols; j++) {
            pixel=  pImg_src[j] * fc;
            if (pixel > 255) {
                pImg_dst[j] = 255;
            }
            else {
                pImg_dst[j] = (uchar)pixel;
            }
        }
    }

}


//fb -> factor de brillo entero
void brillo(Mat img_src, Mat* img_dst, int fb) {
    img_dst->create(img_src.rows, img_src.cols, img_src.type());
    uchar* pImg_src, * pImg_dst; //puntero para apuntar a las filas

    double pixel;
    

    for (int i = 0; i < img_src.rows; i++) {
        pImg_src = img_src.ptr<uchar>(i);
        pImg_dst = img_dst->ptr<uchar>(i);

        for (int j = 0; j < img_src.cols; j++) {
            pixel = pImg_src[j] + fb;

            if (pixel > 255) {
                pImg_dst[j] = 255;
            }
            else if (pixel < 0) {
                pImg_dst[j] = 0;
            }
            else {
                pImg_dst[j] = (uchar)pixel;
            }
            
        }
    }
}

int main() {
    Mat img = imread("sample.jpg", IMREAD_GRAYSCALE);
    imshow("Imagen original", img);

    Mat imgCopia, imgContrasteMas, imgContrasteMenos, imgBrillo;

    copia(img, &imgCopia);
    contraste(img, &imgContrasteMas, 1.5);
    contraste(img, &imgContrasteMenos, 0.5);

    brillo(img, &imgBrillo, 100);
    imshow("Copia", imgCopia);

    imshow("Contraste Mas", imgContrasteMas);
    imshow("Contraste Menos", imgContrasteMenos);
    imshow("Brillo mas", imgBrillo);


    waitKey(0);
}