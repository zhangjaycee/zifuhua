
#include<stdio.h>
#include<stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void process(Mat &img,int L);
void printChar(int val);

int main(int argc,char * argv[])
{
    Mat src,gray;
    int L;
    char key;
    int rate=20;
   VideoCapture capture("test.MOV");
    //Init
    if(argc==1){
        printf("load test.jpg and L=15 automatically\n");
        capture.open("test.MOV");
        //src=imread("test.jpg");
        L=15;
        waitKey(0);
    }else if(argc==2){
        //argv[1] is name
        //src=imread(argv[1]);
        if(strcmp("0",argv[1]))
            capture.open(argv[1]);
        else
            capture.open(0);
        L= 15;
    }else if(argc==3){
            capture.open(argv[1]);
        //src=imread(argv[1]);
        L = atoi(argv[2]);
    }else{
        printf("argc error,try again!\n");
        exit(1);
    }
 /*   if(src.empty()){
        printf("src is empty!\n");
        exit(1);
    }*/
    //process
    while(capture.read(src)){
        system("clear");
        cvtColor(src ,gray , CV_RGB2GRAY);
        process(gray,L);
        //imshow("src",src);
        imshow("gray",gray);
        key=waitKey(1000/rate);
        if(key==27){
            break;
        }
    }
   // waitKey(0);
}

void process(Mat &img,int L)
{
    //Init lengths
    int height=img.rows;
    int width=img.cols;
    int w=L;
    int h=(int)L*2.5;
    int sum=0;

    unsigned char * data=(unsigned char *)img.data;
    for(int i=0;i<height-h;i+=h){
        for(int j=0;j<width-w;j+=w){
            sum=0;
            for(int ih=0;ih<h;ih++){
                for(int iw=0;iw<w;iw++){
                    sum+=data[(i+ih)*width+j+iw];
                }
            }
            sum=(int)sum/(w*h);
            printChar(sum);
        }
        printf("\n");
    }
}
void printChar(int val)
{
    char ch;
    if(val<50){
        ch='@';
    }else if(val<90){
        ch='#';
    }else if(val<120){
        ch='*';
    }else if(val<155){
        ch='+';
    }else if(val<170){
        ch='.';
    }else if(val<260){
        ch=' ';
    }
    printf("%c",ch);
}
