//de una imagen a color dividirla en 3 R G B
#include <stdio.h>
#include <opencv2/opencv.hpp>
float verificalimit(float n);
int main(int argc, char** argv){
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
	cv:: Scalar fondo(127,127,127);

	cv::Mat A =cv::imread(argv[1]);
	cv::Mat B ( A.rows,A.cols,CV_8UC3,fondo);
	//cv::Mat B =A.clone();
	printf("Columnas: %d, Filas: %d, Canales: %d\n", A.cols, A.rows, A.channels());

	cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
//B G R
	float r1,r2,g1,g2,b1,b2,dr,dg,db,r,g,b,aux1,aux2,aux3;
	r1=202/255.0;
	g2=6/255.0;
	b1=70/255.0;

	r2=194/255.0;
	g1=202/255.0;
	b2=6/255.0;

	dr=(r2-r1)/A.cols;
	dg=(g2-g1)/A.cols;
	db=(b2-b1)/A.cols;

	aux1=r1;
	aux2=g1;
	aux3=b1;
	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglonR=B.ptr<uchar>(j);

		for(i=0;i<A.cols*3;i+=3){
			b1=verificalimit(b1);
			g1=verificalimit(g1);
			r1=verificalimit(r1);

			*(renglonR+i+0)=b1* *(renglon+i+0);
			*(renglonR+i+1)=g1* *(renglon+i+1);
			*(renglonR+i+2)=r1* *(renglon+i+2);

			r1=r1+dr;
			g1=g1+dg;
			b1=b1+db;
		}
		r1=aux1;
		g1=aux2;
		b1=aux3;

	}
	cv::imshow("Original",A);
	cv::imshow("Gradiente",B);
	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;

}
float verificalimit(float n){
	float x;
	if(n>255)
		return 255;
	else if(n<0)
		return 0;
	return n;
}
