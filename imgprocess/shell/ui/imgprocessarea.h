#ifndef IMGPROCESSAREA_H
#define IMGPROCESSAREA_H

#include <QWidget>
#include <QPainter>
#include <QPoint>

namespace Ui {
class ImgProcessArea;
}

enum ShapeType
{
    SHAPENONE,
    SHAPELINE,
    SHAPEPOINTS,
    SHAPEPLOYLINE,
    SHAPEPLOYGON,
    SHAPERECT,
    SHAPEECLIPSE,
    SHAPEPIXMAP,
};

class ImgProcessArea : public QWidget
{
    Q_OBJECT

public:
    explicit ImgProcessArea(QWidget *parent = 0);
    ~ImgProcessArea();

public:
    void init(const QPixmap& pixMap);
    void setShapeType(ShapeType shapeType);

protected:
    virtual void mousePressEvent(QMouseEvent *)         override;
    virtual void mouseReleaseEvent(QMouseEvent *)       override;
    virtual void mouseMoveEvent(QMouseEvent *)          override;
    virtual void paintEvent(QPaintEvent *)              override;

private:
    Ui::ImgProcessArea *ui;

    //ª≠∞Âœ‡πÿ
    //QPen            pen

    QPainter         *m_pPainter;
    bool             m_bIsPainterShape;
    QPoint           m_ptMousePress;
    QPoint           m_ptCurrentPos;
    ShapeType        m_pShapeType;
};

#endif // IMGPROCESSAREA_H
