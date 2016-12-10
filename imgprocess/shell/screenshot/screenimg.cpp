#include "screenimg.h"
#include <QApplication>
#include <QDateTime>
#include <QClipboard>
#include <QIcon>
#include <QLayout>
#include <QDesktopWidget>
#include <QClipboard>
#include <QToolBar>
#include <QRubberBand>
#include <QApplication>
#include <QBrush>
#include "screentoolbar.h"

#define DRAGPOINTWIDTH 5

ScreenShotImgDlg::ScreenShotImgDlg(QDialog *parent/* = 0*/) 
    : QDialog(parent)
	, m_bFirst(true)
	, m_bIsdrawing(false)
	, m_drawType(DrawScreenNone)
	, m_dragJudge(DRAGJUDGE_NULL)
	, m_shapeType(DRAWTYPENONE)
	, m_bIsdraging(false)
	, m_bMousePressed(false)
{
	/*
	 * 初始化截图屏幕
	 */
	//获取屏幕尺寸
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
	//m_bIsdrawing = false;
	m_bIszooming = true;
	m_zoomPoint = QCursor::pos();
	
	//初始化类计算
	m_pScreenJudge = QSharedPointer<ScreenJudge>(new ScreenJudge(m_iWidth - 1, m_iHeight - 1, m_zoomPoint));
	
    m_pToolBar = new ScreenToolBar(this);
	connect(m_pToolBar, SIGNAL(selectRect()), this, SLOT(onBtnDrawRectangle()));
	connect(m_pToolBar, SIGNAL(selectSave()), this, SLOT(onBtnSaveClicked()));
	connect(m_pToolBar, SIGNAL(selectCancal()), this, SLOT(onBtnCancle()));
	connect(m_pToolBar, SIGNAL(selectFinish()), this, SLOT(onBtnSureToClipboardClicked()));

    m_bIsSelectDrawShape = false;
   

	//m_dragRect.resize(8);
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
		//m_drawType = DrawScreenDragSize;
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
				m_currentShapeInfo.type = m_shapeType;
				//m_currentShapeInfo.
			}
		}
	}
	//if(m_bFirst)
	//{
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
   /* if (m_bIsdrawing)
    {
        if (event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
        {
            m_pScreenJudge->setEndPoint(event->pos());
        }
    }
    if (m_bIszooming)
    {
        m_pScreenJudge->setMousePoint(event->pos());
        m_zoomPoint = event->pos();
    }
    if (m_bIsdraging)
    {
        //设置鼠标样式
        if (m_pScreenJudge->isInDrawArea(event->pos()))
        {
            this->setCursor(Qt::SizeAllCursor);
        }
        else if (m_pScreenJudge->isInDragLine(event->pos()))
        {
            if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_EAST)
                this->setCursor(Qt::SizeHorCursor);
            else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_WEST)
                this->setCursor(Qt::SizeHorCursor);
            else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_SOUTH)
                this->setCursor(Qt::SizeVerCursor);
            else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_NORTH)
                this->setCursor(Qt::SizeVerCursor);
            else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_EASTSOUTH)
                this->setCursor(Qt::SizeFDiagCursor);
            else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_WESTNORTH)
                this->setCursor(Qt::SizeFDiagCursor);
            else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_WESTSOUTH)
                this->setCursor(Qt::SizeBDiagCursor);
            else if (m_pScreenJudge->dragJudge(event->pos()) == DRAGJUDGE_EASTNORTH)
                this->setCursor(Qt::SizeBDiagCursor);
        }
        else
        {
            this->setCursor(Qt::ArrowCursor);
        }

        if (m_dragJudge == DRAGJUDGE_INSIDE)
        {
            QPoint p(event->pos().x() - m_movePoint.x(), event->pos().y() - m_movePoint.y());
            m_pScreenJudge->moveTo(p);
            m_movePoint = event->pos();
        }
        else if (m_dragJudge == DRAGJUDGE_EAST)
		{
			this->setCursor(Qt::SizeHorCursor);
			m_movePoint.setX(event->pos().x());
			m_pScreenJudge->setEndPoint(m_movePoint);
		}
		else if (m_dragJudge == DRAGJUDGE_WEST)
		{
			this->setCursor(Qt::SizeHorCursor);
			m_movePoint.setX(event->pos().x());
			m_pScreenJudge->setEndPoint(m_movePoint);
		}
		else if (m_dragJudge == DRAGJUDGE_SOUTH)
		{
			this->setCursor(Qt::SizeVerCursor);
			m_movePoint.setY(event->pos().y());
			m_pScreenJudge->setEndPoint(m_movePoint);
		}
		else if (m_dragJudge == DRAGJUDGE_NORTH)
		{
			this->setCursor(Qt::SizeVerCursor);
			m_movePoint.setY(event->pos().y());
			m_pScreenJudge->setEndPoint(m_movePoint);
		}
		else if (m_dragJudge == DRAGJUDGE_EASTNORTH)
		{
			this->setCursor(Qt::SizeBDiagCursor);
			m_pScreenJudge->setEndPoint(event->pos());
		}
		else if (m_dragJudge == DRAGJUDGE_EASTSOUTH)
		{
			this->setCursor(Qt::SizeFDiagCursor);
			m_pScreenJudge->setEndPoint(event->pos());
		}
		else if (m_dragJudge == DRAGJUDGE_WESTNORTH)
		{
			this->setCursor(Qt::SizeFDiagCursor);
			m_pScreenJudge->setEndPoint(event->pos());
		}
		else if (m_dragJudge == DRAGJUDGE_WESTSOUTH)
		{
			this->setCursor(Qt::SizeBDiagCursor);
			m_pScreenJudge->setEndPoint(event->pos());
		}
	}
	*/
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

	//if(m_drawType == DrawScreenNone)
		m_drawType = DrawScreenArea;

	}
	else if(m_drawType == DrawScreenArea)
	{
		if(m_shapeType != DRAWTYPENONE)
		{
			m_currentShapeInfo.type = m_shapeType;
			m_currentShapeInfo.ptLeftTop = getLeftTopPoint(m_ptShapeStartPos, m_ptShapeCurrentPos);
			m_currentShapeInfo.ptRightBottom = getRightBottomPoint(m_ptShapeStartPos, m_ptShapeCurrentPos);
			m_shapeStack.push(m_currentShapeInfo);
		}
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
	
	m_dragJudge = DRAGJUDGE_NULL;
	//if(m_DrawType == DrawScreenArea)
	//	m_bIsdrawing = true;

	/*
        if (m_bIszooming)
            m_bIszooming = false;
        
        if (m_bIsdrawing)
        {
            m_pScreenJudge->setEndPoint(event->pos());
            m_bIsdrawing = false;
        }
        
        if (!m_bIsdraging)
        {
            m_bIsdraging = true;
            m_dragJudge = DRAGJUDGE_OUTSIDE;
        }
        else if (m_dragJudge != DRAGJUDGE_OUTSIDE)
        {
            m_dragJudge = DRAGJUDGE_OUTSIDE;
        }

		m_ptReleasedPos = event->pos();
		*/
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
	if (m_bIsdraging)
		onBtnSureToClipboardClicked();

}

