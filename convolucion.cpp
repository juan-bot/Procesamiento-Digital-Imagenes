//de una imagen a color dividirla en 3 R G B
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
int main(int argc, char** argv){

	int i, j,tam, bordet;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
	printf("Ingresa el tam de la matriz\n");
	scanf("%d",&tam);
	int matriz[tam][tam],div=0;
	bordet=tam/2;
	cv:: Scalar fondo(127,127,127);
  cv:: Scalar fondo2(0,0,0);
	cv::Mat A = cv::imread(argv[1]);

	cv::Mat B ( A.rows,A.cols,CV_8UC1,fondo);
	cv::Mat C ( A.rows+bordet,A.cols+bordet,CV_8UC1,fondo2);
	cv::Mat D ( A.rows+bordet,A.cols+bordet,CV_8UC1,fondo2);

	cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);


	printf("ingresa los valores de la matriz\n");
	for(j=0;j<tam;j++)
		for(i=0;i<tam;i++)
			scanf("%d",&matriz[j][i]);

	printf("\nMatriz ingresada\n");
	for(j=0;j<tam;j++){
		for(i=0;i<tam;i++){
			printf("[%d]",matriz[j][i]);
		}
		printf("\n");
	}
	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglon1=B.ptr<uchar>(j);
		for(i=0;i<A.cols;i++){
			*(renglon1+i)= (0.07* *(renglon+i*3+0)) + (0.716* *(renglon+i*3+1)) + (0.21* *(renglon+i*3+2));
		}
	}
	for(j=bordet;j<A.rows;j++){
		uchar *renglon=B.ptr<uchar>(j);
		uchar *renglon1=C.ptr<uchar>(j);
		uchar *renglon2=D.ptr<uchar>(j);
		for(i=bordet;i<A.cols;i++){
			*(renglon1+i)= *(renglon+i);
			*(renglon2+i)= *(renglon+i);

		}
	}

	int suma;
	for(j=0;j<A.rows;j++){
		uchar *renglon2=D.ptr<uchar>(j+1);
		for(i=0;i<A.cols;i++){
			suma=0;
			for(int k=0; k < tam; k++){
				uchar *renglon1=C.ptr<uchar>(j+k);
				for(int l=0; l < tam ; l++){
						suma += *(renglon1+i+l) * matriz[k][l];
				}
			}
			/*if(suma < 0)
				suma=0;
			else
				if(suma>255)
				 suma =255;*/
			printf("%d , %d\n",*(renglon2+i+bordet),suma);
			div=*(renglon2+i+bordet)/suma;
			if(div < 0)
				div=0;
			else
				if(div>255)
				 div =255;
			*(renglon2+i+bordet)=div;
		}
	}

	cv::imshow("Original",A);
	cv::imshow("convolucion",D);
	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;
}
