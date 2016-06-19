#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    score(0),
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

    // Set background
    background = new BackGround(&timer, scene);
    BackGround::bg_score = &score;

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
    itemList.push_back(new Land(1250 / 2, 500 + 300 / 2,1250, 300,":/image/uncle_land.png",world,scene));
    itemList.push_back(new Land(50, 290, 100, 10,":/image/none.png",world,scene));
    itemList.push_back(new Land(105, 190, 10, 200,":/image/none.png",world,scene));
        // Create barrier
    for (int i = 0;i < 5;++i)
    {
            itemList.push_back(new Barrier(700 + 100*i, 470, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));
    }
    itemList.push_back(new Barrier(800, 345, 150, 6, 0.0f, &timer,":/image/barrier_l.png",world,scene));
    itemList.push_back(new Barrier(1000, 345, 150, 6, 0.0f, &timer,":/image/barrier_l.png",world,scene));
    itemList.push_back(new Barrier(1000, 300, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(1000, 250, 70, 30, 0.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(1000, 210, 70, 30, 0.0f, &timer,":/image/barrier_wood.png",world,scene));

    itemList.push_back(new Barrier(400, 460, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(400, 390, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(400, 320, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));

    itemList.push_back(new Barrier(500, 483, 70, 30, 0.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(530, 431, 150, 6, 0.0f, &timer,":/image/barrier_l.png",world,scene));
    itemList.push_back(new Barrier(500, 421, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));
    itemList.push_back(new Barrier(500, 352, 70, 30, 90.0f, &timer,":/image/barrier_wood.png",world,scene));



        //Create pig
    Enemy::e_score = &score;
    Enemy::list_ptr = &EnemyList;
    EnemyList.push_back(new Enemy(550, 425, 23, &timer, ":/image/pig.png", world, scene));
    EnemyList.push_back(new Enemy(400, 290, 23, &timer, ":/image/pig.png", world, scene));
    for(int i = 0 ;i < 4;++i)
    {
       EnemyList.push_back(new Enemy(750 + 100*i, 523, 23, &timer, ":/image/pig.png", world, scene));
    }
    EnemyList.push_back(new Enemy(800, 320, 23, &timer, ":/image/pig.png", world, scene));
        // Create bird
    birdList.push_back(new BirdWhite(50, 190, 23, &timer, ":/image/white_bird.png", world,scene));
    birdList.push_back(new BirdBlack(50, 110, 23, &timer,  ":/image/black_bird.png", world,scene));
    birdList.push_back(new BirdBlue(50, 70, 23, &timer,  ":/image/blue_bird.png", world,scene));
    birdList.push_back(new BirdGreen(50, 30, 23, &timer, ":/image/green_bird.png", world,scene));
    birdList.push_back(new BirdYellow(50, 20, 23, &timer, ":/image/yellow_bird_2.png", world,scene));
    birdList.push_back(new Bird(50, 20, 23, &timer, ":/image/red_bird.png", world,scene));

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(&timer,SIGNAL(timeout()),background,SLOT(update()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    connect(this,SIGNAL(Restart()),this,SLOT(restart()));
    connect(this,SIGNAL(gameOver()),this,SLOT(GAMEOVER()));
    connect(this,SIGNAL(win()),this,SLOT(WIN()));

    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    int type = event->type();
    Bird * birdie = NULL;

    if (!birdList.isEmpty())
        birdie = static_cast<Bird *>(birdList.last());

    if (type == QEvent::KeyPress)
    {
        QKeyEvent  * key_event = static_cast<QKeyEvent *>(event);
        if (key_event->key() == Qt::Key_Space)
        {
            std::cout << "space press! " << std::endl;
            if(birdie)
                birdie->useSkill();
            return true;
        }
        if (key_event->key() == Qt::Key_R)
        {
            std::cout << "R press! " << std::endl;
            emit Restart();
            return true;
        }
        if (key_event->key() == Qt::Key_Escape)
        {
            std::cout << "esc press! " << std::endl;
            emit quitGame();
            return true;
        }
    }

    if(event->type() == QEvent::MouseButtonPress)
    {
        //std::cout << "Press !" << std::endl ;
        QMouseEvent * e_mouse = static_cast<QMouseEvent *>(event);
        int  e_x = e_mouse->pos().x();
        int  e_y = e_mouse->pos().y();

        if (e_x > 100 && e_x < 150 && e_y<50)
        {
            background->escPress(true);
        } else if(e_x > 150 && e_x < 200 && e_y<50)
        {
            background->rPress(true);
        } else if (!hasBird && (!birdList.isEmpty()) && isStart)
        {
            birdList.removeOne(birdie);
            Enemy::add_score = Enemy::add_score - 1;
        }
        return true;
    }

    if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent * e_mouse = static_cast<QMouseEvent *>(event);
        if (hasBird)
            birdie->setPos(e_mouse->pos().rx(), e_mouse->pos().ry());
        return true;
     }

    if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent * e_mouse = static_cast<QMouseEvent *>(event);
        int  e_x = e_mouse->pos().x();
        int  e_y = e_mouse->pos().y();

         background->rPress(false);
        background->escPress(false);

        if (e_x > 100 && e_x < 150 && e_y<50)
        {
            emit quitGame();
        } else if(e_x > 150 && e_x < 200 && e_y<50)
        {
            emit restart();
        } else if (birdie != NULL)
        {
            hasBird = (hasBird) ? false : true;
            isStart = true;
            birdie->setAwake(!hasBird);
            if (hasBird)
            {
                birdie->setPos(200,375);
            } else {
                birdie->setLinearVelocity(e_mouse->pos().rx() , e_mouse->pos().ry());
                birdie->setIsDone(true);
                if (birdList.length() == 1)
                    emit gameOver();
            }
        }
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
    if (EnemyList.isEmpty())
    {
        emit win();
    }
    if (birdList.isEmpty())
        emit gameOver();

}

void MainWindow::restart()
{
    std::cout << "Performing application reboot..." << std::endl ;
    qApp->exit( MainWindow::EXIT_CODE_REBOOT );
}

void MainWindow::GAMEOVER()
{
        std::cout << "gameover" << std::endl;
         background->gameover();
}

void MainWindow::WIN()
{
         std::cout << "win" << std::endl ;
         background->win();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
    qApp->exit(0);
}
