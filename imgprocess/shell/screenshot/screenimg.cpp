#include "screenimg.h"
#include <QApplication>
#include <QDateTime>
#include <QClipboard>
#include <QDesktopWidget>
#include <QClipboard>
#include <QToolBar>
#include <QApplication>
#include <QBrush>
#include "screentoolbar.h"

#define DRAGPOINTWIDTH 5

static const int MOSAICWIDTH = 6;

ScreenShotImgDlg::ScreenShotImgDlg(QDialog *parent/* = 0*/) 
    : QDialog(parent)
	, m_bFirst(true)
	, m_drawType(DrawScreenNone)
	, m_dragJudge(DRAGJUDGE_NULL)
	, m_shapeType(DRAWTYPENONE)
	, m_bMousePressed(false)
	, m_pTextEdit(NULL)
{
	/*
	 * 初始化截图屏幕
	 */
	//获取屏幕尺寸
#ifdef _DEBUG
#else
	setWindowFlags(Qt::WindowStaysOnTopHint);
#endif
	
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect deskRect = desktopWidget->screenGeometry();
	m_iWidth = deskRect.width();
	m_iHeight = deskRect.height();
	//清空图片
	m_fullScreenPix = QPixmap();
	//获取桌面图片
	m_fullScreenPix = QPixmap::grabWindow(QApplication::desktop()->winId());
	//黑化桌面照片
	int red, green, blue;
	m_fullScreenFogImg = m_fullScreenPix.toImage();
	for (int x = 0; x < m_iWidth; x++)
	{
		for (int y = 0; y < m_iHeight; y++)
		{
			red = qRed(m_fullScreenFogImg.pixel(x, y)) * 0.6;
			green = qGreen(m_fullScreenFogImg.pixel(x, y)) * 0.6;
			blue = qBlue(m_fullScreenFogImg.pixel(x, y)) * 0.6;
			m_fullScreenFogImg.setPixel(x, y, qRgb(red, green, blue));
		}
	}
	//设为新窗口的背景图片以便获取
	m_palette.setBrush(QPalette::Background, QBrush(QPixmap(m_fullScreenPix)));
	setAutoFillBackground(true);
	setPalette(m_palette);
	showFullScreen();
    //设置鼠标可用
	setMouseTracking(true);
	m_palette.setBrush(QPalette::Background, QBrush(m_fullScreenFogImg));
	setAutoFillBackground(true);
	setPalette(m_palette);

	//初始化,表示整个程序开始运作。
	m_zoomPoint = QCursor::pos();

	m_pToolBar = new ScreenToolBar(this);
	connect(m_pToolBar, SIGNAL(selectRect()), this, SLOT(onBtnDrawRectangle()));
	connect(m_pToolBar, SIGNAL(selectSave()), this, SLOT(onBtnSaveClicked()));
	connect(m_pToolBar, SIGNAL(selectCancal()), this, SLOT(onBtnCancle()));
	connect(m_pToolBar, SIGNAL(selectFinish()), this, SLOT(onBtnSureToClipboardClicked()));
	connect(m_pToolBar, SIGNAL(selectText()), this, SLOT(onBtnText()));
	connect(m_pToolBar, SIGNAL(selectMosaic()), this, SLOT(onBtnMosaic()));
	connect(m_pToolBar, SIGNAL(selectUndu()), this, SLOT(onBtnUndu()));
	connect(m_pToolBar, SIGNAL(selectArrow()), this, SLOT(onBtnArrow()));
}

ScreenShotImgDlg::~ScreenShotImgDlg()
{
}

