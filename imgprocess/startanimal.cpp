#include "startanimal.h"
#include <QPixmap>
#include <QTime>

StartAnimal::StartAnimal()
{

}

void StartAnimal::startAnimal()
{
    this->setPixmap(QPixmap(":/image/cat.jpg"));
    this->show();

    this->showMessage("wecomle to imgprocess imgprocess starting", Qt::AlignCenter, Qt::white);
    QTime time;
    time.start();
    while(time.elapsed() < 1000 * 1);

    this->showMessage("imgprocess ending", Qt::AlignCenter, Qt::white);

    time.start();
    while(time.elapsed() < 1000 * 1);
}

void StartAnimal::finishAnimal(QMainWindow &mainwindow)
{
    this->finish(&mainwindow);
}
