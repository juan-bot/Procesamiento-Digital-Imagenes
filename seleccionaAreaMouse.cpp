//selecciona por medio de un click el area de una imagen
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
static void detectaMouse(int event,int x,int y,int flags,void *param);
using namespace cv;
int ban=0,aux[2]={0};
int main(int argc, char** argv){
	int i, j;
	if(argc!=2){
		printf("Pasar una imagen como parametro");
		return -1;
	}
  Mat A = imread(argv[1]);
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
	imshow("Original",R);
  setMouseCallback("Original",detectaMouse,&R);
	int tecla;
	while(true){
		tecla=cv::waitKey(0);
		if(tecla==27) break;
	}
	return 0;
}
static void detectaMouse(int event,int x,int y,int flags,void *param){
	Mat res=*(Mat *)param;
  Scalar fondo(127,127,127);
  Mat B=res.clone();
  //Mat B ( res.rows,res.cols,CV_8UC3,fondo);
  int i, j;
  Scalar color(0,0,0);
  if(event ==EVENT_LBUTTONDOWN){
    aux[0]=x;
    aux[1]=y;
    if(ban ==0)
      ban=1;
    imshow("Original",B);
	}
  else if ( event == EVENT_MOUSEMOVE && ban==1){
    for(j=0;j<res.rows;j++){
      uchar *renglon=res.ptr<uchar>(j);
      uchar *renglonR=B.ptr<uchar>(j);
      for(int k=0,i=0;i<res.cols*3;i+=3,k++){
        if(j>=aux[1] && j<=y && x >= k && aux[0] <= k){
          *(renglonR+i+0)= *(renglon+i+0);
          *(renglonR+i+1)= *(renglon+i+1);
          *(renglonR+i+2)= *(renglon+i+2);
        }
        else{
          *(renglonR+i+0)= (0.07* *(renglon+i+0)) + (0.716* *(renglon+i+1)) + (0.21* *(renglon+i+2));
          *(renglonR+i+1)= *(renglonR+i+0);
          *(renglonR+i+2)=*(renglonR+i+1);
        }
      }
    }
    imshow("Original",B);
  }
  else if  ( event == EVENT_LBUTTONUP ){
    ban=0;
  }
}
