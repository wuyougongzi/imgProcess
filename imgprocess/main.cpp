#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QObject>
#include <QtGui>
#include <QSplashScreen>
#include <QPixmap>
#include <QThread>      //没有对应的sleep函数可以用
#include <QTime>

#include "mainwindow.h"
#include "startanimal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //程序启动画面
/*    QSplashScreen* splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/image/cat.jpg"));
    splash->show();

    Qt::Alignment center = Qt::AlignHCenter;
//    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up to the main window..."),
                       center,
                       Qt::white);


    QTime time;
    time.start();
    while(time.elapsed() < 1000 * 5);

    splash->showMessage(QObject::tr("loading modules..."),
                        center,
                        Qt::white);

  //  loadModules();
    //for test
 //   unsigned long secs = 5;
 //   QThread::sleep(secs);
//    QTime time;
    time.start();
    while(time.elapsed() < 1000 * 5);

    splash->showMessage(QObject::tr("loading modules finished"),
                        center,
                        Qt::white);

 //   QTime time;
    time.start();
    while(time.elapsed() < 1000 * 5);
  // establishConnections();
    //
  */
    StartAnimal* startAnimal = new StartAnimal();
    startAnimal->startAnimal();
    MainWindow w;
    w.show();

    startAnimal->finishAnimal(w);
//    splash->finish(&w);
//    delete splash;
    return a.exec();
}
