#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Node(QObject *parent = 0);
    Node(GraphWidget *graphWidget);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum{ Type = UserType + 1};
    int type() const;
    void calculateForces();
    bool advance();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<Edge*> edgeList;
    QPointF newPos;
    GraphWidget *graph;

};

#endif // NODE_H
