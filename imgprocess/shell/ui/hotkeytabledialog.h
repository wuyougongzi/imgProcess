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
    virtual bool winEvent(MSG *message, long *result);

private:
    Ui::HotKeyTableDialog *ui;
};

#endif // HOTKEYTABLEDIALOG_H
