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

//�������м�����Ϣ
void HotKeyTableDialog::keyPressEvent(QKeyEvent *keyEvent)
{
    //if(keyEvent->modifiers() )
    //toodo:���
    //keyEvent.
    //keyEvent->
    //QString text = keyEvent->text();
    //int k = keyEvent->count();
}