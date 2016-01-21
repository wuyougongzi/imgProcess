#include "imgprocesscenterwidget.h"
#include "ui_imgprocesscenterwidget.h"

ImgProcessCenterWidget::ImgProcessCenterWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::ImgProcessCenterWidget)
{
    ui->setupUi(this);
}

ImgProcessCenterWidget::~ImgProcessCenterWidget()
{
    delete ui;
}

void ImgProcessCenterWidget::setCenterWidgetShowPicture(QString filePath/* = ""*/)
{
    this->setCurrentIndex(CENTERWIDGETSHOWPICTURE);
    QPixmap pixmap(filePath);
    ui->showpicture->setOriginalPixmap(pixmap);
    ui->showpicture->init();
}

QPixmap ImgProcessCenterWidget::getSavedPicture()
{
    return ui->showpicture->getProcessedPixmap();
}
