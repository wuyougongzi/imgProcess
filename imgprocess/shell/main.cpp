#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QObject>
#include <QtGui>
#include <QSplashScreen>
#include <QPixmap>
#include <QThread>      //没有对应的sleep函数可以用
#include <QTime>

#include "ui/mainwindow.h"
#include "ui/startanimal.h"

#include <opencv.hpp>

//#include <QHash>
#include "utility/hash.h"
#include "utility/cvtools.h"

using namespace std;
using namespace cv;

//void OpenCvEnvironmentTest();

int startFromMainWindow(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//StartAnimal* startAnimal = new StartAnimal();
	//startAnimal->startAnimal();
	MainWindow w;
	w.show();
	//startAnimal->finishAnimal(w);
	return a.exec();
}

//直接比较两个的两个图片最简单的方式
//逐个比较像素点和像素点的rgb值,rgb值暂时没有写 //通过仿函数的形式支持,自定义实现像素点和rgb值的实现

//将函数的比较方式抽离
class CvScalarCompare
{
public:
	bool operator()(CvScalar v1, CvScalar v2)
	{
		return v1.val[0] == v2.val[0];	//只比较第一种颜色值
	}
};


bool compareCompleteImg(IplImage *pImage1, IplImage *pImage2, CvScalarCompare cmp)
{
	if(pImage1 == NULL || pImage2 == NULL)
	{
		//两个都为null也返回错误
		assert("image null");
		return false;
	}
	//CvSize size = pImage1->imageSize();
	//for()
	if(pImage1->width != pImage2->width || pImage1->height != pImage2->height)
	{
		return false;
	}

	Mat imgMat1(pImage1);
	Mat imgMat2(pImage2);
	//imgMat1.at()
	double b1;
	double b2;
	//数组越界，这个图像位置的坐标
	//和实际window的坐标的x和y是相反的
	//b1 = cvGet2D(pImage1, 170, 280).val[0];
	CvScalar v1;
	CvScalar v2;
	for(int i = 0; i < pImage1->width; ++i)
	{
		for(int j = 0; j < pImage1->height; ++j)
		{
			//b1 = cvGet2D(pImage1, j, i).val[0];
			//b2 = cvGet2D(pImage2, j, i).val[0];
			//cout << i  <<"  " << j << "\n";
			//if(abs(b1 - b2) < 0.00001)
			v1 = cvGet2D(pImage1, j, i);
			v2 = cvGet2D(pImage2, j, i);
			if(cmp(v1, v2))
			{
				//表示b1 == b2
				continue;
			}
			else
			{
				return false;	//图片该像素点不相同，不是同一张图片
			}
			//多通道
			//
			//
			//cvGet2D(pImage1, i, j).val[1];
			//cvGet2D(pImage1, i, j).val[1];
		}
	}
	return true;
}

void startFromCvImg()
{
	char* imageName = "C:\\Users\\chongge\\Desktop\\testimg\\toolbox.jpg";
	char* imageName1 = "C:\\Users\\chongge\\Desktop\\testimg\\toolbox_1.jpg";
	char* imageName2 = "C:\\Users\\chongge\\Desktop\\testimg\\3.jpg";

	IplImage *pImg1 = NULL;
	pImg1 = cvLoadImage(imageName, 0);

	IplImage *pImg2 = NULL;
	pImg2 = cvLoadImage(imageName1, 0);

	IplImage *pImg3 = NULL;
	pImg3 = cvLoadImage(imageName2, 0);

	CvScalarCompare cmp;
	bool bSame = compareCompleteImg(pImg1, pImg2, cmp);
	cout << bSame << "\n";
	cout <<  compareCompleteImg(pImg1, pImg3, cmp) << "\n";

	//1 切割9个区域
	/*文字区: 125,0, 120 30
		图大小好像是68 * 68的 剩下的是边框
	*/
	//先切一个下来
	//文字的位置
	CvRect txtRect;
	txtRect.x = 125;
	txtRect.y = 0;
	txtRect.width = 120;
	txtRect.height = 30;
	IplImage* pImageText = getImageZone(imageName,txtRect);

	//第一张图的位置
	CvRect pImg1Rect;
	pImg1Rect.x = 0;
	pImg1Rect.y = 30;
	pImg1Rect.width = 70;
	pImg1Rect.height = 80;

	IplImage* pImage1 = getImageZone(imageName,pImg1Rect);

#ifdef _DEBUG
	cvNamedWindow("Image", 1);
	cvShowImage("Image", pImageText);
	
	cvNamedWindow("Image2", 2);
	cvShowImage("Image2", pImage1);

	cvWaitKey(0);
	cvDestroyWindow("Image");
	cvReleaseImage(&pImageText);
#endif // _DEBUG

}

int main(int argc, char *argv[])
{
   
	//OpenCvEnvironmentTest();

	//getchar();
	//system("puase");
	startFromCvImg();
}

//
/*
下面的函数是用于测试opencv环境的，不允许其他地方调用
*/
//
void OpenCvEnvironmentTest()
{
	const char* imageName = "C:\\Users\\chongge\\Desktop\\testimg\\toolbox.jpg";
	Mat img =  imread(imageName);
	
	if(img.empty())
	{
		fprintf(stderr, "Can not load image%s\n", imageName);
		return ;
	}
	//	namedWindow("image", 1);
	imshow("image", img);
	
	waitKey();
}
