/*
qwebkit�ؼ�����Ҫ����һ���ܷ񲥷���Ƶ
//��ʱ���ֲ��Ų���
*/

#include "onlineexplorer.h"
#include "ui_onlineexplorer.h"

OnLineExplorer::OnLineExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnLineExplorer)
{
    ui->setupUi(this);
}

OnLineExplorer::~OnLineExplorer()
{
    delete ui;
}