void ScreenShotImgDlg::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		onBtnCancle();
		return;
	}
	if (m_bIsdraging){
		QPoint startPoint = m_pScreenJudge->westNorthPoint();
		QPoint endPoint = m_pScreenJudge->eastSouthPoint();
		if (event->key() == Qt::Key_Left)
		{
			if (startPoint.x() - 1 < 0)
			{
				return;
			}
			else
			{
				m_pScreenJudge->setStartPoint(QPoint(startPoint.x() - 1, startPoint.y()));
				m_pScreenJudge->setEndPoint(QPoint(endPoint.x() - 1, endPoint.y()));
			}

		}
		if (event->key() == Qt::Key_Right)
		{
			if (endPoint.x() + 1 > m_iWidth - 1)
			{
				return;
			}
			else
			{
				m_pScreenJudge->setStartPoint(QPoint(startPoint.x() + 1, startPoint.y()));
				m_pScreenJudge->setEndPoint(QPoint(endPoint.x() + 1, endPoint.y()));
			}

		}
		if (event->key() == Qt::Key_Up)
		{
			if (startPoint.y() - 1 < 0)
			{
				return;
			}
			else
			{
				m_pScreenJudge->setStartPoint(QPoint(startPoint.x(), startPoint.y() - 1));
				m_pScreenJudge->setEndPoint(QPoint(endPoint.x(), endPoint.y() - 1));
			}
		}
		if (event->key() == Qt::Key_Down)
		{
			if (endPoint.y() + 1 > m_iHeight - 1)
			{
				return;
			}
			else
			{
				m_pScreenJudge->setStartPoint(QPoint(startPoint.x(), startPoint.y() + 1));
				m_pScreenJudge->setEndPoint(QPoint(endPoint.x(), endPoint.y() + 1));
			}

		}
		update();
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
    //设置当前pen为绘制矩形框的
    m_bIsSelectDrawShape = true;
    m_bIsdraging = false;
    m_shapeType = DRAWTYPERECTANGLE;
}

