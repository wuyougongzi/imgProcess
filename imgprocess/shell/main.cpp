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

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartAnimal* startAnimal = new StartAnimal();
    startAnimal->startAnimal();
    MainWindow w;
    w.show();

    startAnimal->finishAnimal(w);
    return a.exec();

}

//
/*
下面的函数是用于测试opencv环境的，不允许其他地方调用
*/
//
void OpenCvEnvironmentTest()
{
	const char* imageName = "C:\\Users\\chongge\\Documents\\Visual Studio 2010\\Projects\\cvtest\\cat.jpg";
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
