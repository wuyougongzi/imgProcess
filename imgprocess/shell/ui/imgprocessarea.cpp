#include "imgprocessarea.h"
#include "ui_imgprocessarea.h"
#include <QMouseEvent>

ImgProcessArea::ImgProcessArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImgProcessArea)
{
    ui->setupUi(this);

//     this->setAutoFillBackground(true);
//     QPalette pla = this->palette();
//     pla.setBrush(QPalette::Window, QBrush())
   // (palette())
    
    //ui->widgetshowpicture->setStyleSheet("border-image:url(:/showpicture/image/showpicture/whitevein.png);");
    //this->setStyleSheet("border-image:url(:/showpicture/image/showpicture/whitevein.png)");
    m_pPainter = new QPainter(this);
    m_bIsPainterShape = false;
}

ImgProcessArea::~ImgProcessArea()
{
    delete ui;
}

void init(const QPixmap& pixMap)
{

}

void ImgProcessArea::mousePressEvent(QMouseEvent *pMouseEvent)
{
    m_bIsPainterShape = true;
    m_ptMousePress = pMouseEvent->pos();
}

void ImgProcessArea::mouseReleaseEvent(QMouseEvent *pMouseEvent)
{
    //m_bIsPainterShape = false;
}

void ImgProcessArea::mouseMoveEvent(QMouseEvent *pMouseEvent)
{
    m_ptCurrentPos = pMouseEvent->pos();



}

void ImgProcessArea::paintEvent(QPaintEvent *)
{
    if(m_bIsPainterShape)
    {
        //todo:Ҫ����Щ�Ƶ�showpitcutre�Ļ�ͼ��
        m_pPainter->begin(this);
        m_pPainter->setPen(QPen(Qt::red, 2, Qt::SolidLine));         //���û�����ʽ 
        // m_pPainter->setBrush(QBrush(Qt::red, Qt::SolidPattern));    //���û�ˢ��ʽ 
        int lefttopPosX = m_ptCurrentPos.x() < m_ptMousePress.x() ? m_ptCurrentPos.x() : m_ptMousePress.x();
        int lefttopPosY = m_ptCurrentPos.y() < m_ptMousePress.y() ? m_ptCurrentPos.y() : m_ptMousePress.y();
        int width = abs(m_ptCurrentPos.x() - m_ptMousePress.x());
        int height = abs(m_ptCurrentPos.y() - m_ptMousePress.y());
        m_pPainter->drawRect(lefttopPosX, lefttopPosY, width, height);
        m_pPainter->end();
    }
    update();
}