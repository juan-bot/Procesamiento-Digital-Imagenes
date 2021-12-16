//de una imagen a color dividirla en 3 R G B
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
int main(int argc, char** argv){
	int histograma[256]={0},rojos[256]={0},azules[256]={0},verdes[256]={0};
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
  cv:: Scalar fondo(255,255,255);
	cv::Mat A = cv::imread(argv[1]);
	int alto,ancho;
	alto=800;
	ancho=1570;
	Mat Histograma ( alto,ancho,CV_8UC3,fondo);
	cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
//B G R
  int aux=0,max=0;
	/*for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		for(i=0;i<A.cols*3;i+=3){
			*(renglon+i+0)+=60;
			*(renglon+i+2)+=60;
			*(renglon+i+3)+=60;
		}
	}*/
	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		for(i=0;i<A.cols*3;i+=3){
			azules[*(renglon+i+0)]+=1;
			verdes[*(renglon+i+1)]+=1;
			rojos[*(renglon+i+2)]+=1;
		}
	}
	int r,g,b;
	for(i=0;i<=255;i++){
		r=rojos[i];
		g=verdes[i];
		b=azules[i];
		if(r>g && r>b)
			aux=r;
		if(g>r && g>b)
			aux=g;
		if(b>r && b>g)
			aux=b;
		if(aux>max)
			max=aux;
		aux=0;
	}
	printf("maximo %d\n",max);
	Scalar rojo(0,0,255);
	Scalar verde(0,255,0);
	Scalar azul(255,0,0);
	int cont=15;
	aux=0;
	for(i=0;i<=255;i++){
		//Rect rectangulo(cont,20,2,fabs(histograma[i]-alto));
		aux=rint((rojos[i]*(alto-20))/max);
    Rect rectanguloR(cont,(alto-10)-aux,2,aux);
		rectangle(Histograma, rectanguloR, rojo,FILLED);

		aux=rint((verdes[i]*(alto-20))/max);
		Rect rectanguloV(cont+2,(alto-10)-aux,2,aux);
		rectangle(Histograma, rectanguloV, verde,FILLED);

		aux=rint((azules[i]*(alto-20))/max);
		Rect rectanguloA(cont+4,(alto-10)-aux,2,aux);
		rectangle(Histograma, rectanguloA, azul,FILLED);

		cont+=6;
	}

	cv::imshow("Original",A);
	cv::imshow("Histograma de colores",Histograma);
	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;

}
