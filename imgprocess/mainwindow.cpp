#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>
#include "mainwindow.h"
#include "imgprocesscenterwidget.h"
#include "ui_mainwindow.h"


class QMenu;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pCenterWidget = new ImgProcessCenterWidget(this);
    setCentralWidget(m_pCenterWidget);
    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFileAction()));

    //about&help Action
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutAction()));
    connect(ui->actionSaveFile, SIGNAL(triggered()), this, SLOT(saveFileAction()));
    /*
    QMenu* fileMenu =  menuBar()->addMenu(tr("&File"));
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
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "img",
                                                    tr("Image (*.png *.jpg)"));
    //todo:
}

void MainWindow::saveFileAction()
{
    //todo:保存文件
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    "img",
                                                    tr("Image (*.png *.jpg)"));
    //todo:
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
