/*
ʱ�䣺2016/12/9
����:��������
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
	void isPointInRect(const QPoint &pt);			//���ڻ���������
	void isPointInLeftTopArea(const QPoint &pt);	//�������Ͻ��϶�λ��
	void isPointInUp(const QPoint &pt);				//�����ϱ��ߣ������ϱ����м�ĵ�
	void isPointInRightUp(const QPoint &pt);
	void isPointInRight(const QPoint &pt);
	void isPointInRightDown(const QPoint &pt);
	void isPointInDown(const QPoint &pt);
	void isPointInLeftDown(const QPoint &pt);
	void isPointInLeft(const QPoint &pt);			//��������ߣ�����������м�ĵ�
private:
	QRect m_Rect;
};