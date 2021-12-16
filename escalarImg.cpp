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
	cv::Mat B ( A.rows/2,A.cols/2,CV_8UC1);
	printf("Columnas: %d, Filas: %d, Canales: %d\n", A.cols, A.rows, A.channels());

	cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
//B G R
int k=0,z=0;
	for(k=0,j=0;j<B.rows;j++,k+=2){
		uchar *renglon=A.ptr<uchar>(k);
		uchar *renglon1=B.ptr<uchar>(j);
		for(z=0,i=0;i<B.cols;i++,z+=2){
			*(renglon1+i+0)= *(renglon+z+0);
			printf("%d ",z);
		}
		printf("\n");
	}
	cv::imshow("original",A);
	cv::imshow("escalada hacia abajo",B);

	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;

}
