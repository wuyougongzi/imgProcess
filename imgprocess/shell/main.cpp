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
