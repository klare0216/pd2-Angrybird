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

    esc_pixmap.setPixmap(QPixmap(":/image/esc.png"));
    esc_pixmap.setTransformationMode(Qt::SmoothTransformation);
    esc_pixmap.setPos(QPointF(100,5));
    scene->addItem(&esc_pixmap);

    r_pixmap.setPixmap(QPixmap(":/image/R.png"));
    r_pixmap.setTransformationMode(Qt::SmoothTransformation);
    r_pixmap.setPos(QPointF(150,5));
    scene->addItem(&r_pixmap);

    // Set scoreBar
    {
        QString text;
        text = "SCORE : 0";
        QFont font;
        font.setPixelSize(30);
        font.setFamily("Courier");
        scoreBar.setPos(1020,2);
        scoreBar.setPlainText(text);
        scoreBar.setFont(font);
        scene->addItem(&scoreBar);
    }

    // Set Message
    {
        //QString text;
        //text = "SCORE : 0";
        QFont font;
        font.setPixelSize(60);
        font.setFamily("Courier");
        message.setPos(800,300);
        //message.setPlainText(text);
        message.setFont(font);
        scene->addItem(&message);
    }


    // connect
    connect(timer, SIGNAL(timeout()), this, SLOT(Floating()));

}

void BackGround::rPress(bool flag)
{
       if (flag) r_pixmap.setPixmap(QPixmap(":/image/R_press.png"));
       else r_pixmap.setPixmap(QPixmap(":/image/R.png"));
       r_pixmap.resetTransform();
        //scene->addItem(&r_pixmap);
}

void BackGround::escPress(bool flag)
{
    if (flag) esc_pixmap.setPixmap(QPixmap(":/image/esc_press.png"));
    else esc_pixmap.setPixmap(QPixmap(":/image/esc.png"));
    esc_pixmap.resetTransform();
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

void BackGround::win()
{

    std::stringstream ss;
    QString q_text;
    char text[100] ;
    ss << "WIN  va_av"<< std::endl;
    ss >> text;
    q_text = text;
    q_text += " ";
    ss >> text;
    q_text += text;
    message.setPlainText(q_text);
}

void BackGround::gameover()
{
        std::stringstream ss;
        QString q_text;
        char text[100] ;
        ss << "GG~  va_av"<< std::endl;
        ss >> text;
        q_text = text;
        q_text += " ";
        ss >> text;
        q_text += text;
        message.setPlainText(q_text);
}
