#include "screenjudge.h"
#include <QDebug>

CScreenJudge::CScreenJudge()
{
}

CScreenJudge::CScreenJudge(int width,int height, QPoint pos)
{
    m_iWidth = width;
    m_iHeight = height;
    m_mousePoint = pos;
    m_iDrawHeight = 0;
    m_iDrawWidth = 0;
}

void CScreenJudge::setStartPoint(QPoint pos)
{
    m_startPoint = pos;
}

void CScreenJudge::setEndPoint(QPoint pos)
{
    m_endPoint = pos;
    setDragPoint();//初始化九个点
    updateDrawWidth();//刷新宽
    updateDrawHeight();//刷新高
    updateDrawRect();//返回可靠矩形
}

void CScreenJudge::updateDrawRect()
{
    m_drawRect = QRect(m_westNorthPoint,m_eastSouthPoint);
}

void CScreenJudge::updateDrawWidth()
{
    //drawWidth = endPoint.x() - startPoint.x();
    m_iDrawWidth = m_eastSouthPoint.x() - m_westNorthPoint.x();
}

void CScreenJudge::updateDrawHeight()
{
    //drawHeight = endPoint.y() - startPoint.y();
    m_iDrawHeight = m_eastSouthPoint.y() - m_westNorthPoint.y();
}

int CScreenJudge::drawWidth()
{
    return m_iDrawWidth;
}

int CScreenJudge::drawHeight()
{
    return m_iDrawHeight;
}

bool CScreenJudge::isInDrawArea(QPoint pos)
{
    if( pos.x() > m_westNorthPoint.x() && pos.x() < m_eastSouthPoint.x() && pos.y() > m_westNorthPoint.y() && pos.y() < m_eastSouthPoint.y() )
        return true;

    return false;
}

QRect CScreenJudge::drawRect()
{
    return m_drawRect;
}

void CScreenJudge::cmpPoint(QPoint &LeftUpPoint, QPoint &RightDownPoint)
{
    QPoint L = LeftUpPoint;
    QPoint R = RightDownPoint;
    if( L.x() <= R.x()  )  //起点在终点左侧
    {
        if( L.y() <= R.y() ) //左上
        {
        }
        else              //左下
        {
            LeftUpPoint.setY(R.y());
            RightDownPoint.setY(L.y());
        }
    }
    else                //在右侧
    {
        if( L.y() < R.y() ) //右上
        {
            LeftUpPoint.setX(R.x());
            RightDownPoint.setX(L.x());
        }
        else             //右下
        {
            QPoint tmp;
            tmp = LeftUpPoint;
            LeftUpPoint = RightDownPoint;
            RightDownPoint = tmp;
        }
    }
}

bool CScreenJudge::isInDragLine(QPoint pos)
{
    if( pos.x() >= m_westNorthPoint.x() && pos.x() <= m_eastSouthPoint.x() && pos.y() >= m_westNorthPoint.y() && pos.y() <= m_eastSouthPoint.y() )
    {
        if(pos.x() == m_westNorthPoint.x() || pos.x() == m_eastSouthPoint.x() || pos.y() == m_westNorthPoint.y() || pos.y() == m_eastSouthPoint.y())
        {
            return true;
        }
    }
    return false;
}

void CScreenJudge::setDragPoint()
{
    m_westNorthPoint = m_startPoint;
    m_eastSouthPoint = m_endPoint;
    cmpPoint(m_westNorthPoint,m_eastSouthPoint);
    int x1,y1,x2,y2,x3,y3;
    x1 = m_westNorthPoint.x();
    y1 = m_westNorthPoint.y();
    x2 = m_eastSouthPoint.x();
    y2 = m_eastSouthPoint.y();
    x3 = (x1+x2)/2;
    y3 = (y1+y2)/2;

    m_eastPoint = QPoint(x2,y3);
    m_westPoint = QPoint(x1,y3);
    m_southPoint = QPoint(x3,y2);
    m_northPoint = QPoint(x3,y1);
    m_eastNorthPoint = QPoint(x2,y1);
    m_westSouthPoint = QPoint(x1,y2);

}

DragJudge CScreenJudge::dragJudge(QPoint pos)
{
    if(pos == m_eastNorthPoint){
        //qDebug()<< "1";
        return DRAGJUDGE_EASTNORTH;
    }
    else if(pos == m_eastSouthPoint){
        //qDebug()<< "2";
        return DRAGJUDGE_EASTSOUTH;
    }
    else if(pos == m_westNorthPoint){
        //qDebug()<< "3";
        return DRAGJUDGE_WESTNORTH;
    }
    else if(pos == m_westSouthPoint){
        //qDebug()<< "4";
        return DRAGJUDGE_WESTSOUTH;
    }
    else if(pos.x() == m_westNorthPoint.x()){
        //qDebug()<< "5";
        return DRAGJUDGE_WEST;
    }
    else if(pos.y() == m_westNorthPoint.y()){
        //qDebug()<< "6";
        return DRAGJUDGE_NORTH;
    }
    else if(pos.x() == m_eastSouthPoint.x()){
        //qDebug()<< "7";
        return DRAGJUDGE_EAST;
    }
    else if(pos.y() == m_eastSouthPoint.y()){
        //qDebug()<< "8";
        return DRAGJUDGE_SOUTH;
    }
	return DRAGJUDGE_NULL;
}

