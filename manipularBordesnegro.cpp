// dando click en la imagen, muestra el color que selecciono en una barra
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
static void mifuncion(int valor,void *params);
Mat A ;
int main(int argc, char** argv){
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}

	A = cv::imread(argv[1],0);
	//Mat R= Mat:: zeros(A.rows,A.cols,CV_8UC1);
	Mat R ( A.rows,A.cols,CV_8UC1);
	printf("Columnas: %d, Filas: %d, Canales: %d\n", A.cols, A.rows, A.channels());

	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglonR=R.ptr<uchar>(j);
		for(i=0;i<A.cols;i++){
			*(renglonR+i+0)=*(renglon+i+0);
		}
	}
  int valor=0;//valor inicial de la barra
	cv::imshow("Ventana",R);
	createTrackbar("Bordes","Ventana",&valor,4,mifuncion,&A);
  int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;
}

static void mifuncion(int valor,void *params){
	//cv::namedWindow("Ventana", cv::WINDOW_AUTOSIZE);
	Mat orig=*(Mat *)params;
	int i,j,valores[4]={0};
	if(valor==0)
		cv::imshow("Ventana",orig);
	if(valor==1 || valor ==2 || valor==3 || valor ==4){

		//Mat res= Mat:: zeros(A.rows,A.cols,CV_8UC1);
		Mat res ( A.rows,A.cols,CV_8UC1);
		for(j=0;j<orig.rows;j++){
			uchar *renglon=orig.ptr<uchar>(j);
			uchar *renglon1=res.ptr<uchar>(j);
			uchar *renglon2=orig.ptr<uchar>(j+1);
			for(i=0;i<orig.cols;i++){
				//resta renglones
					valores[0]= fabs((*(renglon+i+0))-(*(renglon2+i+0)));
				//resta columnas
					valores[1]= fabs((*(renglon+i))-(*(renglon+i+1)));
				//resta diagonal
					valores[2]= fabs((*(renglon+i))-(*(renglon2+i+1)));
				//////////////////////encontrar el mayor///////////////////////////
				if(valores[0] >= valores[1] && valores[0] >= valores[2])
					valores[3]=valores[0];
				else {
					if(valores[1] > valores[2])
						valores[3]=valores[1];
					else
						valores[3]=valores[2];
				}

				if(valor==1){
					if(j<orig.rows-1)
						*(renglon1+i+0)= valores[0];
					else
						*(renglon1+i+0)= 0;
				}
				if(valor==2){
					if(i<A.cols-1)
						*(renglon1+i+0)= valores[1];
					else
					  *(renglon1+i+0)=0;
				}
				if(valor==3){
					if(i<A.cols-1 && j<A.rows-1)
					  *(renglon1+i+0)= valores[2];
					else
						*(renglon1+i+0)=0;
				}
				if(valor==4){
					if(i<A.cols-1 && j<A.rows-1)
 						*(renglon1+i+0)= valores[3];
 					else
 					  *(renglon1+i+0)=0;
				}
			}
		}
		cv::imshow("Ventana",res);
		res.release();
	}
}
