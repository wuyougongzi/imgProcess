#ifndef STARTANIMAL_H
#define STARTANIMAL_H

#include <QSplashScreen>
#include <QMainWindow>

class StartAnimal : public QSplashScreen
{

public:
    explicit StartAnimal();

public:
    void startAnimal();
    void finishAnimal(QMainWindow& mainwindow);

signals:

public slots:

};

#endif // STARTANIMAL_H
