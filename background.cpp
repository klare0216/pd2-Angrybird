#include "background.h"

BackGround::BackGround(QTimer *timer, QGraphicsScene *scene)
{
    // Set pixmap
    for (int i = 0;i < 5;++i)
    {
        cloud.push_back(new QGraphicsPixmapItem());
        cloud.last()->setPos(QPointF(0,0));
        cloud.last()->setTransformationMode(Qt::SmoothTransformation);
        scene->addItem(cloud.last());
    }
    cloud[4]->setPixmap(QPixmap(":/image/cloud_0.png"));
    cloud[3]->setPixmap(QPixmap(":/image/cloud_2.png"));
    cloud[2]->setPixmap(QPixmap(":/image/cloud_1.png"));
    cloud[1]->setPixmap(QPixmap(":/image/cloud_3.png"));
    cloud[0]->setPixmap(QPixmap(":/image/cloud_4.png"));

    aa_pixmap.setPixmap(QPixmap(":/image/aa.png"));
    aa_pixmap.setTransformationMode(Qt::SmoothTransformation);
    aa_pixmap.setPos(QPointF(185,380));
    scene->addItem(&aa_pixmap);

    // Set scoreBar
    QString text;
    text = "SCORE : 0";
    QFont font;
    font.setPixelSize(30);
    font.setFamily("Courier");
    scoreBar.setPos(1020,2);
    scoreBar.setPlainText(text);
    scoreBar.setFont(font);

    scene->addItem(&scoreBar);

    // connect
    connect(timer, SIGNAL(timeout()), this, SLOT(Floating()));

}

void BackGround::Floating()
{
    cloud[0]->setPos( (cloud[0]->x() > 1250) ?  -1250 : cloud[0]->x() + 0.5, cloud[0]->y());
    cloud[1]->setPos( (cloud[1]->x() > 1250) ?  -1250 : cloud[1]->x() + 1, cloud[0]->y());
    cloud[2]->setPos( (cloud[2]->x() > 1250) ?  -1250 : cloud[2]->x() + 0.75, cloud[0]->y());
    cloud[3]->setPos( (cloud[3]->x() < 1250) ?  -1250 : cloud[3]->x()  + 0.25, cloud[0]->y());
    //cloud[4]->setPos( (cloud[4]->x() > 1250) ?  -1250 : cloud[4]->x() + 1, cloud[0]->y());
    for (int i = 0;i < cloud.length() - 1; ++i)
        cloud[i]->resetTransform();
}

int *BackGround::bg_score = NULL;

void BackGround::update()
{
    std::stringstream ss;
    QString q_text;
    char text[100] ;
    ss << "SCORE:" << *bg_score << std::endl;
    ss >> text;
    q_text = text;

    scoreBar.setPlainText(q_text);
}
