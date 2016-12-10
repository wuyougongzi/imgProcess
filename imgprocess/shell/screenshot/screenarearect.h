/*
时间：2016/12/9
功能:绘制区域
*/
#include <QObject>
#include <QRect>

class ScreenAreaRect : public QObject
{
	Q_OBJECT
public:
	ScreenAreaRect(QObject* parent = 0);
	~ScreenAreaRect();

public:
	void setRect(QRect &rect);
	void isPointInRect(const QPoint &pt);			//点在绘制区域内
	void isPointInLeftTopArea(const QPoint &pt);	//点在左上角拖动位置
	void isPointInUp(const QPoint &pt);				//点在上边线，包括上边线中间的点
	void isPointInRightUp(const QPoint &pt);
	void isPointInRight(const QPoint &pt);
	void isPointInRightDown(const QPoint &pt);
	void isPointInDown(const QPoint &pt);
	void isPointInLeftDown(const QPoint &pt);
	void isPointInLeft(const QPoint &pt);			//点在左边线，包括左边线中间的点
private:
	QRect m_Rect;
};