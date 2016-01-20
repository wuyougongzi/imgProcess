#ifndef SHOWPICURE_H
#define SHOWPICURE_H

#include <QWidget>

namespace Ui {
class showPicture;
}

class ShowPicture : public QWidget
{
    Q_OBJECT
public:
    explicit ShowPicture(QWidget *parent = 0);

signals:

private slots:
    void onBtnEnLargeClicked();
    void onBtnZoomClicked();
    void onBtnCutClicked();
    void onBtnTransprentClicked();
private:
   Ui::showPicture *ui;
};

#endif // SHOWPICURE_H
