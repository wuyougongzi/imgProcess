#include "showpicture.h"
#include "ui_showpicture.h"
#include <QMessageBox>
#include "screenshot/screenimg.h"

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

    //todo 绘图区就是imgprocessarea的大小，绘图的事件都在里面操作，
    //需要区分位置，好像设置了border-image失效。需要区分出来。
}

void ShowPicture::init()
{
    //ui->labelshowpicture->setPixmap(m_originalPixmap);
    //ui->widgetshowpicture->setp
    //ui->widgetshowpicture->setAutoFillBackground(true);
    //ui->widgetshowpicture->setStyleSheet("border-image:url(:/showpicture/image/showpicture/greenvein.png)");
    m_processedPixmap = m_originalPixmap;
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
    ScreenShotImgDlg *pSceenImgDlg = new ScreenShotImgDlg;
    pSceenImgDlg->exec();
}

void ShowPicture::setOriginalPixmap(const QPixmap& pixmap)
{
    m_originalPixmap = pixmap;
}

QPixmap ShowPicture::getProcessedPixmap()
{
    return m_processedPixmap;
}

void ShowPicture::onBtnEclipsClicked()
{
    ui->imgprocessarea->setShapeType(SHAPEECLIPSE);
}

void ShowPicture::onBtnLineClicked()
{
    ui->imgprocessarea->setShapeType(SHAPELINE);
}

void ShowPicture::onBtnPixmapClicked()
{
    ui->imgprocessarea->setShapeType(SHAPEPIXMAP);
}

void ShowPicture::onBtnPloyLineClicked()
{
    //todo:
}

void ShowPicture::onBtnPointClicked()
{
    ui->imgprocessarea->setShapeType(SHAPEPOINTS);
}

void ShowPicture::onBtnRectangle()
{
    //todo:
}
