#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
//#include "showpicure.h"

namespace Ui {
class MainWindow;
class showPicture;
}

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

    //about&help action
    void aboutAction();
    void helpOnlineAction();
    void helpOnLocalAction();

   //for test
private slots:
    void okClick();
    void cancalClick();

public:
    /*
     *
    */
private:
    Ui::MainWindow *ui;
 //   Ui::showPicture *m_showPitcure;
  //  ShowPicure* m_showPicture;
};

#endif // MAINWINDOW_H
