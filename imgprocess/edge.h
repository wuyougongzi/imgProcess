#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    //explicit Edge(QObject *parent = 0);

    Edge(Node *sourceNodem, Node *destNode);
    Node *sourceNode() const;
    Node * destNode() const;

    void adjust();

    enum {Type = UserType + 2};

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Node *source;
    Node *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;

};

#endif // EDGE_H
