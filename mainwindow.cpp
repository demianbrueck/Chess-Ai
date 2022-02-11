#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figures.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    chessFieldHeight = 0;
    chessFieldWidth = 0;
    m_amountFigures = 0;
    for(int f=0;f<32;f++){
        m_amountFigures++;
        m_pFigures[f] = new Figures(0,0,(Figures::FIGURE_NAMES)f);
    }
    m_pSysTickTimer = new QTimer(this);
    connect(m_pSysTickTimer, &QTimer::timeout, this, &MainWindow::sysTickTimer);
    activeFigure = 999;
    m_pSysTickTimer->start(1);
    musicPlayer = new QMediaPlayer;

    //ersetzten druch Info on Server
    playingColor = BLACK;
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setBrush(Qt::black);
    //drawing chess field
    chessFieldWidth = 0;
    chessFieldHeight = 0;
    int h;
    h = 0;
    //QPicture
    //painter.drawPicture(50,50,)
    blackFieldColor = false;
    for(int i = 0;i<8;i++){

       for(int j = 0;j<8;j++){



           //if(j!=0){
           if(blackFieldColor == true)painter.setBrush(Qt::darkGray);
           else painter.setBrush(Qt::white);
           //}
           /*else{
               if(blackFieldColor == true) painter.setBrush(Qt::white);
               else painter.setBrush(Qt::black);
           }*/
           painter.drawRect(chessFieldWidth,chessFieldHeight,WINDOW_WIDTH/8,WINDOW_HEIGHT/8);
           chessFieldWidth += WINDOW_WIDTH/8;
           h++;
           if(blackFieldColor == true) blackFieldColor = false;
           else blackFieldColor = true;

       }
       chessFieldWidth = 0;
       chessFieldHeight += WINDOW_HEIGHT/8;
       if(blackFieldColor == true)blackFieldColor = false;
       else blackFieldColor = true;


    }
    for(int i = 0;i<m_amountFigures;i++){
        if(m_pFigures[i]->isThere == true){


            painter.drawPixmap(m_pFigures[i]->getPosX(),m_pFigures[i]->getPosY(),m_pFigures[i]->m_Picture);
        }
    }
    if(activeFigure != 999){
        if(m_pFigures[activeFigure]->isMoving == false){
            QPen pen(QColor("#DC143C"),4);

            painter.setPen(pen);
            //qDebug() << m_pFigures[activeFigure]->getPosX() << m_pFigures[activeFigure]->getPosY() << m_pFigures[activeFigure]->getPosX() << m_pFigures[activeFigure]->getPosY()+BLOCK_WIDTH;
            painter.drawLine(m_pFigures[activeFigure]->getPosX(),m_pFigures[activeFigure]->getPosY(),m_pFigures[activeFigure]->getPosX(),m_pFigures[activeFigure]->getPosY()+BLOCK_WIDTH);
            painter.drawLine(m_pFigures[activeFigure]->getPosX()+BLOCK_WIDTH,m_pFigures[activeFigure]->getPosY(),m_pFigures[activeFigure]->getPosX()+BLOCK_WIDTH,m_pFigures[activeFigure]->getPosY()+BLOCK_WIDTH);
            painter.drawLine(m_pFigures[activeFigure]->getPosX(),m_pFigures[activeFigure]->getPosY(),m_pFigures[activeFigure]->getPosX()+BLOCK_WIDTH,m_pFigures[activeFigure]->getPosY());
            painter.drawLine(m_pFigures[activeFigure]->getPosX(),m_pFigures[activeFigure]->getPosY()+BLOCK_WIDTH,m_pFigures[activeFigure]->getPosX()+BLOCK_WIDTH,m_pFigures[activeFigure]->getPosY()+BLOCK_HEIGHT);
            //qDebug()<<"f";
        }
    }
    painter.setBrush(Qt::red);
    //for(int i = 0;i<28;i++) painter.drawRect(m_pFigures[16]->possibleMoves[i].x(),m_pFigures[16]->possibleMoves[i].y(),10,10);


    painter.end();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

        if(activeFigure != 999 && event->x() > 0 && event->y() > 0 && event->x() < WINDOW_HEIGHT && event->y() < WINDOW_HEIGHT) m_pFigures[activeFigure]->setPos(event->x()-62,event->y()-62);
        //qDebug() << m_pFigures[activeFigure]->getPosX();
        //qDebug() << event->x() << event->y();

    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int figureOnPos;
    figureOnPos = getFigureOnPos(event->x(),event->y());
    //if()

    if(m_pFigures[figureOnPos]->getColor() == BLACK){
    if(figureOnPos != 999){
    if(m_pFigures[figureOnPos]->isThere == true)activeFigure = figureOnPos;
    }

    if(activeFigure != 999){
    posBeforeMove.setX(m_pFigures[activeFigure]->getPosX());
    posBeforeMove.setY(m_pFigures[activeFigure]->getPosY());
    }
    //qDebug() << posBeforeMove.x();
    //qDebug() << posBeforeMove.y();

    if(activeFigure != 999) m_pFigures[activeFigure]->isMoving = true;
    }

    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    captured = false;

    if(activeFigure != 999) m_pFigures[activeFigure]->isMoving = false;
    //qDebug() << event->x();
    //qDebug() << event->y();
    QPoint f = getField(event->x(),event->y());
    refreshCurrentlyPossibleMoves();
    if(activeFigure != 999){

    if(event->x() > 0 && event->y() > 0 && event->x() < WINDOW_WIDTH && event->y() < WINDOW_HEIGHT ){
        qDebug() << "normal";
        bool possibleMove = false;
        qDebug() << "fef"<< m_pFigures[activeFigure]->possibleMovesCurrently.size();
        for(int i = 0;i<m_pFigures[activeFigure]->possibleMovesCurrently.size();i++){
            qDebug() << posBeforeMove.x()+m_pFigures[activeFigure]->possibleMovesCurrently[i].x();
            qDebug() << f.x();
            qDebug() << i;

            if(posBeforeMove.x()+m_pFigures[activeFigure]->possibleMovesCurrently[i].x() == f.x() && posBeforeMove.y() +m_pFigures[activeFigure]->possibleMovesCurrently[i].y() == f.y()){
                possibleMove = true;

                m_pFigures[activeFigure]->setPos(f.x(),f.y());
            }

        }
        if(possibleMove == false)m_pFigures[activeFigure]->setPos(posBeforeMove.x(),posBeforeMove.y());


    }

    else m_pFigures[activeFigure]->setPos(posBeforeMove.x(),posBeforeMove.y());




    //Disables the Figure on Field if antoher Figure gets on it

    for(int i = 0;i<m_amountFigures;i++){
        if(i != activeFigure){
            if(m_pFigures[i]->getPosX() == m_pFigures[activeFigure]->getPosX() && m_pFigures[i]->getPosY() == m_pFigures[activeFigure]->getPosY() && m_pFigures[i]->isThere == true){
                musicPlayer->setMedia(QUrl("qrc:/sounds/capture.mp3"));
                musicPlayer->play();
                //qDebug() << "mem";
                m_pFigures[i]->isThere = false;
                captured = true;
                }
            }

        }


    if(posBeforeMove.x() != m_pFigures[activeFigure]->getPosX() || posBeforeMove.y() != m_pFigures[activeFigure]->getPosY()){
        if(captured == false){
        musicPlayer->setMedia(QUrl("qrc:/sounds/move.mp3"));
        musicPlayer->play();
        }

        }
    }
    if(activeFigure != 999){
        //qDebug() << m_pFigures[activeFigure]->getPosX();
        //qDebug() << m_pFigures[activeFigure]->getPosY();
    }
    //activeFigure = 999;
    update();

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << event->key();

    m_pFigures[31]->setPos(m_pFigures[31]->getPosX()+m_pFigures[31]->possibleMoves[0].x(),m_pFigures[31]->getPosY()+m_pFigures[31]->possibleMoves[0].y());

    //qDebug() << m_pFigures[16]->possibleMoves.size();

    for(int i = 0;i<m_pFigures[16]->possibleMoves.size();i++){
        //qDebug() << "x" << m_pFigures[16]->possibleMoves[i].x();
        //qDebug() << "y"<< m_pFigures[16]->possibleMoves[i].y();
        //qDebug() << i;
    }

    /*switch(event->key()){
    case 'W': m_pPawnBlack->moveForward(1);break;
    case 'D': m_pPawnBlack->moveRight(1);break;
    case 'A': m_pPawnBlack->moveLeft(1);break;
    case 'S': m_pPawnBlack->moveBack(1);break;
    }
    qDebug() << m_pPawnBlack->getPosX() << m_pPawnBlack->getPosY();*/
    update();
}

