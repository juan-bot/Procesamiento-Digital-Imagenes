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
	int histograma[256]={0};
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
	Scalar fondo(127,127,127);
	Scalar fondo2(255,255,255);
	A = cv::imread(argv[1],0);
	int alto,ancho;
	alto=800;
	ancho=800;
	cv::Mat Histograma ( 800,800,CV_8UC1,fondo2);
	cv::namedWindow("Original",WINDOW_AUTOSIZE);
	int aux=0,max=0,min=0,aux2=0;
	for(j=0;j<A.rows;j++){
		uchar *renglon1=A.ptr<uchar>(j);
		for(i=0;i<A.cols;i++){
			aux=*(renglon1+i);
			histograma[aux]+=1;
		}
	}
	for(int k=255,i=0;i<=255;i++,k--){
		if(histograma[i]!=0 && aux==0){
			min=i;
			aux=1;
		}

		if(histograma[k]!=0 && aux2==0){
			max=k;
			aux2=1;

		}
	}
	printf("%d %d\n",min,max);

	/*
	Scalar colorRectangle1(0,0,0);
	int cont=15;
	aux=0;
	for(i=0;i<=255;i++){
		aux=rint((histograma[i]*(alto-20))/max);
    Rect rectangulo(cont,(alto-10)-aux,2,aux);
		rectangle(Histograma, rectangulo, colorRectangle1,FILLED);
		cont+=3;
	}
  int valor=0;//valor inicial de la barra
	imshow("Nuevo",B);
	imshow("Original",A);
	imshow("Histograma",Histograma);
*/
  cv::imshow("Original",A);

 createTrackbar("barra","Original",&min,5,mifuncion,&A);

  int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;
}
static void mifuncion(int valor,void *params){
	//cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
	cv::Mat orig=*(Mat *)params;
	cv::Mat B =orig.clone();
  Scalar fondo2(255,255,255);
  cv::Mat Histograma ( 800,800,CV_8UC1,fondo2);
  int i, j;
  int alto,ancho;
  int aux=0,max=0,min=0,aux2=0;
  alto=800;
	ancho=800;
  int histograma[256]={0};
	for(j=0;j<A.rows;j++){
		uchar *renglon=orig.ptr<uchar>(j);
		uchar *renglonB=B.ptr<uchar>(j);
		for(i=0;i<A.cols;i++){
			*(renglonB+i)=*(renglon+i)+valor;
      aux=*(renglonB+i);
			histograma[aux]+=1;
		}
	}
	for(i=0;i<=255;i++){
		aux=histograma[i];
		if(max < aux)
			max=aux;
	}
  Scalar colorRectangle1(0,0,0);
	int cont=15;
	aux=0;
	for(i=0;i<=255;i++){
		aux=rint((histograma[i]*(alto-20))/max);
    Rect rectangulo(cont,(alto-10)-aux,2,aux);
		rectangle(Histograma, rectangulo, colorRectangle1,FILLED);
		cont+=3;
	}

	imshow("Histograma",Histograma);
 cv::imshow("Original",B);
}
