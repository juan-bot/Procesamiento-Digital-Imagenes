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
	Mat R= Mat:: zeros(A.rows+60,A.cols,CV_8UC3);

	boton =Rect(0,0,A.cols,50);
	rectangle(R,boton,fondo,FILLED);

	for(j=0;j<A.rows;j++){
		uchar *renglon=A.ptr<uchar>(j);
		uchar *renglonR=R.ptr<uchar>(j+60);
		for(i=0;i<A.cols*3;i+=3){
			*(renglonR+i+0)=*(renglon+i+0);
			*(renglonR+i+1)=*(renglon+i+1);
			*(renglonR+i+2)=*(renglon+i+2);
		}
	}

	imshow("Ventana",R);
	setMouseCallback("Ventana",mifuncion,&R);
  int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;
}
static void mifuncion(int event,int x,int y,int flags,void *param){
	Mat res=*(Mat *)param;
	Mat R =Mat:: zeros(res.rows-60,res.cols,CV_8UC3);
	//Mat R=res.clone();
	int i,j;
	int v1,v2,v3;
	if(event ==EVENT_LBUTTONDOWN){
		if(y>60){
			uchar *renglonx=res.ptr<uchar>(y);
			v1=*(renglonx+x*3);
			v2=*(renglonx+x*3+1);
			v3=*(renglonx+x*3+2);
			printf("[%d %d %d]\n",v1,v2,v3);

			Scalar actual(v1,v2,v3);
			rectangle(res,boton,actual,FILLED);
			for(j=0;j<R.rows;j++){
				uchar *renglon=res.ptr<uchar>(j+60);
				uchar *renglonR=R.ptr<uchar>(j);
				for(i=0;i<R.cols*3;i+=3){
					//printf("%lf, ", (*(renglon+i) * (v1/255.0)));
					*(renglonR+i) = (*(renglon+i) * (v1/255.0));
					//printf("%d, ", *(renglonR+i) );
					*(renglonR+i+1) = (*(renglon+i+1) * (v2/255.0));
					*(renglonR+i+2) =  (*(renglon+i+2) * (v3/255.0));
				}
			}
			imshow("Ventana",res);
			imshow("Resultante",R);
			//R.release();
		}
	}

}
