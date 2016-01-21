#ifndef IMGPROCESSCENTERWIDGET_H
#define IMGPROCESSCENTERWIDGET_H

#include <QStackedWidget>

namespace Ui {
class ImgProcessCenterWidget;
}

enum CenterWidgetType
{
    CENTERWIDGETSHOWPICTURE = 0,
};

class ImgProcessCenterWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit ImgProcessCenterWidget(QWidget *parent = 0);
    ~ImgProcessCenterWidget();
    
public:
    void setCenterWidgetShowPicture(QString filePath = "");
    QPixmap getSavedPicture();

private:
    Ui::ImgProcessCenterWidget *ui;
};

#endif // IMGPROCESSCENTERWIDGET_H
