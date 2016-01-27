#include "hotkeytabledialog.h"
#include "ui_hotkeytabledialog.h"
#include <QKeyEvent>

HotKeyTableDialog::HotKeyTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HotKeyTableDialog)
{
    ui->setupUi(this);
}

HotKeyTableDialog::~HotKeyTableDialog()
{
    delete ui;
}

//捕获所有键盘消息
void HotKeyTableDialog::keyPressEvent(QKeyEvent *keyEvent)
{
    //if(keyEvent->modifiers() )
    //toodo:添加
    //keyEvent.
    //keyEvent->
    //QString text = keyEvent->text();
    //int k = keyEvent->count();
}