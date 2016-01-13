#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>

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
    openFileAction->setShortcut(QKeySequence::Open);        //设置快捷键
    openFileAction->setStatusTip(tr("Open a file"));        //设置状态栏
    fileMenu->addAction(openFileAction);
*/

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFileAction()
{
    QFileDialog* fileDlg = new QFileDialog(this, Qt::Dialog);
    QString filePath = "C://Users//chongge//Pictures";
    //设置默认打开路径
    fileDlg->setDirectory(filePath);
    //QFileDialog 设置可选文件名后缀
    //可用QStringList设置多个文件名后缀
    fileDlg->setNameFilter(QString("bmp"));
    //设置默认
    fileDlg->setAcceptMode(QFileDialog::AcceptOpen);
    //设置打开的对话框的默认模式
    fileDlg->setViewMode(QFileDialog::List);
    //设置文件路径名称
    fileDlg->setLabelText(QFileDialog::LookIn, QString("open in"));
    //设置文件名的路径
    fileDlg->setLabelText(QFileDialog::FileName, QString("haha"));
    //设置默认文件名称
    fileDlg->selectFile(QString("filenamehaha.bmp"));
    //fileDlg->setNameFilters();
    fileDlg->exec();
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
    QMessageBox::about(this, "about ImgProcess", "Version 0.1");
}

void MainWindow::helpOnlineAction()
{
    //todo:在线帮助文档
    //打开一个网站或者打开一个webkit对话框
}

void MainWindow::helpOnLocalAction()
{
    //todo:本地帮助文档
    //打开一个本地文件
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
