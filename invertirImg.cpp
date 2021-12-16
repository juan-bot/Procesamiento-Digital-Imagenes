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

	cv::Mat A =cv::imread(argv[1],0);
	cv::Mat B ( A.rows,A.cols,CV_8UC1);
	printf("Columnas: %d, Filas: %d, Canales: %d\n", A.cols, A.rows, A.channels());

	cv::namedWindow("invertida", cv::WINDOW_AUTOSIZE);
//B G R
	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglon1=B.ptr<uchar>(j);
		for(i=0;i<A.cols;i++){

			*(renglon1+i+0)= 255-1-*(renglon+i+0);
		}
	}
	cv::imshow("invertida",B);

	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;

}
