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

public:
    void init();
    void setOriginalPixmap(const QPixmap& pixmap);
    QPixmap getProcessedPixmap();

private slots:
    void onBtnEnLargeClicked();
    void onBtnZoomClicked();
    void onBtnCutClicked();
    void onBtnTransprentClicked();
private:
   Ui::showPicture  *ui;
   QPixmap          m_originalPixmap;       //始终保留原图片
   QPixmap          m_processedPixmap;      //处理后的最新图片
};

#endif // SHOWPICURE_H
