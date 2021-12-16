#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
int main(int argc, char** argv){
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
	cv:: Scalar fondo(127,127,127);

	cv::Mat A =cv::imread(argv[1],0);
	cv::Mat B ( A.rows,A.cols,CV_8UC1);
	cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
//B G R
	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglon1=B.ptr<uchar>(j);
		for(i=0;i<A.cols;i++){
			if(i<A.cols-1)
				*(renglon1+i+0)= fabs((*(renglon+i))-(*(renglon+i+1)));
			else
			  *(renglon1+i+0)=0;
		}
	}
	cv::imshow("original",A);
	cv::imshow("contorno resta Columnas",B);

	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;

}