void ScreenShotImgDlg::onBtnSureToClipboardClicked()
{
    //写剪贴板
    QClipboard *pClipBoard = QApplication::clipboard();
	QPixmap pixmap(m_drawRect.size());

	QRegion region(m_drawRect);
	this->render(&pixmap, QPoint(0, 0), region);
    pClipBoard->setPixmap(pixmap);
    onBtnCancle();
}

void ScreenShotImgDlg::onBtnCancle()
{
	this->close();
	emit onScreenImgClose();
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
	width = m_pScreenJudge->drawWidth();
	height = m_pScreenJudge->drawHeight();
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
			if(!m_shapeStack.isEmpty())
			{
					//先绘制里面已经存在的
				for(QStack<ShapeInfo>::Iterator iter = m_shapeStack.begin(); iter != m_shapeStack.end(); iter++)
				{
					ShapeInfo tmpShapeInfo = *iter;
					if(tmpShapeInfo.type == DRAWTYPERECTANGLE)
					{
						painter.drawRect(QRect(tmpShapeInfo.ptLeftTop, tmpShapeInfo.ptRightBottom));
					}
				}
			}
			else		
			{
				
				QPen pen(QColor(255, 0, 0));
				QBrush brush(QColor(255,255,255));
				painter.setBrush(brush);
				painter.setPen(pen);

				switch(m_shapeType)
				{
				case DRAWTYPERECTANGLE:
					{
						if(m_bMousePressed)		//这里绘制的都是图形的中间状态
						{
							QRect shapeRect = getDrawRect(m_ptShapeStartPos, m_ptShapeCurrentPos);
							painter.drawRect(shapeRect);
						}
						/*
						else		//都已经放到stack里面绘制了
						{
							QRect shapeRect = getDrawRect(m_ptShapeStartPos, m_ptShapeEndPos);
							painter.drawRect(shapeRect);
						}
						*/
					}
					break;
				case DRAWTYPENONE:
					break;
				default:
					break;
				}
			}
			/*else
			{
				if(m_shapeType.type != DRAWTYPENONE)
				{
					//绘制当前的这个
				}
			}
			*/

			
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
					//showToolBar(getRightBottomPoint(m_ptPressedPos, m_ptReleasedPos));
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
	/*
	if (m_bIsdrawing)
    {
		//draw中间截屏区域
		
		QFont font("Microsoft YaHei", 8);
		int x, y;
		x = m_pScreenJudge->westNorthPoint().x();
		y = m_pScreenJudge->westNorthPoint().y();
		int width, height;
		width = m_pScreenJudge->drawWidth();
		height = m_pScreenJudge->drawHeight();

		
		//draw可拉伸点的画~。
		QBrush brush(QColor(0, 255, 0, 125));
		drawpainter.setBrush(brush);
		
		m_dragPoint = m_pScreenJudge->eastPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->westPoint();
		drawpainter.drawRect(m_dragPoint.x() - 3, m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->southPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->northPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y() - 3, 3, 3);
		m_dragPoint = m_pScreenJudge->eastSouthPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->eastNorthPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y() - 3, 3, 3);
		m_dragPoint = m_pScreenJudge->westSouthPoint();
		drawpainter.drawRect(m_dragPoint.x() - 3, m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->westNorthPoint();
		drawpainter.drawRect(m_dragPoint.x() - 3, m_dragPoint.y() - 3, 3, 3);

		
		//draw 鼠标所有像素放大图像尺寸
		if (m_pScreenJudge->infoJudge() == ZOOMJUDGE_LEFTDOWN)
		{
			pen.setColor(QColor(0, 0, 0, 150));
			pen.setWidth(1);
			drawpainter.setPen(pen);
			brush.setColor(QColor(0, 0, 0, 200));
			drawpainter.setBrush(brush);
			drawpainter.drawRect(x, y - 18, 60, 15);
			m_infoThirdRect = QRect(x, y - 18, 60, 15);
			pen.setColor(QColor(255, 255, 255));
			drawpainter.setPen(pen);
			drawpainter.setFont(font);
			drawpainter.drawText(m_infoThirdRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 x %2").arg(width).arg(height));
		}
		else if (m_pScreenJudge->infoJudge() == ZOOMJUDGE_LEFTUP)
		{
			pen.setColor(QColor(0, 0, 0, 150));
			pen.setWidth(1);
			drawpainter.setPen(pen);
			brush.setColor(QColor(0, 0, 0, 200));
			drawpainter.setBrush(brush);
			drawpainter.drawRect(x + 3, y + 3, 60, 15);
			m_infoThirdRect = QRect(x, y + 3, 60, 15);
			pen.setColor(QColor(255, 255, 255));
			drawpainter.setPen(pen);
			drawpainter.setFont(font);
			drawpainter.drawText(m_infoThirdRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 x %2").arg(width).arg(height));
		}
	}
	
	if (m_bIsdraging)
    {
		m_drawRect = m_pScreenJudge->drawRect();
		QPainter drawpainter(this);
		m_pixMap = m_fullScreenPix.copy(m_drawRect);
		drawpainter.drawPixmap(m_drawRect, m_pixMap);
		QPen pen;
		pen.setColor(QColor(0, 255, 0, 125));
		pen.setWidthF(1);
		drawpainter.setPen(pen);
		drawpainter.drawRect(m_drawRect);
		QFont font("Microsoft YaHei", 8);
		int x, y;
		x = m_pScreenJudge->westNorthPoint().x();
		y = m_pScreenJudge->westNorthPoint().y();
		int width, height;
		width = m_pScreenJudge->drawWidth();
		height = m_pScreenJudge->drawHeight();

		//可拉伸点的画~。
		QBrush brush(QColor(0, 255, 0, 125));
		drawpainter.setBrush(brush);
		m_dragPoint = m_pScreenJudge->eastPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->westPoint();
		drawpainter.drawRect(m_dragPoint.x() - 3, m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->southPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->northPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y() - 3, 3, 3);
		m_dragPoint = m_pScreenJudge->eastSouthPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->eastNorthPoint();
		drawpainter.drawRect(m_dragPoint.x(), m_dragPoint.y() - 3, 3, 3);
		m_dragPoint = m_pScreenJudge->westSouthPoint();
		drawpainter.drawRect(m_dragPoint.x() - 3, m_dragPoint.y(), 3, 3);
		m_dragPoint = m_pScreenJudge->westNorthPoint();
		drawpainter.drawRect(m_dragPoint.x() - 3, m_dragPoint.y() - 3, 3, 3);

		//右键菜单
		QAction *actionSave = new QAction(tr("保存为  &S"), this);;
		QAction *actionCancle = new QAction(tr("取消 &C"), this);
		QToolBar toolbar(this);
		actionSave = new QAction(tr("保存为  &S"), this);
		toolbar.addAction(actionSave);
		connect(actionSave, SIGNAL(triggered()), this, SLOT(onBtnSaveClicked()));
		toolbar.addAction(actionCancle);
		connect(actionCancle, SIGNAL(triggered()), this, SLOT(onBtnCancle()));
		toolbar.setGeometry(m_drawRect);

		//信息框
		if (m_pScreenJudge->infoJudge() == ZOOMJUDGE_LEFTDOWN)
		{
			pen.setColor(QColor(0, 0, 0, 150));
			pen.setWidth(1);
			drawpainter.setPen(pen);
			brush.setColor(QColor(0, 0, 0, 200));
			drawpainter.setBrush(brush);
			drawpainter.drawRect(x, y - 18, 60, 15);
			m_infoThirdRect = QRect(x, y - 18, 60, 15);
			pen.setColor(QColor(255, 255, 255));
			drawpainter.setPen(pen);
			drawpainter.setFont(font);
			drawpainter.drawText(m_infoThirdRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 x %2").arg(width).arg(height));
		}
		else if (m_pScreenJudge->infoJudge() == ZOOMJUDGE_LEFTUP)
		{
			pen.setColor(QColor(0, 0, 0, 150));
			pen.setWidth(1);
			drawpainter.setPen(pen);
			brush.setColor(QColor(0, 0, 0, 200));
			drawpainter.setBrush(brush);
			drawpainter.drawRect(x + 3, y + 3, 60, 15);
			m_infoThirdRect = QRect(x, y + 3, 60, 15);
			pen.setColor(QColor(255, 255, 255));
			drawpainter.setPen(pen);
			drawpainter.setFont(font);
			drawpainter.drawText(m_infoThirdRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 x %2").arg(width).arg(height));
		}

		if (m_pScreenJudge->btnJudge() == DRAGJUDGE_INSIDE)
		{
			m_pToolBar->setGeometry(m_pScreenJudge->eastNorthPoint().x() - m_pToolBar->width(),
									m_pScreenJudge->eastNorthPoint().y(), 
									m_pToolBar->width(), 
									m_pToolBar->height());
			m_pToolBar->show();
		}
		else if (m_pScreenJudge->btnJudge() == DRAGJUDGE_SOUTH)
		{
            m_pToolBar->setGeometry(m_pScreenJudge->eastSouthPoint().x() - m_pToolBar->width(),
									m_pScreenJudge->eastSouthPoint().y(), m_pToolBar->width(), m_pToolBar->height());
            m_pToolBar->show();
		}
		else if (m_pScreenJudge->btnJudge() == DRAGJUDGE_NORTH)
		{
			m_pToolBar->setGeometry(m_pScreenJudge->eastSouthPoint().x() - m_pToolBar->width(),
				m_pScreenJudge->eastSouthPoint().y(), m_pToolBar->width(), m_pToolBar->height());
			m_pToolBar->show();
		}
	}

    //拖动窗口大小的时候zooming小窗口才显示
    if (m_bIszooming)
    {
        QPainter zoomPainter(this);
        QPen pen;
        QBrush brush(QColor(0, 0, 0));
        QFont font("Microsoft YaHei", 8);
        int x, y;
        x = m_zoomPoint.x();
        y = m_zoomPoint.y();
        int width, height;
        width = m_pScreenJudge->drawWidth();
        height = m_pScreenJudge->drawHeight();
        int red, green, blue;
        red = qRed(m_fullScreenFogImg.pixel(x, y));
        green = qGreen(m_fullScreenFogImg.pixel(x, y));
        blue = qBlue(m_fullScreenFogImg.pixel(x, y));

        //放大框
        m_zoomRect = QRect(x - 10, y - 10, 20, 20);
        m_pixMap = m_fullScreenPix.copy(m_zoomRect);
        if (m_pScreenJudge->zoomJudge() == ZOOMJUDGE_LEFTUP){
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
        }
        else if (m_pScreenJudge->zoomJudge() == ZOOMJUDGE_LEFTDOWN){
            zoomPainter.drawPixmap(x + 10, y - 130, 100, 100, m_pixMap);
            pen.setColor(QColor(0, 255, 0, 125));
            pen.setWidthF(3);
            zoomPainter.setPen(pen);
            zoomPainter.drawLine(x + 10 + 50, y - 125, x + 10 + 50, y - 35);
            zoomPainter.drawLine(x + 15, y - 80, x + 10 + 95, y - 80);
            pen.setColor(QColor(0, 0, 0));
            pen.setWidth(1);
            zoomPainter.setPen(pen);
            zoomPainter.drawRect(x + 10, y - 130, 100, 100);
            //信息框
            brush.setColor(QColor(0, 0, 0, 200));
            zoomPainter.setBrush(brush);
            zoomPainter.drawRect(x + 10, y - 30, 100, 30);
            m_infoFirstRect = QRect(x + 10, y - 30, 100, 15);
            m_infoSecondRect = QRect(x + 10, y - 30 + 15, 100, 15);
            pen.setColor(QColor(255, 255, 255));
            zoomPainter.setPen(pen);
            zoomPainter.setFont(font);
            zoomPainter.drawText(m_infoFirstRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 x %2").arg(width).arg(height));
            zoomPainter.drawText(m_infoSecondRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("RGB(%1,%2,%3)").arg(red).arg(green).arg(blue));
        }
        else if (m_pScreenJudge->zoomJudge() == ZOOMJUDGE_RIGHTUP){
            zoomPainter.drawPixmap(x - 110, y + 10, 100, 100, m_pixMap);
            pen.setColor(QColor(0, 255, 0, 125));
            pen.setWidthF(3);
            zoomPainter.setPen(pen);
            zoomPainter.drawLine(x - 60, y + 15, x - 60, y + 10 + 95);
            zoomPainter.drawLine(x - 105, y + 10 + 50, x - 15, y + 10 + 50);
            pen.setColor(QColor(0, 0, 0));
            pen.setWidth(1);
            zoomPainter.setPen(pen);
            zoomPainter.drawRect(x - 110, y + 10, 100, 100);
            //信息框
            brush.setColor(QColor(0, 0, 0, 200));
            zoomPainter.setBrush(brush);
            zoomPainter.drawRect(x - 110, y + 110, 100, 30);
            m_infoFirstRect = QRect(x - 110, y + 110, 100, 15);
            m_infoSecondRect = QRect(x - 110, y + 110 + 15, 100, 15);
            pen.setColor(QColor(255, 255, 255));
            zoomPainter.setPen(pen);
            zoomPainter.setFont(font);
            zoomPainter.drawText(m_infoFirstRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 x %2").arg(width).arg(height));
            zoomPainter.drawText(m_infoSecondRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("RGB(%1,%2,%3)").arg(red).arg(green).arg(blue));
        }
        else if (m_pScreenJudge->zoomJudge() == ZOOMJUDGE_RIGHTDOWN){
            zoomPainter.drawPixmap(x - 110, y - 130, 100, 100, m_pixMap);
            pen.setColor(QColor(0, 255, 0, 125));
            pen.setWidthF(3);
            zoomPainter.setPen(pen);
            zoomPainter.drawLine(x - 60, y - 125, x - 60, y - 35);
            zoomPainter.drawLine(x - 105, y - 80, x - 15, y - 80);
            pen.setColor(QColor(0, 0, 0));
            pen.setWidth(1);
            zoomPainter.setPen(pen);
            zoomPainter.drawRect(x - 110, y - 130, 100, 100);
            //信息框
            brush.setColor(QColor(0, 0, 0, 200));
            zoomPainter.setBrush(brush);
            zoomPainter.drawRect(x - 110, y - 30, 100, 30);
            m_infoFirstRect = QRect(x - 110, y - 30, 100, 15);
            m_infoSecondRect = QRect(x - 110, y - 30 + 15, 100, 15);
            pen.setColor(QColor(255, 255, 255));
            zoomPainter.setPen(pen);
            zoomPainter.setFont(font);
            zoomPainter.drawText(m_infoFirstRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 x %2").arg(width).arg(height));
            zoomPainter.drawText(m_infoSecondRect, Qt::AlignHCenter | Qt::AlignVCenter, QString("RGB(%1,%2,%3)").arg(red).arg(green).arg(blue));
        }
    }
    if(m_bIsSelectDrawShape)
    {
        QPainter* painter = new QPainter(this);
        painter->begin(this);
        painter->setPen(QPen(Qt::red, 2, Qt::SolidLine));         //设置画笔形式 
        // m_pPainter->setBrush(QBrush(Qt::red, Qt::SolidPattern));    //设置画刷形式 
        int lefttopPosX = m_ptReleasedPos.x() < m_ptPressedPos.x() ? m_ptReleasedPos.x() : m_ptPressedPos.x();
        int lefttopPosY = m_ptReleasedPos.y() < m_ptPressedPos.y() ? m_ptReleasedPos.y() : m_ptPressedPos.y();
        int width = abs(m_ptReleasedPos.x() - m_ptPressedPos.x());
        int height = abs(m_ptReleasedPos.y() - m_ptPressedPos.y());
        painter->drawRect(lefttopPosX, lefttopPosY, width, height);
        painter->end();
    }
	*/
}
