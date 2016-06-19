#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>


class BackGround : public QObject
{
    Q_OBJECT
public:
    BackGround(QTimer *timer,QGraphicsScene *scene);
public slots:
    void Floating();
private:
    QList<QGraphicsPixmapItem *> cloud;
    QGraphicsPixmapItem aa_pixmap;
};



#endif // BACKGROUND_H