void MainWindow::sysTickTimer()
{


}

QPoint MainWindow::getField(float mouse_xPos, float mouse_yPos)
{
    float counter_x = 0;
    float counter_y = 0;
    float pos_x = 0;
    float pos_y = 0;
    for(int i = 0;i<9;i++){
          if(mouse_xPos < counter_x && mouse_xPos + 125 > counter_x) pos_x = counter_x;


          counter_x += 125;
    }

    for(int j = 0;j<9;j++){
          if(mouse_yPos < counter_y && mouse_yPos + 125 > counter_y) pos_y = counter_y;
              counter_y += 125;
    }
    pos_x -= 125;
    pos_y -= 125;
    QPoint fieldPos;
    fieldPos.setX(pos_x);
    fieldPos.setY(pos_y);
    return fieldPos;
}

int MainWindow::getFigureOnPos(float pos_x, float pos_y)
{
    int figure = 999;
    QPoint f;
    f = getField(pos_x,pos_y);
    for(int i = 0;i<m_amountFigures;i++) if(f.x() == m_pFigures[i]->getPosX() && f.y() == m_pFigures[i]->getPosY()) figure = i;
    if(figure == 999) figure = 999;
    return figure;
}

void MainWindow::refreshCurrentlyPossibleMoves()
{
    for(int i = 0;i<m_amountFigures;i++){
        m_pFigures[i]->possibleMovesCurrently.clear();
        for(int j = 0;j<m_pFigures[i]->possibleMoves.size();j++){
            QPoint f;

            if(m_pFigures[i]->getPosX()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->getPosY()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->getPosX()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->getPosY()+m_pFigures[i]->possibleMoves[j].y() < 876){
                f.setX(m_pFigures[i]->getPosX()+m_pFigures[i]->possibleMoves[j].x());
                f.setY(m_pFigures[i]->getPosX()+m_pFigures[i]->possibleMoves[j].y());
                m_pFigures[i]->possibleMovesCurrently.append(f);
            }
        }
    }


}

