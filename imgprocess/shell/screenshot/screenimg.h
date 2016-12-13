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
#include <QStack>
#include <QTextEdit>

//��ǰ���Ƶ�����
enum DrawShapeType
{
    DRAWTYPENONE = 0,
    DRAWTYPERECTANGLE,
    DRAWTYPEELLIPSE,
    DRAWTYPEARROW,
    DRAWTYPETEXT,
	DRAWTYPEMOSAIC,
};

struct ShapeInfo
{
	DrawShapeType	type;
	QPoint		ptLeftTop;
	QPoint		ptRightBottom;
	QPoint		ptCenter;	//��Բ�εĿ�����Ҫ,��֪���ܲ�������
	QColor		brushColor;	//�����ɫ����֪���ܲ����õ�
	QColor		penColor;	//�߿���ɫ
	int			penWeight;	//�߿��ϸ
	ShapeInfo()
	{
		type = DRAWTYPENONE;
		penWeight = 1;
		penColor.setRgb(255, 0, 0);
		brushColor.setRgb(255, 0, 0);
	}
};

//paint ״̬��
enum DrawStatus
{
	DrawScreenNone = 0,
	DrawScreenArea,			//������Ҫ��׽����Ļλ��
	DrawScreenDragPos,		//�϶�����ʱ����
	DrawScreenDragSize,		//�϶���Сʱ����
	DrawScreenShape,		//��Ҫ�����������״
};


class ScreenToolBar;

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
	void onBtnText();
	void onBtnUndu();
	void onBtnArrow();
	void onBtnMosaic();

signals:
    void onScreenImgClose();
    void onSaveSucessed(const QString& strFilePath);
	
private:
	QPixmap getDrawAreaPixmap();
	void drawScreenArea(const QRect& rect);
	void drawRectDragPoint(const QRect& rect);			//������Ļ������϶��ĵ�
	void drawZoomArea(const QPoint& pt);				//���ƷŴ��
	QPoint getLeftTopPoint(const QPoint &pt1, const QPoint &pt2);
	QPoint getRightBottomPoint(const QPoint &pt1, const QPoint &pt2);
	QRect getDrawRect(const QPoint &pt1, const QPoint &pt2);
	void showToolBar(const QPoint &drawAreaRightBottomPt);
	void drawShapeArrow(QPainter *painter, const QPoint &ptStart, const QPoint &ptEnd);
	void drawTextAreaRect(QPainter *painter);
	void drawExitingShapeAll(QPainter *painter);
	void drawMosaic(QPainter *painter, const QPoint &pt);

private:
    //�ദ��
    QSharedPointer<ScreenJudge> m_pScreenJudge;

    //��Ļ����
    int             m_iWidth;			//������Ļ�Ŀ��
    int             m_iHeight;			//��Ļ�ĸ߶�
    QPixmap         m_fullScreenPix;	//��ȡ��������Ļ
    QImage          m_fullScreenFogImg;	//�������ת������
	QPoint          m_ptPressedPos;		//���ƽ�������ʹ�õĵ�
	QPoint          m_ptReleasedPos;
	QPoint			m_ptCurrentPos;
	bool			m_bMousePressed;	//���ڻ���һЩ�м�״̬

	QPalette		m_palette;
    //draw��
    bool            m_bIsdrawing;		
	bool			m_bFirst;
    QPixmap         m_drawPix;			//����ͼƬ��������������С��Ӧ
    QRect           m_drawRect;			//��������
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
    QPoint          m_ptDragStartPos;
    QPoint          m_movePoint;
    DragJudge       m_dragJudge;

    //��ǰѡ�л�������
    bool            m_bIsSelectDrawShape;    //��־��ǰ�Ƿ���ѡ��ĳ����״�������϶���Ϊ
    DrawShapeType		m_shapeType;
    QPoint			m_ptShapeStartPos;
	QPoint			m_ptShapeEndPos;
	QPoint			m_ptShapeCurrentPos;

	DrawStatus		m_drawType;
    ScreenToolBar	*m_pToolBar;			//������

	ShapeInfo			m_currentShapeInfo;		//��ǰ���ڻ���ͼ��
	QStack<ShapeInfo>	m_shapeStack;			//����stack��Ϊ��֧�ֺ���ĳ�������
	//QVector<QRect>	m_dragRect;				//���϶����С�ļ���rect����,�򻯼���

	QVector<QPoint>		m_mosaicVec;
	QTextEdit		*m_textEdit;
	QRect			m_rcTextEdit;
};

#endif // SCREENIMG_H
