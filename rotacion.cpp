//de una imagen a color dividirla en 3 R G B
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
#define sin(x) sin(x*Acos(-1)/180)

Mat rotaOpenCv(Mat src, double angulo);

int main(int argc, char** argv){

	int i, j,tam, bordet;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}

	cv::Mat A = cv::imread(argv[1],0);
	cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);

	Mat resultado =rotaOpenCv(A,45.0);
	printf("original: %d x %d\n",A.cols,A.rows);
	printf("resultante: %d x %d",resultado.cols,resultado.rows);

	cv::imshow("Original",A);
	//cv::imshow("rot",resultado);
	cv::imshow("resultado",resultado);
	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;
}
Mat rotaOpenCv(Mat src, double angulo){
	Mat res;
	Point2f pt(src.cols/2, src.rows/2);
	Mat r = getRotationMatrix2D(pt,angulo,1.0);
	warpAffine( src,res,r,Size(src.cols,src.rows));
	return res;
}
