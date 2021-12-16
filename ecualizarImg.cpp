//de una imagen a color dividirla en 3 R G B
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
void mostrarHistograma(int histograma[],int alto);

int main(int argc, char** argv){
	int histograma[256]={0},HA[256]={0},histograma2[256]={0};
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
	cv:: Scalar fondo(127,127,127);
  cv:: Scalar fondo2(255,255,255);
	cv::Mat A = cv::imread(argv[1]);
	int alto,ancho;
	alto=800;
	ancho=800;
	cv::Mat B ( A.rows,A.cols,CV_8UC3,fondo);
	Mat C ( A.rows,A.cols,CV_8UC1,fondo);
	Mat Histograma ( alto,ancho,CV_8UC3,fondo2);
	printf("Columnas: %d, Filas: %d, Canales: %d\n", A.cols, A.rows, A.channels());
	cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
//B G R
  int aux=0,max=0;
	for(j=0;j<A.rows;j++){

		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglon1=B.ptr<uchar>(j);
		for(i=0;i<A.cols*3;i+=3){
			*(renglon1+i+2)=*(renglon1+i+1)= *(renglon1+i+0)= (0.07* *(renglon+i+0)) + (0.716* *(renglon+i+1)) + (0.21* *(renglon+i+2));
			aux=*(renglon1+i+2);
			histograma[aux]+=1;
		}
	}
	HA[0]=histograma[0];
	for(i=1;i<=255;i++){
		HA[i]=HA[i-1]+histograma[i];
	}


	for(j=0;j<B.rows;j++){
		uchar *renglon1=B.ptr<uchar>(j);
		uchar *renglon2=C.ptr<uchar>(j);
		for(i=0;i<B.cols;i++){
			aux=*(renglon2+i)=(255*(HA[i]-HA[0]))/((B.rows*B.cols)-HA[0]);
			histograma2[aux]+=1;
		}
	}
	mostrarHistograma(histograma,alto);
	imshow("Original",A);
	imshow("Grises",B);
	imshow("Mejorada",C);
	//cv::imshow("Histograma",Histograma);
	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;
}
void mostrarHistograma(int histograma[],int alto){
	int i,j,aux,max=0;
	cv:: Scalar fondo2(255,255,255);
	Mat Histograma ( alto,alto,CV_8UC1,fondo2);
	for(i=0;i<=255;i++){
		aux=histograma[i];
		printf("%d\n",aux);
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
}
