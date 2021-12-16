
#include <stdio.h>
#include <opencv2/opencv.hpp>
int main(int argc, char** argv){
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
	cv:: Scalar fondo(127,127,127);

	cv::Mat A =cv::imread("image2.jpg");
	cv::Mat B =cv::imread("image2.png");
	cv::Mat C ( A.rows,A.cols,CV_8UC3);
	cv::Mat D ( A.rows,A.cols,CV_8UC3);
	cv::Mat E ( A.rows,A.cols,CV_8UC3);
	printf("Columnas: %d, Filas: %d, Canales: %d\n", A.cols, A.rows, A.channels());
	printf("Columnas: %d, Filas: %d, Canales: %d\n", B.cols, B.rows, B.channels());

	cv::namedWindow("img1", cv::WINDOW_AUTOSIZE);
//B G R
	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglon1=B.ptr<uchar>(j);
		uchar *renglon2=C.ptr<uchar>(j);
		uchar *renglon3=D.ptr<uchar>(j);
		uchar *renglon4=E.ptr<uchar>(j);
		for(i=0;i<A.cols*3;i+=3){
			*(renglon2+i)= *(renglon+i) & *(renglon1+i);
			*(renglon2+i+1)= *(renglon+i+1) & *(renglon1+i+1);
			*(renglon2+i+2)= *(renglon+i+2) & *(renglon1+i+2);

			*(renglon3+i)= *(renglon+i) | *(renglon1+i);
			*(renglon3+i+1)= *(renglon+i+1) | *(renglon1+i+1);
			*(renglon3+i+2)= *(renglon+i+2) | *(renglon1+i+2);

			*(renglon4+i)= ~ *(renglon+i);
			*(renglon4+i+1)= ~ *(renglon+i+1);
			*(renglon4+i+2)= ~ *(renglon+i+2);


		}
	}
	cv::imshow("img1",A);
	cv::imshow("img2",B);
	cv::imshow("and",C);
	cv::imshow("or",D);
	cv::imshow("not",E);

	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;

}
