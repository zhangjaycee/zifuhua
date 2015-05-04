#include<stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include<unistd.h>

//#define LIDU 20
using namespace cv;
using namespace std;
int LIDU=15;
//对图像指定的区域加马赛克
//方法是把目标区域划分成小块，把每个块的值都设成这个块的均值或中值

void addMaSaiKe(IplImage *src,CvRect rect,IplImage *dst,int W,int H);
void testMasaike(char *);

//hi im version 1.0
int main(int argc,char * argv[])
{
char name[30];
    //strncpy(name, "test.jpg",strlen("test.jpg"));
     if(argc==1){
                testMasaike("test.jpg");
    }else if(argc>1&&argc<3){
                testMasaike(argv[1]);
    }else if(argc<4){
        LIDU = atoi(argv[2]);
                testMasaike(argv[1]);
    } else{
        printf("argc error,try again!\n");
        exit(0);
    }
}
void testMasaike(char * name)
{
    printf("ok");
    IplImage *src=cvLoadImage(name,0);
    IplImage *src0=cvLoadImage(name);
    cvShowImage("Ma",src0);
    IplImage *dst=cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
    int	w,h;//这作为马赛克窗的尺寸
   w=(int)(LIDU*0.48);
   h=LIDU;
    int ww=src->width/w*w;
    int hh=src->height/h*h;
   CvRect rect=cvRect(0,0,ww,hh);//ROI的尺寸要是马赛克窗口的整数倍
   addMaSaiKe(src,rect,dst,w,h);
    cvNamedWindow("Ma",1);
 //   cvShowImage("Ma",src);
    cvWaitKey(0);
}
void addMaSaiKe(IplImage *src,CvRect rect,IplImage *dst,int W,int H)
{
    CvMat *model=cvCreateMat(H,W,CV_8U);
    IplImage *tmp=cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
    cvCopyImage(src,tmp);
    cvSetImageROI(tmp,rect);
    cvAddS(tmp,cvScalar(80),tmp);
    CvRect subRect;
    CvScalar avg=cvScalarAll(0);
    int count=0,outside=0;
    char ch;
    for(int i=0;i<rect.height;i=i+H)
    {//设置ROI之后，i=0;是ROI区域的第一个位置
        for(int j=0;j<rect.width;j=j+W)
        {
            subRect=cvRect(j,i,W,H);
            cvGetSubRect(tmp,model,subRect);
            avg=cvAvg(model);
                    //////////////////////
                    if(avg.val[0]<150){
                        avg.val[0]=0;
                        ch='@';
                    }else if(avg.val[0]<170){
                        avg.val[0]=155;
                        ch='#';
                    }else if(avg.val[0]<190){
                        avg.val[0]=200;
                        ch='*';
                    }else if(avg.val[0]<200){
                        avg.val[0]=200;
                        ch='+';
                    }else if(avg.val[0]<225){
                        avg.val[0]=230;
                        ch='.';
                    }else if(avg.val[0]<260){
                        avg.val[0]=255;
                        ch=' ';
                    }
                    printf("%c",ch);
                        /////////////////////
           // printf("%3.0lf ",avg.val[0]);
            for(int h=i;h<i+H&&h<rect.height;h++){
                for(int w=j;w<j+W&&w<rect.width;w++){
                    cvSet2D(tmp,h,w,avg);
                }
            }
        }
            //if(h%1==0)
                printf("\n");
    }
    cvResetImageROI(tmp);
    cvCopyImage(tmp,dst);
}
