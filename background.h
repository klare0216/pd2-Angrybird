#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <sstream>

#include <QPainter>
#include <QTimer>


class BackGround : public QObject
{
    Q_OBJECT
public:
    BackGround(QTimer *timer,QGraphicsScene *scene);
    static int *bg_score;
public slots:
    void Floating();
    void update();
private:
    QList<QGraphicsPixmapItem *> cloud;
    QGraphicsPixmapItem aa_pixmap;
    QGraphicsTextItem scoreBar;
};



#endif // BACKGROUND_H
