#include "screentoolbar.h"
#include "ui_screentoolbar.h"
//#include <QClipboard>

ScreenToolBar::ScreenToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenToolBar)
{
    ui->setupUi(this);
	connect(ui->btnFinish, SIGNAL(clicked()), this, SLOT(onBtnFinishClicked()));
	connect(ui->btnCancal, SIGNAL(clicked()), this, SLOT(onBtnCancalClicked()));
	connect(ui->btnRect, SIGNAL(clicked()), this, SLOT(onBtnRectClicked()));
	connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
		
}

ScreenToolBar::~ScreenToolBar()
{
    delete ui;
}

void ScreenToolBar::onBtnCancalClicked()
{
	emit selectCancal();
}

void ScreenToolBar::onBtnFinishClicked()
{
	emit selectFinish();
}

void ScreenToolBar::onBtnRectClicked()
{
	emit selectRect();
}

void ScreenToolBar::onBtnSaveClicked()
{
	emit selectSave();
}
