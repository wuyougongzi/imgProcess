#include "showpicure.h"
#include "ui_showPicure.h"
#include <QMessageBox>

ShowPicure::ShowPicure(QWidget *parent) :
    QWidget(parent),
    m_showPicture(new Ui::showPicture)
{
    m_showPicture->setupUi(this);
    connect(m_showPicture->testButton, SIGNAL(clicked()), this, SLOT(testButtonClick()));
}


void ShowPicure::testButtonClick()
{
    QMessageBox box;
    box.setText("test Button click");
    box.exec();
}
