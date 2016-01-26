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

ScreenShotImgDlg::ScreenShotImgDlg(QDialog *parent)
	: QDialog(parent)
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
	setMouseTracking(true);
	m_palette.setBrush(QPalette::Background, QBrush(m_fullScreenFogImg));
	setAutoFillBackground(true);
	setPalette(m_palette);

	//初始化,表示整个程序开始运作。
	m_bFirst = true;
	m_bIsdrawing = false;
	m_bIszooming = true;
	m_zoomPoint = QCursor::pos();
	m_bIsdraging = false;
	//初始化类计算
	m_pScreenJudge = QSharedPointer<ScreenJudge>(new ScreenJudge(m_iWidth - 1, m_iHeight - 1, m_zoomPoint));
	
    //矩形画框
    m_pBtnRectangle.setIcon(QIcon(tr(":/screenshot/image/screenshot/srceenshot_rectangle.png")));
    m_pBtnRectangle.setIconSize(QSize(30,30));
    m_pBtnRectangle.setWindowFlags(Qt::FramelessWindowHint);
    m_pBtnRectangle.setAutoRaise(true);
    m_pBtnRectangle.setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(&m_pBtnRectangle, SIGNAL(clicked()), this, SLOT(onBtnDrawRectangle()));

    //保存
    m_pBtnSave.setIcon(QIcon(tr(":/screenshot/image/screenshot/screenshot_save.png")));
    m_pBtnSave.setIconSize(QSize(30, 30));
    m_pBtnSave.setWindowFlags(Qt::FramelessWindowHint);
    m_pBtnSave.setAutoRaise(true);
    m_pBtnSave.setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(&m_pBtnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
    //确认
    m_pBtnSure.setIcon(QIcon(tr(":/screenshot/image/screenshot/screenshot_yes.png")));
    m_pBtnSure.setIconSize(QSize(30, 30));
    m_pBtnSure.setWindowFlags(Qt::FramelessWindowHint);
    m_pBtnSure.setAutoRaise(true);
    m_pBtnSure.setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(&m_pBtnSure, SIGNAL(clicked()), this, SLOT(onBtnSureToClipboardClicked()));
    //取消
    m_pBtnCancle.setIcon(QIcon(tr(":/screenshot/image/screenshot/screenshot_no.png")));
    m_pBtnCancle.setIconSize(QSize(30, 30));
    m_pBtnCancle.setWindowFlags(Qt::FramelessWindowHint);
    m_pBtnCancle.setAutoRaise(true);
    m_pBtnCancle.setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(&m_pBtnCancle, SIGNAL(clicked()), this, SLOT(onBtnCancle()));

    m_bIsSelectDrawShape = false;
    m_CurrentDrawType = DRAWTYPENONE;
}

ScreenShotImgDlg::~ScreenShotImgDlg()
{
}

void ScreenShotImgDlg::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_bFirst)
        {
            m_bFirst = false;
            m_bIsdrawing = true;
        }
        if (m_bIsdrawing)
        {
            m_pScreenJudge->setStartPoint(event->pos());
        }
        if (m_bIsdraging)
        {
            /*
                1 位置在绘图区域内
                2 位置在线上
                3 位置在外面
            */
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
}

    //自己添加的
    m_ptMousePress = event->pos();

}
void ScreenShotImgDlg::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bIsdrawing)
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
    m_ptCurrentPos = event->pos();
	update();
}

void ScreenShotImgDlg::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
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
        update();
    }
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
    //todo:
    //设置当前pen为绘制矩形框的
    m_bIsSelectDrawShape = true;
    m_bIsdraging = false;
    m_CurrentDrawType = DRAWTYPERECTANGLE;

}

void ScreenShotImgDlg::onBtnSureToClipboardClicked()
{
    //写剪贴板
    QClipboard *pClipBoard = QApplication::clipboard();
    pClipBoard->setPixmap(m_pixMap);
    onBtnCancle();
}

void ScreenShotImgDlg::onBtnCancle()
{
    m_pBtnRectangle.close();
	m_pBtnSave.close();
	m_pBtnSure.close();
	m_pBtnCancle.close();
	this->close();
	emit onScreenImgClose();
}

