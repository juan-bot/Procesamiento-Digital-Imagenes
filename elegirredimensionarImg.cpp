// dando click en la imagen, muestra el color que selecciono en una barra
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
static void mifuncion2(int valor,void *params);
static void mifuncion(int event,int x,int y,int flags,void *param);
Rect boton;
Mat A ;
Scalar fondo(0,0,255);
int main(int argc, char** argv){
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}

	A = cv::imread(argv[1]);
	Mat R= Mat:: zeros(A.rows,A.cols,CV_8UC3);


	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglonR=R.ptr<uchar>(j);
		for(i=0;i<A.cols*3;i+=3){
			*(renglonR+i+0)=*(renglon+i+0);
			*(renglonR+i+1)=*(renglon+i+1);
			*(renglonR+i+2)=*(renglon+i+2);
		}
	}
  int valor=1;//valor inicial de la barra
	cv::imshow("Ventana",R);
	createTrackbar("barra","Ventana",&valor,8,mifuncion2,&A);
  int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;
}

static void mifuncion2(int valor,void *params){
	cv::namedWindow("Ventana", cv::WINDOW_AUTOSIZE);
	Mat orig=*(Mat *)params;
	//Mat res = A.clone();
	int i,j;
	printf("%d\n",valor);
	if(valor==0)
		cv::imshow("Ventana",orig);
  int k=0,z=0;
	if(valor==2 || valor ==4 || valor==8){
		Mat res= Mat:: zeros(A.rows/valor,A.cols/valor,CV_8UC3);
		for(k=0,j=0;j<res.rows;j++,k+=valor){
			uchar *renglon=orig.ptr<uchar>(k);
			uchar *renglon1=res.ptr<uchar>(j);
			for(z=0,i=0;i<res.cols*3;i+=3,z+=valor*3){
				*(renglon1+i+0)= *(renglon+z+0);
				*(renglon1+i+1)= *(renglon+z+1);
				*(renglon1+i+2)= *(renglon+z+2);
			}
		}
		cv::imshow("Ventana",res);
		res.release();
	}
}
