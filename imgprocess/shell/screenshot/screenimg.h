#ifndef SCREENIMG_H
#define SCREENIMG_H

#include "screenjudge.h"
#include <QDialog>
#include <QPixmap>
#include <QScreen>
#include <QPalette>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QKeyEvent>
#include <QFont>
#include <QMenu>
#include <QString>
#include <QFileDialog>
#include <QToolButton>

//��ǰ���Ƶ�����
enum DrawType
{
    DRAWTYPENONE = -1,
    DRAWTYPERECTANGLE,
    DRAWTYPEELLIPSE,
    DRAWTYPEARROW,
    DRAWTYPETEXT,
};

class ScreenShotImgDlg : public QDialog
{
    Q_OBJECT
    
public:
    ScreenShotImgDlg(QDialog *parent = 0);
    virtual ~ScreenShotImgDlg();

protected:
    virtual void paintEvent(QPaintEvent *)                  override;
    virtual void mousePressEvent(QMouseEvent *event)        override;
    virtual void mouseMoveEvent(QMouseEvent *event)         override;
    virtual void mouseReleaseEvent(QMouseEvent *event)      override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *)       override;
    virtual void keyPressEvent(QKeyEvent *event)            override;

private slots:
    void onBtnDrawRectangle();
    void onBtnSaveClicked();
    void onBtnSureToClipboardClicked();
    void onBtnCancle();

signals:
        void onScreenImgClose();
        void onSaveSucessed(const QString& strFilePath);

private:
    //�ദ��
    QSharedPointer<ScreenJudge> m_pScreenJudge;

    //��Ļ����
    int             m_iWidth;
    int             m_iHeight;
    QPixmap         m_fullScreenPix;
    QImage          m_fullScreenFogImg;
    QScreen         *m_pScreen;
    QPalette        m_palette;

    //draw��
    bool             m_bIsdrawing;
    QPixmap          m_drawPix;
    QRect            m_drawRect;

    //zoom��
    bool            m_bIszooming;
    QPoint          m_zoomPoint;
    QPixmap         m_pixMap;
    QRect           m_zoomRect;
    QRect           m_infoFirstRect;
    QRect           m_infoSecondRect;
    QRect           m_infoThirdRect;

    //drag��
    bool            m_bIsdraging;
    bool            m_bFirst;
    QPoint          m_dragPoint;
    QPoint          m_movePoint;
    DragJudge       m_dragJudge;

    //������ ����
    QToolButton     m_pBtnRectangle;
    QToolButton     m_pBtnSave;
    QToolButton     m_pBtnSure;
    QToolButton     m_pBtnCancle;

    //��ǰѡ�л�������
    bool            m_bIsSelectDrawShape;    //��־��ǰ�Ƿ���ѡ��ĳ����״�������϶���Ϊ
    DrawType        m_CurrentDrawType;
    QPoint          m_ptMousePress;
    QPoint          m_ptCurrentPos;

};

#endif // SCREENIMG_H
