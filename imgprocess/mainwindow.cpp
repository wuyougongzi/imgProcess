#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLabel>

class QMenu;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okClick()));
  //  connect(ui->cancalButton, SIGNAL(clicked()), this, SLOT(cancalClick()));

    //todo:menu如何触发事件
    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFileAction()));

    //about&help Action
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutAction()));

    /*  QMenu* fileMenu =  menuBar()->addMenu(tr("&File"));

    openFileAction = new QAction(tr("&OpenFile"), this);
 //   openFileAction->setShortcut(QKeySequence::Open);   //设置快捷键
    openFileAction->setStatusTip(tr("Open a file"));      //设置状态栏
    fileMenu->addAction(openFileAction);
*/
 //test//

 }


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFileAction()
{
    //todo:
    m_pOpenFileDlg = new OpenFileDgl();
    m_pOpenFileDlg->show();
   // m_pOpenFileDlg->update();
}

void MainWindow::saveFileAction()
{
    //todo:保存文件
}

void MainWindow::saveFileAsAction()
{
    //todo:文件保存为
}

void MainWindow::aboutAction()
{
    //todo:显示软件信息
 /*   QLabel* label = new QLabel(NULL);
    label->setText("test");
    label->show();
   */
    //
    QMessageBox::about(this, "about ImgProcess", "Version 0.1");
}

void MainWindow::helpOnlineAction()
{
    //todo:在线帮助文档
    //
}

void MainWindow::helpOnLocalAction()
{
    //todo:本地帮助文档
}

void MainWindow::okClick()
{
    QMessageBox box;
    box.setText("ok test");
    box.exec();
}

void MainWindow::cancalClick()
{
    QMessageBox box;
    box.setText("cancal test");
    box.exec();
}