void ScreenShotImgDlg::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
		return;
	
	m_bMousePressed = true;

	//第一种状态
	if(m_drawType == DrawScreenNone)
	{
		m_ptPressedPos = event->pos();
	}
	//第二种状态
	if(m_drawType == DrawScreenArea)
	{
		m_ptDragStartPos = event->pos();
		//两种情况，鼠标在点上，或者边框线上，调整大小
		//鼠标不在以上区域且鼠标在截屏区域内，调整位置
		//判断第一种情况,鼠标在线上
		//简化问题，只判断四个方向的拖动情况
		if(m_ptDragStartPos.x() == m_drawRect.left())
		{
			this->setCursor(Qt::SizeHorCursor);
			m_dragJudge = DRAGJUDGE_LEFT;
			m_drawType = DrawScreenDragSize;
		}
		else if(m_ptDragStartPos.x() == m_drawRect.right())
		{
			this->setCursor(Qt::SizeHorCursor);
			m_dragJudge = DRAGJUDGE_RIGHT;
			m_drawType = DrawScreenDragSize;
		}
		else if(m_ptDragStartPos.y() == m_drawRect.top())
		{
			this->setCursor(Qt::SizeVerCursor);
			m_dragJudge = DRAGJUDGE_UP;
			m_drawType = DrawScreenDragSize;

		}
		else if(m_ptDragStartPos.y() == m_drawRect.bottom())
		{
			this->setCursor(Qt::SizeVerCursor);
			m_dragJudge = DRAGJUDGE_DOWN;
			m_drawType = DrawScreenDragSize;

		}
		else if(m_drawRect.contains(m_ptDragStartPos))
		{
			if(m_shapeType == DRAWTYPENONE)
			{
				this->setCursor(Qt::SizeAllCursor);
				m_dragJudge = DRAGJUDGE_INSIDE;
				m_drawType = DrawScreenDragPos;
			}
			else
			{
				m_ptShapeStartPos = event->pos();
				m_drawType = DrawScreenShape;
				if(m_shapeType == DRAWTYPEMOSAIC)
				{
					m_pixMap = getDrawAreaPixmap();
				}
				else if(m_shapeType == DRAWTYPETEXT && m_pTextEdit != NULL)
				{
					
				}
			}
		}
	}
	//if(m_bFirst)
	//
	//	m_DrawType = DrawScreenArea;
	//	return;
	//}
	/*
	m_pScreenJudge->setStartPoint(event->pos());
	if (m_bIsdraging)
	{
	*/
            /*
                1 位置在绘图区域内
                2 位置在线上
                3 位置在外面
            */
	/*
            if (m_pScreenJudge->isInDrawArea(event->pos()))
            {
                this->setCursor(Qt::SizeAllCursor);
                m_dragJudge = DRAGJUDGE_INSIDE;
                m_movePoint = event->pos();
            }
            else if(m_pScreenJudge->isInDragLine(event->pos()))
            {
                if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_EAST)
                {
                    this->setCursor(Qt::SizeHorCursor);
                    m_dragJudge = DRAGJUDGE_EAST;
                    m_movePoint = m_pScreenJudge->eastSouthPoint();
                    m_pScreenJudge->setStartPoint(m_pScreenJudge->westNorthPoint());
                }
                else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_WEST)
                {
                    this->setCursor(Qt::SizeHorCursor);
                    m_dragJudge = DRAGJUDGE_WEST;
                    m_movePoint = m_pScreenJudge->westSouthPoint();
                    m_pScreenJudge->setStartPoint(m_pScreenJudge->eastNorthPoint());
                }
                else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_SOUTH)
                {
                    this->setCursor(Qt::SizeVerCursor);
                    m_dragJudge = DRAGJUDGE_SOUTH;
                    m_movePoint = m_pScreenJudge->eastSouthPoint();
                    m_pScreenJudge->setStartPoint(m_pScreenJudge->westNorthPoint());
                }
                else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_NORTH)
                {
                    this->setCursor(Qt::SizeVerCursor);
                    m_dragJudge = DRAGJUDGE_NORTH;
                    m_movePoint = m_pScreenJudge->eastNorthPoint();
                    m_pScreenJudge->setStartPoint(m_pScreenJudge->westSouthPoint());
                 }
                 else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_EASTSOUTH)
                {
                    this->setCursor(Qt::SizeFDiagCursor);
                    m_dragJudge = DRAGJUDGE_EASTSOUTH;
                    m_movePoint.setX(event->pos().x() - m_pScreenJudge->drawWidth());
                    m_movePoint.setY(event->pos().y() - m_pScreenJudge->drawHeight());
                    m_pScreenJudge->setStartPoint(m_movePoint);
                }
                else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_WESTNORTH)
                {
                    this->setCursor(Qt::SizeFDiagCursor);
                    m_dragJudge = DRAGJUDGE_WESTNORTH;
                    m_movePoint.setX(event->pos().x() + m_pScreenJudge->drawWidth());
                    m_movePoint.setY(event->pos().y() + m_pScreenJudge->drawHeight());
                    m_pScreenJudge->setStartPoint(m_movePoint);
                }
                else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_WESTSOUTH)
                {
                    this->setCursor(Qt::SizeBDiagCursor);
                    m_dragJudge = DRAGJUDGE_WESTSOUTH;
                    m_movePoint.setX(event->pos().x() + m_pScreenJudge->drawWidth());
                    m_movePoint.setY(event->pos().y() - m_pScreenJudge->drawHeight());
                    m_pScreenJudge->setStartPoint(m_movePoint);
                }
                else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_EASTNORTH)
                {
                    this->setCursor(Qt::SizeBDiagCursor);
                    m_dragJudge = DRAGJUDGE_EASTNORTH;
                    m_movePoint.setX(event->pos().x() - m_pScreenJudge->drawWidth());
                    m_movePoint.setY(event->pos().y() + m_pScreenJudge->drawHeight());
                    m_pScreenJudge->setStartPoint(m_movePoint);
                }

                m_bIszooming = true;        //鼠标按下在拖动边界时显示放大对话框
            }
            else
            {
                this->setCursor(Qt::ArrowCursor);
                m_dragJudge = DRAGJUDGE_OUTSIDE;
            }
        }
		*/
}

