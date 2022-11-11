#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void copia(Mat img_src, Mat *img_dst)
{
    uchar *pImg_src, *pImg_dst;                                  // puntero para apuntar a las filas
    img_dst->create(img_src.rows, img_src.cols, img_src.type()); // se genera una copia de las filas ycolumnas de la imagen fuente 
    for (int i = 0; i < img_src.rows; i++)
    {
        pImg_src = img_src.ptr<uchar>(i);
        pImg_dst = img_dst->ptr<uchar>(i);
        for (int j = 0; j < img_src.cols; j++)
        {
            pImg_dst[j] = pImg_src[j];
        }
    }
}
void contraste(Mat img_src, Mat *img_dst, float fc)
{
    uchar *pImg_src, *pImg_dst; // puntero para apuntar a las filas
    double pixel;
    img_dst->create(img_src.rows, img_src.cols, img_src.type());
    for (int i = 0; i < img_src.rows; i++)
    {
        pImg_src = img_src.ptr<uchar>(i);
        pImg_dst = img_dst->ptr<uchar>(i);
        for (int j = 0; j < img_src.cols; j++)
        {
            pixel = pImg_src[j] * fc;
            if (pixel > 255)
            {
                pImg_dst[j] = 255;
            }
            else
            {
                pImg_dst[j] = (uchar)pixel;
            }
        }
    }
}
void brillo(Mat img_src, Mat *img_dst, int fb)
{
    img_dst->create(img_src.rows, img_src.cols, img_src.type());
    uchar *pImg_src, *pImg_dst; // puntero para apuntar a las filas
    double pixel;
    for (int i = 0; i < img_src.rows; i++)
    {
        pImg_src = img_src.ptr<uchar>(i);
        pImg_dst = img_dst->ptr<uchar>(i);
        for (int j = 0; j < img_src.cols; j++)
        {
            pixel = pImg_src[j] + fb;
            if (pixel > 255)
            {
                pImg_dst[j] = 255;
            }
            else if (pixel < 0)
            {
                pImg_dst[j] = 0;
            }
            else
            {
                pImg_dst[j] = (uchar)pixel;
            }
        }
    }
}
void complemento(Mat img_src, Mat *img_dst)
{
    img_dst->create(img_src.rows, img_src.cols, img_src.type());
    uchar *pImg_src, *pImg_dst; // puntero para apuntar a las filas
    double pixel;
    for (int i = 0; i < img_src.rows; i++)
    {
        pImg_src = img_src.ptr<uchar>(i);
        pImg_dst = img_dst->ptr<uchar>(i);
        for (int j = 0; j < img_src.cols; j++)
        {
            pImg_dst[j] = 255 - pImg_src[j];
        }
    }
}
void complementoRGB(Mat img_src, Mat *img_dst)
{
    img_dst->create(img_src.rows, img_src.cols, img_src.type());
    Vec3b *pImg_src, *pImg_dst; // puntero para apuntar a las filas
    double pixel;
    for (int i = 0; i < img_src.rows; i++)
    {
        pImg_src = img_src.ptr<Vec3b>(i);
        pImg_dst = img_dst->ptr<Vec3b>(i);
        for (int j = 0; j < img_src.cols; j++)
        {
            pImg_dst[j][0] = 255 - pImg_src[j][0];
            pImg_dst[j][1] = 255 - pImg_src[j][1];
            pImg_dst[j][2] = 255 - pImg_src[j][2];
        }
    }
}
// Combinacion -> grises
// factor w;
void combinacion(Mat img_src, Mat img_src2, Mat *img_dst, float w)
{
    // img_dst->create(500,500,img_src.rows, img_src.cols, img_src.type());
    img_dst->create(img_src.rows, img_src.cols, img_src.type());
    uchar *pImg_src, *pImg_src2, *pImg_dst; // puntero para apuntar a las filas
    for (int i = 0; i < img_src.rows; i++)
    {
        pImg_src = img_src.ptr<uchar>(i);
        pImg_src2 = img_src2.ptr<uchar>(i);
        pImg_dst = img_dst->ptr<uchar>(i);
        for (int j = 0; j < img_src.cols; j++)
        {
            pImg_dst[j] = w * pImg_src[j] + (1 - w) * pImg_src2[j];
        }
    }
}
int main()
{
    Mat img = imread("imagenDePrueba.jpg", IMREAD_GRAYSCALE);
    Mat imgRGB = imread("imagenDePrueba.jpg");
    Mat img2 = imread("jill.jpg", IMREAD_GRAYSCALE);
    Mat imgCopia, imgContrasteMas, imgContrasteMenos, imgBrillo, imgComplemento, imgComplementoRGB, imgCombinacion;
    // resize(img, img, Size(img.cols / 2, img.rows / 2)); // Tamaño mas pequeño por problemas de visualizacion
        // resize(imgRGB, imgRGB, Size(imgRGB.cols / 2, imgRGB.rows / 2)); // Tamaño mas pequeño por problemas de visualizacion
    imshow("Imagen 1 original", img);
    imshow("Imagen 2 original", img2);
    copia(img, &imgCopia);
    imshow("Copia", imgCopia);
    contraste(img, &imgContrasteMas, 1.5);
    imshow("Contraste Mas", imgContrasteMas);
    contraste(img, &imgContrasteMenos, 0.5);
    imshow("Contraste Menos", imgContrasteMenos);
    brillo(img, &imgBrillo, 100);
    imshow("Brillo mas", imgBrillo);
    brillo(img, &imgBrillo, -100);
    imshow("Brillo menos", imgBrillo);
    complemento(img, &imgComplemento);
    imshow("Complemento", imgComplemento);
    complementoRGB(imgRGB, &imgComplementoRGB);
    imshow("complemento RGB", imgComplementoRGB);
    combinacion(img, img2, &imgCombinacion, 0.7);
    imshow("Combinación 0.7", imgCombinacion);
    combinacion(img, img2, &imgCombinacion, 0.5);
    imshow("Combinación 0.5", imgCombinacion);
    combinacion(img, img2, &imgCombinacion, 0.3);
    imshow("Combinación 0.3", imgCombinacion);
    waitKey(0);
}