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
    ~ShowPicture();
signals:

public:
    void init();
    void setOriginalPixmap(const QPixmap& pixmap);
    QPixmap getProcessedPixmap();

// protected:
//     virtual void mousePressEvent(QMouseEvent *)         override;
//     virtual void mouseReleaseEvent(QMouseEvent *)       override;
//     virtual void mouseMoveEvent(QMouseEvent *)          override;
//     
//     virtual void paintEvent(QPaintEvent *)              override;
    
private slots:
    void onBtnColorSettingClicked();
    void onBtnEnLargeClicked();
    void onBtnZoomClicked();
    void onBtnCutClicked();
    void onBtnTransprentClicked();
    void onBtnEclipsClicked();
    void onBtnLineClicked();
    void onBtnPixmapClicked();
    void onBtnPloyLineClicked();
    void onBtnPointClicked();
    void onBtnRectangleClicked();

private:
   Ui::showPicture  *ui;
   QPixmap          m_originalPixmap;       //ʼ�ձ���ԭͼƬ
   QPixmap          m_processedPixmap;      //����������ͼƬ
 
};

#endif // SHOWPICURE_H