void ScreenShotImgDlg::mouseMoveEvent(QMouseEvent *event)
{
	m_ptCurrentPos = event->pos();
	m_ptShapeCurrentPos = event->pos();
	if(m_ptCurrentPos.x() == m_drawRect.left())
	{
		this->setCursor(Qt::SizeHorCursor);
		//m_dragJudge = DRAGJUDGE_LEFT;
	}
	else if(m_ptCurrentPos.x() == m_drawRect.right())
	{
		this->setCursor(Qt::SizeHorCursor);
		//m_dragJudge = DRAGJUDGE_RIGHT;
	}
	else if(m_ptCurrentPos.y() == m_drawRect.top())
	{
		this->setCursor(Qt::SizeVerCursor);
		//m_dragJudge = DRAGJUDGE_UP;
	}
	else if(m_ptCurrentPos.y() == m_drawRect.bottom())
	{
		this->setCursor(Qt::SizeVerCursor);
		//m_dragJudge = DRAGJUDGE_DOWN;
	}
	else if(m_drawRect.contains(m_ptCurrentPos))
	{
		if(m_shapeType == DRAWTYPENONE)
			this->setCursor(Qt::SizeAllCursor);
		//m_dragJudge = DRAGJUDGE_INSIDE;
	}
	else {
		this->setCursor(Qt::ArrowCursor);
	}
	static QPoint lastTimePt(0, 0);
	if(m_drawType == DrawScreenShape && m_shapeType == DRAWTYPEMOSAIC && m_bMousePressed)
	{
		QPoint tmpPt = event->pos();
	/*	if(abs(tmpPt.x() - lastTimePt.x()) > MOSAICWIDTH * 2
		|| abs(tmpPt.y() - lastTimePt.y()) > MOSAICWIDTH *2)
	*/
			m_mosaicVec.push_back(event->pos());

		lastTimePt = event->pos();
	}
	update();
}

