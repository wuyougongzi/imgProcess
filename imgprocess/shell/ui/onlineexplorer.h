#ifndef ONLINEEXPLORER_H
#define ONLINEEXPLORER_H

#include <QWidget>

namespace Ui {
class OnLineExplorer;
}

class OnLineExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit OnLineExplorer(QWidget *parent = 0);
    ~OnLineExplorer();

private:
    Ui::OnLineExplorer *ui;
};

#endif // ONLINEEXPLORER_H
