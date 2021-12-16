//de una imagen a color dividirla en 3 R G B
#include <stdio.h>
#include <opencv2/opencv.hpp>
int main(int argc, char** argv){
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
	cv:: Scalar fondo(127,127,127);

	cv::Mat A =cv::imread(argv[1]);
	cv::Mat B ( A.rows,A.cols,CV_8UC3,fondo);
	cv::Mat C ( A.rows,A.cols,CV_8UC3,fondo);
	cv::Mat D ( A.rows,A.cols,CV_8UC3,fondo);
	printf("Columnas: %d, Filas: %d, Canales: %d\n", A.cols, A.rows, A.channels());

	cv::namedWindow("Rojos", cv::WINDOW_AUTOSIZE);
//B G R
	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglonR=B.ptr<uchar>(j);
		uchar *renglonA=C.ptr<uchar>(j);
		uchar *renglonV=D.ptr<uchar>(j);
		for(i=0;i<A.cols*3;i+=3){

			*(renglonR+i+1)=*(renglon+i+1);
			*(renglonR+i+0)=0;
			*(renglonR+i+2)=0;

			*(renglonA+i+0)=*(renglon+i+0);
			*(renglonA+i+1)=0;
			*(renglonA+i+2)=0;

			*(renglonV+i+2)=*(renglon+i+2);
			*(renglonV+i+0)=0;
			*(renglonV+i+1)=0;
		}
	}
	cv::imshow("Original",A);
	cv::imshow("Rojos",D);
	cv::imshow("Verdes",B);
	cv::imshow("Azules",C);
	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;

}