void ScreenShotImgDlg::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
		return;

	m_bMousePressed = false;
	m_ptShapeEndPos = event->pos();
	if(m_drawType == DrawScreenNone)
	{
		m_ptReleasedPos = event->pos();
		m_drawType = DrawScreenArea;

	}
	else if(m_drawType == DrawScreenArea)
	{
		
	}
	else if(m_drawType == DrawScreenDragPos)
	{
		m_ptPressedPos = m_ptPressedPos + (m_ptCurrentPos - m_ptDragStartPos);
		m_ptReleasedPos = m_ptReleasedPos + (m_ptCurrentPos - m_ptDragStartPos);
		m_drawType = DrawScreenArea;
	}
	else if(m_drawType == DrawScreenDragSize)
	{
		if(m_dragJudge == DRAGJUDGE_LEFT)
		{
			QPoint movePressed = m_ptPressedPos + (m_ptCurrentPos - m_ptDragStartPos);
			QPoint moveReleased = m_ptReleasedPos + (m_ptCurrentPos - m_ptDragStartPos);
			QPoint ptLeftTop = getLeftTopPoint(movePressed, moveReleased);
			m_ptReleasedPos = getRightBottomPoint(m_ptPressedPos, m_ptReleasedPos);
			m_ptPressedPos = ptLeftTop;
		}
		else if(m_dragJudge == DRAGJUDGE_RIGHT)
		{

		}
		else if(m_dragJudge == DRAGJUDGE_UP)
		{

		}
		else if(m_dragJudge == DRAGJUDGE_DOWN)
		{

		}
		m_drawType = DrawScreenArea;
	}
	else if(DrawScreenShape)
	{
		if(m_shapeType == DRAWTYPERECTANGLE)
		{
			m_currentShapeInfo.type = m_shapeType;
			m_currentShapeInfo.ptLeftTop = getLeftTopPoint(m_ptShapeStartPos, m_ptShapeCurrentPos);
			m_currentShapeInfo.ptRightBottom = getRightBottomPoint(m_ptShapeStartPos, m_ptShapeCurrentPos);
			m_shapeStack.push(m_currentShapeInfo);
		}
		else if(m_shapeType == DRAWTYPEARROW)
		{
			m_currentShapeInfo.type = m_shapeType;
			m_currentShapeInfo.ptLeftTop = m_ptShapeStartPos;
			m_currentShapeInfo.ptRightBottom = m_ptShapeCurrentPos;
			m_shapeStack.push(m_currentShapeInfo);
		}
		m_drawType = DrawScreenArea;
	}
	
	m_dragJudge = DRAGJUDGE_NULL;
	update();
}

void ScreenShotImgDlg::contextMenuEvent(QContextMenuEvent *event)
{
	Q_UNUSED(event);
    //todo:添加其他事件，供选择。
	onBtnCancle();
}

void ScreenShotImgDlg::mouseDoubleClickEvent(QMouseEvent *)
{
	onBtnSureToClipboardClicked();
}

void ScreenShotImgDlg::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		onBtnCancle();
		return;
	}
}

void ScreenShotImgDlg::onBtnSaveClicked()
{
	QString filename;
 	filename = QFileDialog::getSaveFileName(this, "Save ScreenShot Image",
 		QApplication::applicationDirPath(), tr("Image (*.jpg *.png *.bmp)"));
	if (filename.isNull())
	{
		return;
	}
	if (m_pixMap.save(filename))
	{
		emit onSaveSucessed(filename);
		onBtnCancle();
	}
}

void ScreenShotImgDlg::onBtnDrawRectangle()
{
    m_shapeType = DRAWTYPERECTANGLE;
}

QPixmap ScreenShotImgDlg::getDrawAreaPixmap()
{
	QPixmap pixmap(m_drawRect.size());

	QRegion region(m_drawRect);
	this->render(&pixmap, QPoint(0, 0), region);
	return pixmap;
}

void ScreenShotImgDlg::onBtnSureToClipboardClicked()
{
    //写剪贴板
    QClipboard *pClipBoard = QApplication::clipboard();
	QPixmap pixmap = getDrawAreaPixmap();

    pClipBoard->setPixmap(pixmap);
    onBtnCancle();
}

void ScreenShotImgDlg::onBtnCancle()
{
	this->close();
	emit onScreenImgClose();
}

void ScreenShotImgDlg::onBtnText()
{
	m_shapeType = DRAWTYPETEXT;
	if(m_pTextEdit == NULL)
	{
		m_pTextEdit = new QTextEdit(this);
		connect(m_pTextEdit, SIGNAL(textChanged()), this, SLOT(onTextEditTextChanged()));
	}
}

void ScreenShotImgDlg::onBtnUndu()
{
	if(!m_shapeStack.isEmpty())
	{
		m_shapeStack.pop();
		update();
	}
	else
		this->close();
}

void ScreenShotImgDlg::onBtnArrow()
{
	m_shapeType = DRAWTYPEARROW;
}

void ScreenShotImgDlg::onBtnMosaic()
{
	m_shapeType = DRAWTYPEMOSAIC;
}

void ScreenShotImgDlg::onTextEditTextChanged()
{

}

QPoint ScreenShotImgDlg::getLeftTopPoint(const QPoint &pt1, const QPoint &pt2)
{
	int leftTopX = pt1.x() < pt2.x() ? pt1.x() : pt2.x();
	int leftTopY = pt1.y() < pt2.y() ? pt1.y() : pt2.y();
	return QPoint(leftTopX, leftTopY);
}

