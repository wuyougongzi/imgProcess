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

//当前绘制的类型
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
	QPoint		ptCenter;	//画圆形的可能需要,不知道能不能用上
	QColor		brushColor;	//填充颜色，不知道能不能用到
	QColor		penColor;	//边框颜色
	int			penWeight;	//边框粗细
	ShapeInfo()
	{
		type = DRAWTYPENONE;
		penWeight = 1;
		penColor.setRgb(255, 0, 0);
		brushColor.setRgb(255, 0, 0);
	}
};

//paint 状态机
enum DrawStatus
{
	DrawScreenNone = 0,
	DrawScreenArea,			//绘制需要捕捉的屏幕位置
	DrawScreenDragPos,		//拖动区域时绘制
	DrawScreenDragSize,		//拖动大小时绘制
	DrawScreenShape,		//需要绘制里面的形状
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
	void drawRectDragPoint(const QRect& rect);			//绘制屏幕区域可拖动的点
	void drawZoomArea(const QPoint& pt);				//绘制放大框
	QPoint getLeftTopPoint(const QPoint &pt1, const QPoint &pt2);
	QPoint getRightBottomPoint(const QPoint &pt1, const QPoint &pt2);
	QRect getDrawRect(const QPoint &pt1, const QPoint &pt2);
	void showToolBar(const QPoint &drawAreaRightBottomPt);
	void drawShapeArrow(QPainter *painter, const QPoint &ptStart, const QPoint &ptEnd);
	void drawTextAreaRect(QPainter *painter);
	void drawExitingShapeAll(QPainter *painter);
	void drawMosaic(QPainter *painter, const QPoint &pt);

private:
    //类处理
    QSharedPointer<ScreenJudge> m_pScreenJudge;

    //屏幕处理
    int             m_iWidth;			//整个屏幕的宽度
    int             m_iHeight;			//屏幕的高度
    QPixmap         m_fullScreenPix;	//截取的整个屏幕
    QImage          m_fullScreenFogImg;	//由上面的转换而来
	QPoint          m_ptPressedPos;		//绘制截屏区域使用的点
	QPoint          m_ptReleasedPos;
	QPoint			m_ptCurrentPos;
	bool			m_bMousePressed;	//用于绘制一些中间状态

	QPalette		m_palette;
    //draw框
    bool            m_bIsdrawing;		
	bool			m_bFirst;
    QPixmap         m_drawPix;			//截屏图片，和下面的区域大小对应
    QRect           m_drawRect;			//截屏区域
    //zoom框
    bool            m_bIszooming;
    QPoint          m_zoomPoint;
    QPixmap         m_pixMap;
    QRect           m_zoomRect;
    QRect           m_infoFirstRect;
    QRect           m_infoSecondRect;
    QRect           m_infoThirdRect;

    //drag框
    bool            m_bIsdraging;
    QPoint          m_ptDragStartPos;
    QPoint          m_movePoint;
    DragJudge       m_dragJudge;

    //当前选中绘制类型
    bool            m_bIsSelectDrawShape;    //标志当前是否有选中某种形状，还是拖动行为
    DrawShapeType		m_shapeType;
    QPoint			m_ptShapeStartPos;
	QPoint			m_ptShapeEndPos;
	QPoint			m_ptShapeCurrentPos;

	DrawStatus		m_drawType;
    ScreenToolBar	*m_pToolBar;			//工具栏

	ShapeInfo			m_currentShapeInfo;		//当前正在画的图形
	QStack<ShapeInfo>	m_shapeStack;			//采用stack，为了支持后面的撤销操作
	//QVector<QRect>	m_dragRect;				//可拖动变大小的几个rect区域,简化计算

	QVector<QPoint>		m_mosaicVec;
	QTextEdit		*m_textEdit;
	QRect			m_rcTextEdit;
};

#endif // SCREENIMG_H
