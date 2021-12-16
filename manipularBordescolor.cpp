// dando click en la imagen, muestra el color que selecciono en una barra
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
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
  int valor=0;//valor inicial de la barra
	cv::imshow("Ventana",R);
	createTrackbar("Bordes","Ventana",&valor,4,mifuncion2,&A);
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
	int i,j,renglones[4]={0},columna[4]={0},diagonal[4]={0},max[3]={0};
	if(valor==0)
		cv::imshow("Ventana",orig);
	if(valor==1 || valor ==2 || valor==3 || valor ==4){
		Mat res= Mat:: zeros(A.rows,A.cols,CV_8UC3);
		for(j=0;j<orig.rows;j++){
			uchar *renglon=orig.ptr<uchar>(j);
			uchar *renglon1=res.ptr<uchar>(j);
			uchar *renglon2=orig.ptr<uchar>(j+1);
			for(i=0;i<orig.cols*3;i+=3){
				//renglones
				renglones[0]=fabs((*(renglon+i+0))-(*(renglon2+i+0)));
				renglones[1]=fabs((*(renglon+i+1))-(*(renglon2+i+1)));
				renglones[2]=fabs((*(renglon+i+2))-(*(renglon2+i+2)));
				renglones[3]=renglones[0]+renglones[1]+renglones[2];
				//Columnas
				columna[0]=fabs((*(renglon+i))-(*(renglon+i+3)));
				columna[1]=fabs((*(renglon+i+1))-(*(renglon+i+4)));
				columna[2]=fabs((*(renglon+i+2))-(*(renglon+i+5)));
				columna[3]=columna[0]+columna[1]+columna[2];
				//diagonales
				diagonal[0]=fabs((*(renglon+i))-(*(renglon2+i+3)));
				diagonal[1]=fabs((*(renglon+i+1))-(*(renglon2+i+4)));
				diagonal[2]=fabs((*(renglon+i+2))-(*(renglon2+i+5)));
				diagonal[3]=diagonal[0]+diagonal[1]+diagonal[2];

				if(renglones[3] >= columna[3] && renglones[3] >= diagonal[3]){
					max[0]=renglones[0];
					max[1]=renglones[1];
					max[2]=renglones[2];
				}

				else {
					if(columna[3] > diagonal[3]){
						max[0]=columna[0];
						max[1]=columna[1];
						max[2]=columna[2];
					}
					else{
						max[0]=diagonal[0];
						max[1]=diagonal[1];
						max[2]=diagonal[2];
					}
				}
				if(valor==1){
					if(j<orig.rows-1){
						*(renglon1+i+0)= renglones[0];
						*(renglon1+i+1)= renglones[1];
						*(renglon1+i+2)= renglones[2];
					}
					else{
						*(renglon1+i+0)= 0;
						*(renglon1+i+1)= 0;
						*(renglon1+i+2)= 0;
					}

				}
				if(valor==2){

						*(renglon1+i+0)= columna[0];
						*(renglon1+i+1)= columna[1];
						*(renglon1+i+2)= columna[2];

				}
				//printf("[%d][%d]\n", j,i);
				if(valor==3){
						*(renglon1+i+0)= diagonal[0];
						*(renglon1+i+1)= diagonal[1];
						*(renglon1+i+2)= diagonal[2];


				}
				if(valor==4){

						*(renglon1+i+0)= max[0];
						*(renglon1+i+1)= max[1];
						*(renglon1+i+2)= max[2];

				}
			}
		}
		cv::imshow("Ventana",res);
		res.release();
	}
}
