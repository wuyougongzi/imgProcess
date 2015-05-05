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

    this->showMessage("start test", Qt::AlignCenter, Qt::white);
    QTime time;
    time.start();
    while(time.elapsed() < 1000 * 5);

    this->showMessage("start End", Qt::AlignCenter, Qt::white);

    time.start();
    while(time.elapsed() < 1000 * 5);
}

void StartAnimal::finishAnimal(QMainWindow &mainwindow)
{
    this->finish(&mainwindow);
}