QPoint ScreenShotImgDlg::getRightBottomPoint(const QPoint &pt1, const QPoint &pt2)
{
	int rightBottomX = pt1.x() > pt2.x() ? pt1.x() : pt2.x();
	int rightBottomY = pt1.y() > pt2.y() ? pt1.y() : pt2.y();
	return QPoint(rightBottomX, rightBottomY);
}

QRect ScreenShotImgDlg::getDrawRect(const QPoint &pt1, const QPoint &pt2)
{
	int leftTopX = pt1.x() < pt2.x() ? pt1.x() : pt2.x();
	int leftTopY = pt1.y() < pt2.y() ? pt1.y() : pt2.y();
	int rightBottomX = pt1.x() > pt2.x() ? pt1.x() : pt2.x();
	int rightBottomY = pt1.y() > pt2.y() ? pt1.y() : pt2.y();

	return QRect(QPoint(leftTopX, leftTopY), QPoint(rightBottomX, rightBottomY));
}

void ScreenShotImgDlg::showToolBar(const QPoint &drawAreaRightBottomPt)
{
	m_pToolBar->setGeometry(drawAreaRightBottomPt.x() - m_pToolBar->width(),
							drawAreaRightBottomPt.y() + 10, 
							m_pToolBar->width(), 
							m_pToolBar->height());
	m_pToolBar->show();
}

void ScreenShotImgDlg::drawRectDragPoint(const QRect& rect)
{
	QPainter drawpainter(this);
	QBrush brush(QColor(255, 0, 0, 125));
	QPen pen(QColor(255, 0, 0, 125));
	drawpainter.setBrush(brush);
	drawpainter.setPen(pen);

	//按顺时针绘制点
	//左上点
	QPoint ptLeftTop = rect.topLeft();
	drawpainter.drawRect(ptLeftTop.x() - (DRAGPOINTWIDTH + 1) / 2,
						ptLeftTop.y() - (DRAGPOINTWIDTH + 1) / 2,
						DRAGPOINTWIDTH, DRAGPOINTWIDTH);
	
	QPoint ptTopMiddle = (rect.topLeft() + rect.topRight()) / 2;
	drawpainter.drawRect(ptTopMiddle.x(),
						ptTopMiddle.y() - (DRAGPOINTWIDTH + 1) / 2,
						DRAGPOINTWIDTH, DRAGPOINTWIDTH);
	
	QPoint ptTopRight = rect.topRight();
	drawpainter.drawRect(ptTopRight.x() - (DRAGPOINTWIDTH + 1) / 2,
						ptTopRight.y() - (DRAGPOINTWIDTH + 1) / 2,
						DRAGPOINTWIDTH, DRAGPOINTWIDTH);

	
	QPoint ptRightMiddle = (rect.topRight() + rect.bottomRight()) / 2;
	drawpainter.drawRect(ptRightMiddle.x() - (DRAGPOINTWIDTH + 1) / 2,
						ptRightMiddle.y(),
						DRAGPOINTWIDTH, DRAGPOINTWIDTH);
	
	QPoint ptRightBottom = rect.bottomRight();
	drawpainter.drawRect(ptRightBottom.x() - (DRAGPOINTWIDTH + 1) / 2,
						ptRightBottom.y() - (DRAGPOINTWIDTH + 1) / 2,
						DRAGPOINTWIDTH, DRAGPOINTWIDTH);
	
	QPoint ptBottomMiddle = (rect.bottomRight() + rect.bottomLeft()) / 2;
	drawpainter.drawRect(ptBottomMiddle.x(), 
						ptBottomMiddle.y() - (DRAGPOINTWIDTH + 1) / 2,
						DRAGPOINTWIDTH, DRAGPOINTWIDTH);
	
	QPoint ptBottomLeft = rect.bottomLeft();
	drawpainter.drawRect(ptBottomLeft.x() - (DRAGPOINTWIDTH + 1) / 2,
						ptBottomLeft.y() - (DRAGPOINTWIDTH + 1) / 2,
						DRAGPOINTWIDTH, DRAGPOINTWIDTH);
	
	QPoint ptLeftMiddle = (rect.topLeft() + rect.bottomLeft()) / 2;
	drawpainter.drawRect(ptLeftMiddle.x()- (DRAGPOINTWIDTH + 1) / 2,
						ptLeftMiddle.y(),
						DRAGPOINTWIDTH, DRAGPOINTWIDTH);
}

