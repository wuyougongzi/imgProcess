#ifndef SHOWPICURE_H
#define SHOWPICURE_H

#include <QWidget>

namespace Ui {
class showPicture;
}

class ShowPicure : public QWidget
{
    Q_OBJECT
public:
    explicit ShowPicure(QWidget *parent = 0);

signals:

private slots:
    void testButtonClick();

private:
   Ui::showPicture *m_showPicture;
};

#endif // SHOWPICURE_H
