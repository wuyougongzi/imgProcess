#ifndef IMGPROCESSCENTERWIDGET_H
#define IMGPROCESSCENTERWIDGET_H

#include <QStackedWidget>

namespace Ui {
class ImgProcessCenterWidget;
}

class ImgProcessCenterWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit ImgProcessCenterWidget(QWidget *parent = 0);
    ~ImgProcessCenterWidget();

private:
    Ui::ImgProcessCenterWidget *ui;
};

#endif // IMGPROCESSCENTERWIDGET_H