QPoint CScreenJudge::eastPoint()
{
    return m_eastPoint;
}

QPoint CScreenJudge::westPoint()
{
    return m_westPoint;
}

QPoint CScreenJudge::southPoint()
{
    return m_southPoint;
}

QPoint CScreenJudge::northPoint()
{
    return m_northPoint;
}

QPoint CScreenJudge::eastSouthPoint()
{
    return m_eastSouthPoint;
}

QPoint CScreenJudge::eastNorthPoint()
{
    return m_eastNorthPoint;
}

QPoint CScreenJudge::westSouthPoint()
{
    return m_westSouthPoint;
}

QPoint CScreenJudge::westNorthPoint()
{
    return m_westNorthPoint;
}

void CScreenJudge::moveTo(QPoint pos)
{
    int Lx = m_westNorthPoint.x() + pos.x();
    int Ly = m_westNorthPoint.y() + pos.y();
    int Rx = m_eastSouthPoint.x() + pos.x();
    int Ry = m_eastSouthPoint.y() + pos.y();

    //qDebug()<<"左上右下的位置："<<Lx<<","<<Ly<<","<<Rx<<","<<Ry;

    ////保障机制
    if( Lx<0 )
    {
        Lx = 0;
        Rx -= pos.x();
    }
    if( Ly<0 )
    {
        Ly = 0;
        Ry -= pos.y();
    }
    if( Rx>m_iWidth)
    {
        Rx = m_iWidth;
        Lx -= pos.x();
        /*qDebug()<<"左上右下的位置："<<Lx<<","<<Ly<<","<<Rx<<","<<Ry;*/
    }
    if( Ry>m_iHeight )
    {
        Ry = m_iHeight;
        Ly -= pos.y();
        /*qDebug()<<"左上右下的位置："<<Lx<<","<<Ly<<","<<Rx<<","<<Ry;*/
    }
    /*
    if(Rx == Width || Ry == Height)
    {
        if(Rx == Width && Ry == Height)
            {
                setstartPoint(QPoint(Lx,Ly));
                setendPoint(QPoint(Rx-1,Ry-1));
            }else if(Rx == Width)
            {
                setstartPoint(QPoint(Lx,Ly));
                setendPoint(QPoint(Rx-1,Ry));
            }else if(Ry == Height)
            {
                setstartPoint(QPoint(Lx,Ly));
                setendPoint(QPoint(Rx,Ry-1));
            }
    }else{
        setstartPoint(QPoint(Lx,Ly));
        setendPoint(QPoint(Rx,Ry));
    }
    */
    setStartPoint(QPoint(Lx,Ly));
    setEndPoint(QPoint(Rx,Ry));
}

void CScreenJudge::setMousePoint(QPoint pos)
{
    m_mousePoint = pos;
}

QPoint CScreenJudge::mousePoint()
{
    return m_mousePoint;
}

ZoomJudge CScreenJudge::zoomJudge()
{
    if(m_mousePoint.x() < m_iWidth - 150 && m_mousePoint.y() < m_iHeight -150){
        return ZOOMJUDGE_LEFTUP;
    }else if(m_mousePoint.x() > m_iWidth - 150 && m_mousePoint.y() > m_iHeight -150){
        return ZOOMJUDGE_RIGHTDOWN;
    }else if(m_mousePoint.x() >= m_iWidth - 150){
        return ZOOMJUDGE_RIGHTUP;
    }else if(m_mousePoint.y() >= m_iHeight -150){
        return ZOOMJUDGE_LEFTDOWN;
    }
	return ZOOMJUDGE_NULL;
}

ZoomJudge CScreenJudge::infoJudge()
{
    if(m_eastNorthPoint.y() <= 30){
        return ZOOMJUDGE_LEFTUP;
    }
    return ZOOMJUDGE_LEFTDOWN;
}

DragJudge CScreenJudge::btnJudge()
{
    if(m_eastNorthPoint.y() < 30 && m_eastSouthPoint.y() +40 > m_iHeight)
    {
        return DRAGJUDGE_INSIDE;
    }else if(m_eastNorthPoint.y() < 30)
    {
        return DRAGJUDGE_SOUTH;
    }else if(m_eastSouthPoint.y() +40 > m_iHeight)
    {
        return DRAGJUDGE_NORTH;
    }
    return DRAGJUDGE_SOUTH;
}


