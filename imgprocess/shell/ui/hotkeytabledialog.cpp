#include "hotkeytabledialog.h"
#include "ui_hotkeytabledialog.h"
#include <Windows.h>


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


bool HotKeyTableDialog::winEvent(MSG *message, long *result)
{
    //�����õ���Ϣ�����õ������hotkeyLineEdit
    switch(message->message)
    {
    case WM_KEYDOWN:
        {
            //todo:
        }
        break;
    case WM_CHAR:
        {
            //todo:
        }
        break;
    case WM_SYSKEYDOWN:
        {

        }
        break;
    case WM_SYSCHAR:
        {

        }
        break;
    }
    return QWidget::winEvent(message, result);
}