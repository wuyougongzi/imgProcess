#include "showpicture.h"
#include "ui_showpicture.h"
#include <QMessageBox>
#include <QGraphicsScene>

ShowPicture::ShowPicture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showPicture)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(":/image/cat.jpg"));
    ui->graphicsView->setScene(scene);

    connect(ui->btnenlarge,
            SIGNAL(clicked()),
            this,
            SLOT(onBtnEnLargeClicked()));

    connect(ui->btnzoom,
            SIGNAL(clicked()),
            this,
            SLOT(onBtnZoomClicked()));

    connect(ui->btntransparrent,
            SIGNAL(clicked()),
            this,
            SLOT(onBtnTransprentClicked()));

    connect(ui->btncut,
            SIGNAL(clicked()),
            this,
            SLOT(onBtnCutClicked()));

}

void ShowPicture::onBtnEnLargeClicked()
{
    //todo: 图片放大算法

}

void ShowPicture::onBtnZoomClicked()
{

}

void ShowPicture::onBtnTransprentClicked()
{

}

void ShowPicture::onBtnCutClicked()
{

}