void ScreenShotImgDlg::drawZoomArea(const QPoint& pt)
{
	QPainter zoomPainter(this);
	QPen pen;
	QBrush brush(QColor(0, 0, 0));
	QFont font("Microsoft YaHei", 8);
	int x, y;
	x = pt.x();
	y = pt.y();
	int width, height;
	width = m_drawRect.width();
	height = m_drawRect.height();
	//width = m_pScreenJudge->drawWidth();
	//height = m_pScreenJudge->drawHeight();
	int red, green, blue;
	red = qRed(m_fullScreenFogImg.pixel(x, y));
	green = qGreen(m_fullScreenFogImg.pixel(x, y));
	blue = qBlue(m_fullScreenFogImg.pixel(x, y));

	//放大框
	m_zoomRect = QRect(x - 10, y - 10, 20, 20);
	m_pixMap = m_fullScreenPix.copy(m_zoomRect);
	//if (m_pScreenJudge->zoomJudge() == ZOOMJUDGE_LEFTUP){

		zoomPainter.drawPixmap(x + 10, y + 10, 100, 100, m_pixMap);
		pen.setColor(QColor(0, 255, 0, 125));
		pen.setWidthF(3);
		zoomPainter.setPen(pen);
		zoomPainter.drawLine(x + 10 + 50, y + 15, x + 10 + 50, y + 10 + 95);
		zoomPainter.drawLine(x + 15, y + 10 + 50, x + 10 + 95, y + 10 + 50);
		pen.setColor(QColor(0, 0, 0));
		pen.setWidth(1);
		zoomPainter.setPen(pen);
		zoomPainter.drawRect(x + 10, y + 10, 100, 100);
		//信息框            
		brush.setColor(QColor(0, 0, 0, 200));
		zoomPainter.setBrush(brush);
		zoomPainter.drawRect(x + 10, y + 10 + 100, 100, 30);
		m_infoFirstRect = QRect(x + 10, y + 10 + 100, 100, 15);
		m_infoSecondRect = QRect(x + 10, y + 10 + 100 + 15, 100, 15);
		pen.setColor(QColor(255, 255, 255));
		zoomPainter.setPen(pen);
		zoomPainter.setFont(font);
		zoomPainter.drawText(m_infoFirstRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 x %2").arg(width).arg(height));
		zoomPainter.drawText(m_infoSecondRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("RGB(%1,%2,%3)").arg(red).arg(green).arg(blue));
	//}
}

void ScreenShotImgDlg::drawScreenArea(const QRect& rect)
{
	QPainter drawpainter(this);
	m_drawPix = m_fullScreenPix.copy(m_drawRect);
	QPen pen;
	pen.setColor(QColor(0, 255, 0, 125));
	pen.setWidthF(1);
	drawpainter.setPen(pen);

	QBrush brush(m_fullScreenPix);
	drawpainter.setBrush(brush);
	drawpainter.drawRect(m_drawRect);
}

void ScreenShotImgDlg::drawShapeArrow(QPainter *painter, const QPoint &ptStart, const QPoint &ptEnd)
{
	QLineF lineArrow(ptStart, ptEnd);
	qreal arrowLength = lineArrow.length();
	//默认值
	qreal arrowHeadLength = 16;
	qreal arrowHeadWidth = 16;
	qreal arrowSideWidth = 4;

	QPointF pt = lineArrow.pointAt((arrowLength - arrowHeadLength) / arrowLength);
	QLineF lineArrowHead(pt, lineArrow.p2());
	lineArrowHead.setAngle(lineArrow.angle() + 90);

	QPointF ptMid = lineArrowHead.pointAt(0.5);
	lineArrowHead.translate(pt - ptMid);

	QPointF pt1 = lineArrowHead.pointAt(0);
	QPointF pt2 = lineArrowHead.pointAt(1);

	QPointF pts[3] = {ptEnd, pt1, pt2};
	painter->drawPolygon(pts, 3);

	pt1 = lineArrowHead.pointAt(
		(arrowHeadWidth - arrowSideWidth) / arrowHeadWidth);
	pt2 = lineArrowHead.pointAt(
		1 - (arrowHeadWidth - arrowSideWidth) / arrowHeadWidth);
	QPointF ptOffset = lineArrow.pointAt(
		(arrowLength - arrowHeadLength + 2) / arrowLength);
	QLineF lineSide(pt1, pt2);
	ptMid = lineSide.pointAt(0.5);
	lineSide.translate(ptOffset - ptMid);

	pts[0] = ptStart;
	pts[1] = lineSide.p1();
	pts[2] = lineSide.p2();
	painter->drawPolygon(pts, 3);
}

void ScreenShotImgDlg::drawTextAreaRect(QPainter *painter)
{

}

void ScreenShotImgDlg::drawExitingShapeAll(QPainter *painter)
{
	for(QStack<ShapeInfo>::Iterator iter = m_shapeStack.begin(); iter != m_shapeStack.end(); iter++)
	{
		ShapeInfo tmpShapeInfo = *iter;
		if(tmpShapeInfo.type == DRAWTYPERECTANGLE)
		{
			painter->drawRect(QRect(tmpShapeInfo.ptLeftTop, tmpShapeInfo.ptRightBottom));
		}
		else if(tmpShapeInfo.type == DRAWTYPEARROW)
		{
			painter->setPen(Qt::NoPen);
			QBrush brush(QColor(255,0,0));
			painter->setBrush(brush);
			//反走样
			painter->setRenderHint(QPainter::Antialiasing, true);
			drawShapeArrow(painter, tmpShapeInfo.ptLeftTop, tmpShapeInfo.ptRightBottom);
		}
	}
}

void ScreenShotImgDlg::drawMosaic(QPainter *painter, const QPoint &currentPt)
{
	QImage image = m_pixMap.toImage();

	QPoint pt;
	for(int index = 0; index < (int)m_mosaicVec.size(); index++){
		//todo:好像长了之后还有拖动比较快之后绘制会有延迟，看起来比较明显
		//需要解决上面的问题
		pt = m_mosaicVec[index];
		int x = pt.x() - m_drawRect.topLeft().x();
		int y = pt.y() - m_drawRect.topLeft().y();
		int red = 0, green = 0, blue = 0;

		//总共 9 * 9个点
		for(int i = MOSAICWIDTH *(-1); i <= MOSAICWIDTH; i++)
		{
			for(int j = MOSAICWIDTH * (-1); j <= MOSAICWIDTH; j++)
			{
				//if()
				if(x + i >= 0 && x + i < image.width() && y + j >= 0 && y + j < image.height())
				{
					red += qRed(image.pixel(x + i, y + j));
					green += qGreen(image.pixel(x + i, y + j));
					blue += qBlue(image.pixel(x + i, y + j));
				}
			}
		}
		int PtCnt = ((MOSAICWIDTH * 2) + 1) * ((MOSAICWIDTH * 2) + 1);
		red = red / PtCnt;
		green = green / PtCnt;
		blue = blue / PtCnt;

		QBrush brush(QColor(red, green, blue));
		painter->setPen(Qt::NoPen);
		painter->setBrush(brush);

		painter->drawRect(QRect(QPoint(pt.x() - MOSAICWIDTH, pt.y() - MOSAICWIDTH),
			QPoint(pt.x() + MOSAICWIDTH, pt.y() + MOSAICWIDTH)));
	}
}

void ScreenShotImgDlg::paintEvent(QPaintEvent *event)
{
	/*
	1 下面m_bisdrawing,m_bIsdraging，m_bIszooming，m_bIsSelectDrawShape
	  是页面绘制状态机标志
	*/
	//todo: 可拉伸的点变成拖动，功能失效，需要重新查看调整。
	//todo: 调整点的大小，变得更可用
	//简化问题，只有通过四个方向的拖动改变大小
	//在区域中花矩形，后面的逻辑就更复杂了
	//需要自己重新尝试
	//todo：尝试绘制输入框及文字
	switch(m_drawType)
	{
	case DrawScreenNone:
		{
			__super::paintEvent(event);
			return ;
		}
		break;
	case DrawScreenArea:
		{
			m_drawRect = getDrawRect(m_ptPressedPos, m_ptReleasedPos);
			drawScreenArea(m_drawRect);
			drawRectDragPoint(m_drawRect);
			QPainter painter(this);

			//先绘制里面已经存在的
			drawExitingShapeAll(&painter);
			drawMosaic(&painter, m_ptShapeCurrentPos);

			if(m_pTextEdit != NULL)
			{
				painter.setBrush(Qt::NoBrush);
				painter.drawRect(QRect(m_ptShapeStartPos.x(), m_ptShapeStartPos.y(), 30 ,50));
				m_pTextEdit->setFixedHeight(50);
				m_pTextEdit->setFixedWidth(80);
				m_pTextEdit->setStyleSheet("border: 1px solid blue");
				m_pTextEdit->move(m_ptShapeStartPos);
				m_pTextEdit->show();
			}

			showToolBar(getRightBottomPoint(m_ptPressedPos, m_ptReleasedPos));
		}
		break;
	case DrawScreenShape:
		{
			m_drawRect = getDrawRect(m_ptPressedPos, m_ptReleasedPos);
			drawScreenArea(m_drawRect);
			drawRectDragPoint(m_drawRect);

			QPainter painter(this);
					//先绘制里面已经存在的
			drawExitingShapeAll(&painter);
			
				QPen pen(QColor(255, 0, 0));
				QBrush brush(QColor(255,255,255));
				painter.setBrush(brush);
				painter.setPen(pen);

				switch(m_shapeType)
				{
				case DRAWTYPERECTANGLE:							{
						if(m_bMousePressed)		//这里绘制的都是图形的中间状态
						{
							QRect shapeRect = getDrawRect(m_ptShapeStartPos, m_ptShapeCurrentPos);
							painter.drawRect(shapeRect);
						}
					}
					break;
				case DRAWTYPEARROW:
					{
						if(m_bMousePressed)
						{
							painter.setPen(Qt::NoPen);
							QBrush brush(QColor(255,0,0));
							painter.setBrush(brush);
							//反走样
							painter.setRenderHint(QPainter::Antialiasing, true);
							drawShapeArrow(&painter, m_ptShapeStartPos, m_ptShapeCurrentPos);
						}
					}
					break;
				case DRAWTYPEMOSAIC:
					{
						if(m_bMousePressed)
						{
							//painter
							//取鼠标附近9 * 9 像素点颜色的平均值
							//将brush 的宽度设置为9
							drawMosaic(&painter, m_ptShapeCurrentPos);
						}
					}
					break;
				case DRAWTYPETEXT:
					{
					/*	if(!m_bMousePressed)
						{
						painter.setBrush(Qt::NoBrush);
						painter.drawRect(QRect(m_ptShapeStartPos.x(), m_ptShapeStartPos.y(), 30 ,50));
						m_pTextEdit->setFixedHeight(30);
						m_pTextEdit->setFixedWidth(50);
						//m_pTextEdit->setStyleSheet("border: 1px solid blue");
						m_pTextEdit->move(m_ptShapeStartPos);
						}
						*/
					}
					break;
				case DRAWTYPENONE:
					break;
				default:
					break;
				}
			showToolBar(getRightBottomPoint(m_ptPressedPos, m_ptReleasedPos));
		}
		break;
	case DrawScreenDragSize:
		{
			switch(m_dragJudge)
			{
			case DRAGJUDGE_LEFT:
				{
					QPoint movePressed = m_ptPressedPos + (m_ptCurrentPos - m_ptDragStartPos);
					QPoint moveReleased = m_ptReleasedPos + (m_ptCurrentPos - m_ptDragStartPos);
					QPoint ptLeftTop = getLeftTopPoint(movePressed, moveReleased);
					m_drawRect = getDrawRect(ptLeftTop, getRightBottomPoint(m_ptPressedPos, m_ptReleasedPos));
					drawScreenArea(m_drawRect);
					drawRectDragPoint(m_drawRect);
				}
				break;
			default:
				break;
			}
			drawZoomArea(m_ptCurrentPos);
		}
		break;
	case DrawScreenDragPos:
		{
			QPoint movePressed = m_ptPressedPos + (m_ptCurrentPos - m_ptDragStartPos);
			QPoint moveReleased = m_ptReleasedPos + (m_ptCurrentPos - m_ptDragStartPos);
			m_drawRect = getDrawRect(movePressed, moveReleased);
			drawScreenArea(m_drawRect);
			drawRectDragPoint(m_drawRect);
			showToolBar(getRightBottomPoint(movePressed, moveReleased));
		}
		break;
	default:
		break;
	}
	__super::paintEvent(event);
}
