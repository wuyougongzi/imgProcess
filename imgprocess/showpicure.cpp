#include "showpicure.h"
#include "ui_showPicure.h"
#include <QMessageBox>
#include <QGraphicsScene>

ShowPicure::ShowPicure(QWidget *parent) :
    QWidget(parent),
    m_showPicture(new Ui::showPicture)
{
    m_showPicture->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene;

    scene->addPixmap(QPixmap(":/image/cat.jpg"));

    m_showPicture->graphicsView->setScene(scene);
 //   m_showPicture->graphicsView->resize(image->width() + 10, image->height() + 10);
    //ui->graphicsView->show();

   // m_showPicture->graphicsView
   // connect(m_showPicture->testButton, SIGNAL(clicked()), this, SLOT(testButtonClick()));
}


void ShowPicure::testButtonClick()
{
    QMessageBox box;
    box.setText("test Button click");
    box.exec();
}
