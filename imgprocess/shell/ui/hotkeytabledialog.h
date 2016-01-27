#ifndef HOTKEYTABLEDIALOG_H
#define HOTKEYTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class HotKeyTableDialog;
}

class HotKeyTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HotKeyTableDialog(QWidget *parent = 0);
    ~HotKeyTableDialog();

protected:
    virtual void keyPressEvent(QKeyEvent *) override;

private:
    Ui::HotKeyTableDialog *ui;
};

#endif // HOTKEYTABLEDIALOG_H
