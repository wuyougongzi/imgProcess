#ifndef SCREENTOOLBAR_H
#define SCREENTOOLBAR_H

#include <QWidget>

namespace Ui {
class ScreenToolBar;
}

class ScreenToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenToolBar(QWidget *parent = 0);
    ~ScreenToolBar();

signals:
	void selectRect();
	void selectSave();
	void selectCancal();
	void selectFinish();

private slots:
	void onBtnCancalClicked();
	void onBtnFinishClicked();
	void onBtnRectClicked();
	void onBtnSaveClicked();

private:
    Ui::ScreenToolBar *ui;
};

#endif // SCREENTOOLBAR_H
