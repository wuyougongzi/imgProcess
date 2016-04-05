/*
qwebkit控件，主要测试一下能否播放视频
//暂时发现播放不了
*/

#include "onlineexplorer.h"
#include "ui_onlineexplorer.h"
#include <QWebSettings>

OnLineExplorer::OnLineExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnLineExplorer)
{
//    QWebSetting *psetting = QWebSetting
    ui->setupUi(this);

    QWebSettings *pSettings = QWebSettings::globalSettings();
    pSettings->setAttribute(QWebSettings::PluginsEnabled, true);
    pSettings->setAttribute(QWebSettings::JavascriptEnabled, true);
    pSettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    pSettings->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    //ui->webView->load(QUrl("http://www.youku.com/"));
}

OnLineExplorer::~OnLineExplorer()
{
    delete ui;
}
