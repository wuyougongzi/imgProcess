#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include "showpicture.h"

namespace Ui {
class MainWindow;
}

class ImgProcessCenterWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //fileaction
    void openFileAction();
    void saveFileAction();
    void saveFileAsAction();
    //editaction

    //settingaction
    void hotKeySettingAction();
    //about&help action
    void aboutAction();
    void helpOnlineAction();
    void helpOnLocalAction();

private:
    Ui::MainWindow *ui;;
    ImgProcessCenterWidget      *m_pCenterWidget;
};

#endif // MAINWINDOW_H
