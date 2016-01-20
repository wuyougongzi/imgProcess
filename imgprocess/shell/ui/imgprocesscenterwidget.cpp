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
