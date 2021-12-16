#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#define SIN(x) sin(x*acos(-1)/180)
#define COS(x) cos(x*acos(-1)/180)

using namespace cv;

Mat rotarOpenCV(Mat image, double angulo);
void rota(int filas, int columnas, int grados, Mat A);

int main(int argc, char** argv){
	int i, j;
	Mat im = imread(argv[1],0);
	namedWindow("Imagen", cv::WINDOW_AUTOSIZE);
	imshow("Imagen", im);
	printf("Columnas: %d, Filas: %d, Canales: %d\n", im.cols, im.rows, im.channels());
	Mat resultado = rotarOpenCV(im, 45.0);

	imshow("OpenCv", resultado);
	rota(im.rows, im.cols, 45, im);
	int tecla;
	while (true) {
		tecla = waitKey(0);
		if (tecla == 27) {
			break;
		}
	}
	return 0;
}

Mat rotarOpenCV(Mat image, double angulo) {
	Mat res;
	Point2f pt(image.cols / 2, image.rows / 2);
	Mat r = getRotationMatrix2D(pt, angulo, 1.0);
	warpAffine(image, res, r, Size(image.cols, image.rows));
	return res;
}

void rota(int filas, int columnas, int grados, Mat A){
	int nDF = (filas * abs(COS(grados)) + columnas * abs(SIN(grados)));
	int nDC = (filas * abs(SIN(grados)) + columnas * abs(COS(grados)));
	Mat R(nDF, nDC, CV_8UC1);
	int refy = nDC / 2;
	int refx = nDF / 2;
	int xoffset = refx - filas / 2;
	int yoffset = refy - columnas / 2;
	for (int j = 0; j < filas; j++){
		uchar* ren = A.ptr<uchar>(j);
		for (int i = 0; i < columnas; i++){
			int nuevax = j - refx + xoffset;
			int nuevay = i - refy + yoffset;
			int xprima = refx + (nuevax * COS(grados) - nuevay * SIN(grados));
			int yprima = refy + (nuevax * SIN(grados) + nuevay * COS(grados));

			if (xprima >= 0 && xprima < nDF && yprima >= 0 && yprima < nDC){
				uchar* renC = R.ptr<uchar>(xprima);
				if(j<10)
					printf("%d + %d = %d + %d\n",xprima,yprima,j,i);
				*(renC + yprima) = *(ren + i);
			}
		}

	}

	imshow("A mano", R);

}
