#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void escalar(Mat img_src, Mat *img_dst, float cx, float cy)
{
    // cx y cy > factores de escalamiento, y son valores flotantes
    // 1) Si Cx y Cy son mayores a 1 - crecimiento proporcional > 100%
    // 2) Si Cx y Cy son menores a 1 - decrecimiento proporcional < 100%
    float T[3][3] = {{cx, 0, 0}, {0, cy, 0}, {0, 0, 1}}; // Matriz afin para escalamiento
    uchar *pImg_src, *pImg_dst;                          // Punteros a la imagen original y a la imagen destino
    int *v, *w;
    int k = 0;
    int imgSize = img_src.rows * img_src.cols;
    v = (int *)malloc(sizeof(int) * imgSize);
    w = (int *)malloc(sizeof(int) * imgSize);
    for (int x = 0; x < img_src.rows; x++)
    {
        for (int y = 0; y < img_src.cols; y++)
        {
            // Se transforman las coordenadas x, y
            v[k] = (x * T[0][0]) + (y * T[1][0] + (1 * T[2][0]));
            w[k] = (x * T[0][1]) + (y * T[1][1] + (1 * T[2][1]));
            k++;
        }
    }
    int *pMax_v = max_element(v, v + imgSize);
    int *pMax_w = max_element(w, w + imgSize);
    img_dst->create(*pMax_v + 1, *pMax_w + 1, img_src.type());
    k = 0;
    for (int x = 0; x < img_src.rows; x++)
    {
        pImg_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            pImg_dst = img_dst->ptr<uchar>(v[k]);
            pImg_dst[w[k]] = pImg_src[y];
            k++;
        }
    }
    free(v);
    free(w);
}
void rotar(Mat img_src, Mat *img_dst, double grados)
{
    const double PI = 3.1416;
    double anguloRad = grados * (PI / 180);
    double T[3][3] = {{cos(anguloRad), sin(anguloRad), 0},
                      {-sin(anguloRad), cos(anguloRad), 0},
                      {0, 0, 1}};
    int vecSize = img_src.rows * img_src.cols;
    int *v = (int *)malloc(sizeof(int) * vecSize);
    int *w = (int *)malloc(sizeof(int) * vecSize);
    int k = 0;
    uchar *pImg_src, *pImg_dst;
    for (int x = 0; x < img_src.rows; x++)
    {
        pImg_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            // Se transforman las coordenadas x, y
            v[k] = (x * T[0][0]) + (y * T[1][0]) + (1 * T[2][0]);
            w[k] = (x * T[0][1]) + (y * T[1][1]) + (1 * T[2][1]);
            k++;
        }
    }
    int *pMin_v = min_element(v, v + vecSize); // Valor minimo del vector v
    int *pMin_w = min_element(w, w + vecSize); // Valor minimo del vector w
    int min_v = *pMin_v;
    int min_w = *pMin_w;
    for (int i = 0; i < vecSize; i++)
    {
        v[i] = v[i] - min_v;
        w[i] = w[i] - min_w;
    }
    int *pMax_v = max_element(v, v + vecSize); // Valor minimo del vector v
    int *pMax_w = max_element(w, w + vecSize); // Valor minimo del vector w
    int max_v = *pMax_v;
    int max_w = *pMax_w;
    img_dst->create(max_v + 1, max_w + 1, img_src.type());
    k = 0;
    for (int x = 0; x < img_src.rows; x++)
    {
        pImg_src = img_src.ptr<uchar>(x); // imagen origen apunta a x
        for (int y = 0; y < img_src.cols; y++)
        {
            pImg_dst = img_dst->ptr<uchar>(v[k]); // imagen destino apunta a v
            pImg_dst[w[k]] = pImg_src[y];
            k++;
        }
    }
    free(v);
    free(w);
}
void trasladar(Mat img_src, Mat *img_dst, int tx, int ty)
{
    //
    int T[3][3] = {{1, 0, 0},
                   {0, 1, 0},
                   {0, 0, 1}};  // Matriz afin para traslacion
    uchar *pImg_src, *pImg_dst; // Punteros a la imagen original y a la imagen destino
    int v, w;
    img_dst->create(img_src.rows + tx, img_src.cols + ty, CV_8UC1);
    for (int x = 0; x < img_src.rows; x++)
    {
        pImg_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            // Se transforman las coordenadas x, y
            v = (x * T[0][0]) + (y * T[1][0] + (1 * T[2][0]));
            w = (x * T[0][1]) + (y * T[1][1] + (1 * T[2][1]));
            pImg_dst = img_dst->ptr<uchar>(v);
            pImg_dst[w] = pImg_src[y];
        }
    }
}
void sesgoV(Mat img_src, Mat *img_dst, float sv)
{
    double T[3][3] = {{1, 0, 0},
                      {sv, 1, 0},
                      {0, 0, 1}};
    int *v, *w, k = 0;
    int vecSize = img_src.rows * img_src.cols;
    v = (int *)malloc(sizeof(int) * vecSize);
    w = (int *)malloc(sizeof(int) * vecSize);
    uchar *pImg_src, *pImg_dst;
    for (int x = 0; x < img_src.rows; x++)
    {
        pImg_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            // Se transforman las coordenadas x, y
            v[k] = (x * T[0][0]) + (y * T[1][0]) + (1 * T[2][0]);
            w[k] = (x * T[0][1]) + (y * T[1][1]) + (1 * T[2][1]);
            k++;
        }
    }
    int *pMax_v = max_element(v, v + vecSize); // Valor minimo del vector v
    int *pMax_w = max_element(w, w + vecSize); // Valor minimo del vector w
    img_dst->create(*pMax_v + 1, *pMax_w + 1, CV_8UC1);
    k = 0;
    for (int x = 0; x < img_src.rows; x++)
    {
        pImg_src = img_src.ptr<uchar>(x); // imagen origen apunta a x
        for (int y = 0; y < img_src.cols; y++)
        {
            pImg_dst = img_dst->ptr<uchar>(v[k]); // imagen destino apunta a v
            pImg_dst[w[k]] = pImg_src[y];
            k++;
        }
    }
    free(v);
    free(w);
}
void sesgoH(Mat img_src, Mat *img_dst, float sh)
{
    double T[3][3] = {{1, sh, 0},
                      {0, 1, 0},
                      {0, 0, 1}};
    int *v, *w, k = 0;
    int vecSize = img_src.rows * img_src.cols;
    v = (int *)malloc(sizeof(int) * vecSize);
    w = (int *)malloc(sizeof(int) * vecSize);
    uchar *pImg_src, *pImg_dst;
    for (int x = 0; x < img_src.rows; x++)
    {
        pImg_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            // Se transforman las coordenadas x, y
            v[k] = (x * T[0][0]) + (y * T[1][0]) + (1 * T[2][0]);
            w[k] = (x * T[0][1]) + (y * T[1][1]) + (1 * T[2][1]);
            k++;
        }
    }
    int *pMax_v = max_element(v, v + vecSize); // Valor minimo del vector v
    int *pMax_w = max_element(w, w + vecSize); // Valor minimo del vector w
    img_dst->create(*pMax_v + 1, *pMax_w + 1, CV_8UC1);
    k = 0;
    for (int x = 0; x < img_src.rows; x++)
    {
        pImg_src = img_src.ptr<uchar>(x); // imagen origen apunta a x
        for (int y = 0; y < img_src.cols; y++)
        {
            pImg_dst = img_dst->ptr<uchar>(v[k]); // imagen destino apunta a v
            pImg_dst[w[k]] = pImg_src[y];
            k++;
        }
    }
    free(v);
    free(w);
}
int main()
{
    Mat img = imread("imagenDePrueba.jpg", IMREAD_GRAYSCALE);
    Mat imgEscalada, imgEscaladaOpenCV, imgRotacion, imgTrasladada, imgSesgoV, imgSesgoVEsc,
        imgSesgoH;
    float fx = 1.2, fy = 1.2;
    imshow("Imagen original", img);
    escalar(img, &imgEscalada, 0.4, 0.8); // La imagen original se escala a un 50% menor del tamañooriginal
        imshow("CX = 0.4, CY = 0.8", imgEscalada);
    escalar(img, &imgEscalada, 0.5, 0.5); // La imagen original se escala a un 50% menor del tamañooriginal
        imshow("CX = 0.5, CY = 0.5", imgEscalada);
    resize(img, imgEscaladaOpenCV, Size(img.cols * fy, img.rows * fx), fx, fy, INTER_LINEAR);
    imshow("Imagen escalada OpenCV", imgEscaladaOpenCV);
    resize(img, img, Size(img.cols / 1.2, img.rows / 1.2));
    rotar(img, &imgRotacion, 45);
    imshow("Imagen rotacion 45", imgRotacion);
    rotar(img, &imgRotacion, -45);
    imshow("Imagen rotacion -45", imgRotacion);
    rotar(img, &imgRotacion, 15);
    imshow("Imagen rotacion 15", imgRotacion);
    rotar(img, &imgRotacion, -15);
    imshow("Imagen rotacion -15", imgRotacion);
    rotar(img, &imgRotacion, 180);
    imshow("Imagen rotacion 180", imgRotacion);
    rotar(img, &imgRotacion, 90);
    imshow("Imagen rotacion 90", imgRotacion);
    rotar(img, &imgRotacion, -90);
    imshow("Imagen rotacion -90", imgRotacion);
    trasladar(img, &imgTrasladada, 50, 50);
    imshow("Imagen trasladada tx = 50, ty = 50", imgTrasladada);
    trasladar(img, &imgTrasladada, 50, 100);
    imshow("Imagen trasladada tx = 50, ty = 100", imgTrasladada);
    sesgoV(img, &imgSesgoV, 1);
    escalar(imgSesgoV, &imgSesgoV, 0.5, 0.5);
    imshow("Sesgo Vertical 1", imgSesgoV);
    sesgoV(img, &imgSesgoV, 0.5);
    escalar(imgSesgoV, &imgSesgoV, 0.5, 0.5);
    imshow("Sesgo Vertical 0.5", imgSesgoV);
    sesgoH(img, &imgSesgoH, 1);
    escalar(imgSesgoH, &imgSesgoH, 0.5, 0.5);
    imshow("Sesgo Horizonal 1", imgSesgoH);
    sesgoH(img, &imgSesgoH, 0.5);
    escalar(imgSesgoH, &imgSesgoH, 0.5, 0.5);
    imshow("Sesgo Horizonal 0.5", imgSesgoH);
    escalar(img, &img, 2, 2);
    imshow("Escalamiento (cx = 2, cy = 2)", img);
    waitKey(0);
}