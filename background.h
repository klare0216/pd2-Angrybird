#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QPushButton>
#include <sstream>

#include <QPainter>
#include <QTimer>


class BackGround : public QObject
{
    Q_OBJECT
public:
    BackGround(QTimer *timer,QGraphicsScene *scene);
    static int *bg_score;
    void rPress(bool flag);
    void escPress(bool flag);

public slots:
    void Floating();
    void update();
    void win();
    void gameover();


private:
    QList<QGraphicsPixmapItem *> cloud;
    QGraphicsPixmapItem aa_pixmap;
    QGraphicsPixmapItem esc_pixmap;
    QGraphicsPixmapItem r_pixmap;
    QGraphicsTextItem scoreBar;
    QGraphicsTextItem message;

};



#endif // BACKGROUND_H
