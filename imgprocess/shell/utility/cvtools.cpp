
#include "cvtools.h"
#include "highgui.h"

IplImage  * getImageZone(char *filename,CvRect rect)
{
	IplImage *pImg=NULL;

	// IplImage *ptemp=NULL;
	// IplImage *testImg=NULL;
	//cvLoadImage ��0��ʾ��ȡ�Ҷ�ֵ��1��ʾ��ȡ��ɫֵ���������Ҫ��ȡ�ɽӿ�
	pImg=cvLoadImage(filename,0);
	int height=rect.height;
	int width =rect.width;
	// int x   =rect.x;
	// int y   =rect.y;
	CvSize size;
	// size=cvGetSize(pImg);
	size.height=height;
	size.width =width;
	IplImage *testImg=cvCreateImage(size,pImg->depth,pImg->nChannels);

	cvSetImageROI(pImg,rect);
	cvCopy(pImg,testImg,0);

	// IplImage *ptemp=cvCreateImage(size,IPL_DEPTH_8U,1);
	// cvCvtColor(testImg,ptemp,CV_BGR2GRAY);
	//  cvCvtColor(ԭʼͼ��,Ŀ��ͼ��,CV_BGR2GRAY); 
	// cvCvtColor(ptemp1,ptemp2,CV_BGR2GRAY);
	// cvNamedWindow("ptemp",1);
	// cvShowImage("ptemp",ptemp);


	// cvCanny(ptemp,pCannyImg, 35 , 120 , 3 ); 
	// cvResetImageROI(pImg); 
	// printf("pImg height:%d\n",(int)pImg->height);
	// printf("pImg width :%d\n",(int)pImg->width);

	// printf("pImg(height width) :%d %d\n",
	// (int)pImg->height,(int)pImg->width); 
	// printf("testImg(height width) :%d %d\n",
	// (int)testImg->height,(int)testImg->width); 
	// cvNamedWindow("pImg",1);
	return testImg;
}