void ScreenShotImgDlg::paintEvent(QPaintEvent *)
{
	if (m_bIsdrawing)
    {
		m_drawRect = m_pScreenJudge->drawRect();
		QPainter drawpainter(this);
		m_drawPix = m_fullScreenPix.copy(m_drawRect);
		drawpainter.drawPixmap(m_drawRect, m_drawPix);
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

        /*
            1 分别作为不同的窗口分别显示的，不方便统一管理
            2 在拖动时几个按钮会出现消失的现象。其实没有消失，显示位置也是正确的
              只是没有显示到屏幕上，切换窗口时能发现。
            3 在功能多的时候更不方便扩展，下面会出现很多小的对话框。
            4 综合以上几点需要把工具栏的按钮重新改造。
        */
		//button
		if (m_pScreenJudge->btnJudge() == DRAGJUDGE_INSIDE)
		{
            m_pBtnRectangle.setGeometry(m_pScreenJudge->eastNorthPoint().x() - 120, m_pScreenJudge->eastSouthPoint().y(), 30, 30);
            m_pBtnRectangle.show();
			m_pBtnSave.setGeometry(m_pScreenJudge->eastNorthPoint().x() - 90, m_pScreenJudge->eastNorthPoint().y(), 30, 30);
			m_pBtnSave.show();
			m_pBtnSure.setGeometry(m_pScreenJudge->eastNorthPoint().x() - 60, m_pScreenJudge->eastNorthPoint().y(), 30, 30);
			m_pBtnSure.show();
			m_pBtnCancle.setGeometry(m_pScreenJudge->eastNorthPoint().x() - 30, m_pScreenJudge->eastNorthPoint().y(), 30, 30);
			m_pBtnCancle.show();
		}
		else if (m_pScreenJudge->btnJudge() == DRAGJUDGE_SOUTH)
		{
            m_pBtnRectangle.setGeometry(m_pScreenJudge->eastSouthPoint().x() - 120, m_pScreenJudge->eastSouthPoint().y(), 30, 30);
            m_pBtnRectangle.show();
			m_pBtnSave.setGeometry(m_pScreenJudge->eastSouthPoint().x() - 90, m_pScreenJudge->eastSouthPoint().y(), 30, 30);
			m_pBtnSave.show();
			m_pBtnSure.setGeometry(m_pScreenJudge->eastSouthPoint().x() - 60, m_pScreenJudge->eastSouthPoint().y(), 30, 30);
			m_pBtnSure.show();
			m_pBtnCancle.setGeometry(m_pScreenJudge->eastSouthPoint().x() - 30, m_pScreenJudge->eastSouthPoint().y(), 30, 30);
			m_pBtnCancle.show();
		}
		else if (m_pScreenJudge->btnJudge() == DRAGJUDGE_NORTH)
		{
            m_pBtnRectangle.setGeometry(m_pScreenJudge->eastNorthPoint().x() - 120, m_pScreenJudge->eastNorthPoint().y(), 30, 30);
            m_pBtnRectangle.show();
			m_pBtnSave.setGeometry(m_pScreenJudge->eastNorthPoint().x() - 90, m_pScreenJudge->eastNorthPoint().y() - 30, 30, 30);
			m_pBtnSave.show();
			m_pBtnSure.setGeometry(m_pScreenJudge->eastNorthPoint().x() - 60, m_pScreenJudge->eastNorthPoint().y() - 30, 30, 30);
			m_pBtnSure.show();
			m_pBtnCancle.setGeometry(m_pScreenJudge->eastNorthPoint().x() - 30, m_pScreenJudge->eastNorthPoint().y() - 30, 30, 30);
			m_pBtnCancle.show();
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
//     if(m_bIsSelectDrawShape)
//     {
//         QPainter* painter = new QPainter(this);
//         painter->begin(this);
//         painter->setPen(QPen(Qt::red, 2, Qt::SolidLine));         //设置画笔形式 
//         // m_pPainter->setBrush(QBrush(Qt::red, Qt::SolidPattern));    //设置画刷形式 
//         int lefttopPosX = m_ptCurrentPos.x() < m_ptMousePress.x() ? m_ptCurrentPos.x() : m_ptMousePress.x();
//         int lefttopPosY = m_ptCurrentPos.y() < m_ptMousePress.y() ? m_ptCurrentPos.y() : m_ptMousePress.y();
//         int width = abs(m_ptCurrentPos.x() - m_ptMousePress.x());
//         int height = abs(m_ptCurrentPos.y() - m_ptMousePress.y());
//         painter->drawRect(lefttopPosX, lefttopPosY, width, height);
//         painter->end();
//     }
}
