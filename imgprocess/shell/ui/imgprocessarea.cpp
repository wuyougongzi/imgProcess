#include "imgprocessarea.h"
#include "ui_imgprocessarea.h"
#include <QMouseEvent>

ImgProcessArea::ImgProcessArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImgProcessArea),
    m_bIsPainterShape(false),
    m_pShapeType(SHAPERECT)
{
    ui->setupUi(this);

//     this->setAutoFillBackground(true);
//     QPalette pla = this->palette();
//     pla.setBrush(QPalette::Window, QBrush())
   // (palette())
    
    //ui->widgetshowpicture->setStyleSheet("border-image:url(:/showpicture/image/showpicture/whitevein.png);");
    //this->setStyleSheet("border-image:url(:/showpicture/image/showpicture/whitevein.png)");
    m_pPainter = new QPainter(this);
}

ImgProcessArea::~ImgProcessArea()
{
    delete ui;
}

void ImgProcessArea::init(const QPixmap& pixMap)
{

}

void ImgProcessArea::setShapeType(ShapeType shapeType)
{
    m_pShapeType = shapeType;
}

void ImgProcessArea::mousePressEvent(QMouseEvent *pMouseEvent)
{
    m_bIsPainterShape = true;
    m_ptMousePress = pMouseEvent->pos();
}

void ImgProcessArea::mouseReleaseEvent(QMouseEvent *pMouseEvent)
{
    //m_bIsPainterShape = false;
    //m_ptMousePress
}

void ImgProcessArea::mouseMoveEvent(QMouseEvent *pMouseEvent)
{
    m_ptCurrentPos = pMouseEvent->pos();

}
// 
void ImgProcessArea::paintEvent(QPaintEvent *event)
{
    if(m_bIsPainterShape)
    {
        //todo:要把这些移到showpitcutre的绘图区
        m_pPainter->begin(this);
        m_pPainter->setPen(QPen(Qt::red, 2, Qt::SolidLine));         //设置画笔形式 
        // m_pPainter->setBrush(QBrush(Qt::red, Qt::SolidPattern));    //设置画刷形式 
        switch(m_pShapeType)
        {
        case SHAPERECT:
            {
                int lefttopPosX = m_ptCurrentPos.x() < m_ptMousePress.x() ? m_ptCurrentPos.x() : m_ptMousePress.x();
                int lefttopPosY = m_ptCurrentPos.y() < m_ptMousePress.y() ? m_ptCurrentPos.y() : m_ptMousePress.y();
                int width = abs(m_ptCurrentPos.x() - m_ptMousePress.x());
                int height = abs(m_ptCurrentPos.y() - m_ptMousePress.y());
                m_pPainter->drawRect(lefttopPosX, lefttopPosY, width, height);
            }
            break;
        case SHAPELINE:
            {
                m_pPainter->drawLine(m_ptMousePress, m_ptCurrentPos);
            }
            break;
        case SHAPEECLIPSE:
            {
                QPoint centerPt = (m_ptMousePress + m_ptCurrentPos) / 2;
                int rx = abs(m_ptCurrentPos.x() - m_ptMousePress.x()) / 2;
                int ry = abs(m_ptCurrentPos.y() - m_ptMousePress.y()) / 2;
                m_pPainter->drawEllipse(centerPt, rx, ry);
            }
            break;
        }
        
        
        m_pPainter->end();
    }
    update();
 //   QWidget::paintEvent(event);
}
