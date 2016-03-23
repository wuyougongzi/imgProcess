/*
qwebkit控件，主要测试一下能否播放视频
//暂时发现播放不了
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
