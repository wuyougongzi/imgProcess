#ifndef SCREENJUDGE_H
#define SCREENJUDGE_H

#include <QPoint>
#include <QRect>

//zoom�ж��������
enum ZoomJudge{
	ZOOMJUDGE_LEFTUP = 0,
	ZOOMJUDGE_LEFTDOWN,
	ZOOMJUDGE_RIGHTUP,
	ZOOMJUDGE_RIGHTDOWN,
	ZOOMJUDGE_NULL
};

enum DragJudge{
	DRAGJUDGE_EAST = 0,
	DRAGJUDGE_WEST,
	DRAGJUDGE_SOUTH,
	DRAGJUDGE_NORTH,
	DRAGJUDGE_EASTSOUTH,
	DRAGJUDGE_EASTNORTH,
	DRAGJUDGE_WESTSOUTH,
	DRAGJUDGE_WESTNORTH,
	DRAGJUDGE_INSIDE,
	DRAGJUDGE_OUTSIDE,
	DRAGJUDGE_NULL
};

class CScreenJudge
{
public:
    CScreenJudge();
    CScreenJudge(int weight, int height, QPoint pos);

    //draw��������ж�
    void setStartPoint(QPoint pos);
    void setEndPoint(QPoint pos);
    int drawWidth();
    int drawHeight();
    bool isInDrawArea(QPoint pos);
    QRect drawRect();
    //drag��Ļ���
    bool isInDragLine(QPoint pos);
    void setDragPoint();
    DragJudge dragJudge(QPoint pos);
    QPoint eastPoint();
    QPoint westPoint();
    QPoint southPoint();
    QPoint northPoint();
    QPoint eastSouthPoint();
    QPoint eastNorthPoint();
    QPoint westSouthPoint();
    QPoint westNorthPoint();
    void moveTo(QPoint pos);

    //zoom���ж�
    void setMousePoint(QPoint pos);
    QPoint mousePoint();
    ZoomJudge zoomJudge();
    ZoomJudge infoJudge();

    //button�ж�
    DragJudge btnJudge();

private:
    void cmpPoint(QPoint &LeftUpPoint,QPoint &RightDownPoint);//������ô��ͼ�����ǿ�ʼ�ĵ������Ϸ��������ĵ������·�

    void updateDrawRect();
    void updateDrawWidth();
    void updateDrawHeight();
private:
    //draw��
    QPoint      m_startPoint;
    QPoint      m_endPoint;
    QPoint      m_mousePoint;

    QRect       m_drawRect;

    //drag��
    QPoint      m_westNorthPoint;
    QPoint      m_northPoint;
    QPoint      m_eastNorthPoint;
    QPoint      m_westPoint;
    QPoint      m_eastPoint;
    QPoint      m_westSouthPoint;
    QPoint      m_southPoint;
    QPoint      m_eastSouthPoint;

    int         m_iWidth;
    int         m_iHeight;
    int         m_iDrawWidth;
    int         m_iDrawHeight;
};

#endif // SCREENJUDGE_H
