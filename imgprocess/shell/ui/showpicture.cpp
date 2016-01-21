#include "showpicture.h"
#include "ui_showpicture.h"
#include <QMessageBox>
#include <QGraphicsScene>

ShowPicture::ShowPicture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showPicture)
{
    ui->setupUi(this);

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

void ShowPicture::init()
{
    ui->labelshowpicture->setPixmap(m_originalPixmap);
    m_processedPixmap = m_originalPixmap;
}

void ShowPicture::onBtnEnLargeClicked()
{
    //todo: 图片放大算法
    //ui->showpicwidget->
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

void ShowPicture::setOriginalPixmap(const QPixmap& pixmap)
{
    m_originalPixmap = pixmap;
}

QPixmap ShowPicture::getProcessedPixmap()
{
    return m_processedPixmap;
}

