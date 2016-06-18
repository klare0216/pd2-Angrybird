#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hasBird(false),
    isStart(false),
    bullet_num(0)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
   // delete contactListener;
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    std::cout << width() << " , " << height() << std::endl;
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    // World
        // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
        // Setting world
    contactListener = new abContactListener();
    world->SetContactListener(contactListener);

    // Setting Size
    GameItem::setGlobalSize(QSizeF(32, 18),size());

    // Create GameItem
        // Create ground
    itemList.push_back(new Land(width() / 2, 600 + width() / 2 / 2, width(), width() / 2,":/ground.png",world,scene));
    itemList.push_back(new Land(50, 250, 100, 10,":/image/none.png",world,scene));
    itemList.push_back(new Land(105, 150, 10, 200,":/image/none.png",world,scene));
        //Create pig
    itemList.push_back(new Enemy(550, 390, 23, &timer, ":/image/pig.png", world, scene));
    itemList.push_back(new Enemy(550, 310, 23, &timer, ":/image/pig.png", world, scene));
        // Create barrier
    itemList.push_back(new Barrier(500, 390, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(600, 390, 70, 30, 90.0f,  &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(550, 345, 150, 6, 0.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(500, 310, 70, 30, 90.0f,  &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(600, 310, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(550, 305, 150, 6, 0.0f, &timer,":/image/barrier_wood.png",world,scene));
        // Create bird
    birdList.push_back(new BirdYellow(50, 190, 23, &timer, ":/bird.png", world,scene));
    ++bullet_num;
    birdList.push_back(new BirdYellow(50, 150, 23, &timer,  ":/image/uncle_bird.png", world,scene));
    ++bullet_num;
    birdList.push_back(new BirdYellow(50, 110, 23, &timer,  ":/image/uncle_bird.png", world,scene));
    ++bullet_num;
    birdList.push_back(new BirdWhite(50, 70, 23, &timer,  ":/image/uncle_bird.png", world,scene));
    ++bullet_num;
    birdList.push_back(new BirdWhite(50, 30, 23, &timer, ":/image/87_bird.png", world,scene));
    ++bullet_num;
    birdList.push_back(new BirdWhite(50, 20, 23, &timer, ":/image/87_bird.png", world,scene));
    ++bullet_num;
    birdList.push_back(new BirdWhite(50, 20, 23, &timer, ":/image/87_bird.png", world,scene));
    ++bullet_num;

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);


    /* debug
    for (int i = 0;i <= itemList.length() - 1;i++)
    {
        itemList[i]->deBug();
    }
    */
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    int type = event->type();

    if (type == QEvent::KeyPress)
    {
        QKeyEvent  * key_event = static_cast<QKeyEvent *>(event);
        if (key_event->key() == Qt::Key_Space)
        {
            std::cout << "space press! " << std::endl;
            static_cast<Bird *>(birdList.last())->useSkill();
            return true;
        }
    }

    if(event->type() == QEvent::MouseButtonPress)
    {
        /* TODO : add your code here */
        //std::cout << "Press !" << std::endl ;
        Bird * birdie = static_cast<Bird *>(birdList.last());
        if (!hasBird && bullet_num > 1 && isStart)
        {
            birdList.pop_back();
            birdie->deleteLater();
            --bullet_num;
        }

        return true;
    }

    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        QMouseEvent * e_mouse = static_cast<QMouseEvent *>(event);
        Bird * birdie = static_cast<Bird *>(birdList.last());
        //birdie->deBug();
        //std::cout << birdie << std::endl;
        //birdie->setAwake(!hasBird);
        if (hasBird)
            birdie->setPos(e_mouse->pos().rx(), e_mouse->pos().ry());

        return true;
     }

    if(event->type() == QEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */
        QMouseEvent * e_mouse = static_cast<QMouseEvent *>(event);
        Bird * birdie = static_cast<Bird *>(birdList.last());

        hasBird = (hasBird) ? false : true;
        isStart = true;
        birdie->setAwake(!hasBird);
        if (hasBird)
        {
            birdie->setPos(200,300);
        } else {
            birdie->setLinearVelocity(e_mouse->pos().rx() , e_mouse->pos().ry());
        }

        //std::cout << birdie << std::endl;
        //birdie->deBug();
        //std::cout << "Release !" << std::endl ;
        //std::cout << e_mouse->pos().ry() << std::endl;
        return true;
    }

    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
