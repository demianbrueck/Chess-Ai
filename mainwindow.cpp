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
        m_pFiguresCopy[f] = new Figures(0,0,(Figures::FIGURE_NAMES)f);

    }
    m_pSysTickTimer = new QTimer(this);
    connect(m_pSysTickTimer, &QTimer::timeout, this, &MainWindow::sysTickTimer);
    activeFigure = 999;
    m_pSysTickTimer->start(1);
    musicPlayer = new QMediaPlayer;
    colorTurn = BLACK;
    for(int i = 0;i < m_amountFigures;i++){
        m_pFigures[i]->posBeforeMove.setX(m_pFigures[i]->getPosX());
        m_pFigures[i]->posBeforeMove.setY(m_pFigures[i]->getPosY());
        m_pFigures[i]->firstMove = false;
    }
    depth = 3;
    m_pFigures[29]->moveForward(5);
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
        for(int f = 0;f<m_pFigures[activeFigure]->possibleMovesCurrently.size();f++){
            QPen pen(QColor("#F06B2D"),4);

            painter.setPen(pen);

            //qDebug() << m_pFigures[activeFigure]->getPosX() << m_pFigures[activeFigure]->getPosY() << m_pFigures[activeFigure]->getPosX() << m_pFigures[activeFigure]->getPosY()+BLOCK_WIDTH;
            painter.drawLine(m_pFigures[activeFigure]->possibleMovesCurrently[f].x(),m_pFigures[activeFigure]->possibleMovesCurrently[f].y(),m_pFigures[activeFigure]->possibleMovesCurrently[f].x(),m_pFigures[activeFigure]->possibleMovesCurrently[f].y()+BLOCK_WIDTH);
            painter.drawLine(m_pFigures[activeFigure]->possibleMovesCurrently[f].x()+BLOCK_WIDTH,m_pFigures[activeFigure]->possibleMovesCurrently[f].y(),m_pFigures[activeFigure]->possibleMovesCurrently[f].x()+BLOCK_WIDTH,m_pFigures[activeFigure]->possibleMovesCurrently[f].y()+BLOCK_WIDTH);
            painter.drawLine(m_pFigures[activeFigure]->possibleMovesCurrently[f].x(),m_pFigures[activeFigure]->possibleMovesCurrently[f].y(),m_pFigures[activeFigure]->possibleMovesCurrently[f].x()+BLOCK_WIDTH,m_pFigures[activeFigure]->possibleMovesCurrently[f].y());
            painter.drawLine(m_pFigures[activeFigure]->possibleMovesCurrently[f].x(),m_pFigures[activeFigure]->possibleMovesCurrently[f].y()+BLOCK_WIDTH,m_pFigures[activeFigure]->possibleMovesCurrently[f].x()+BLOCK_WIDTH,m_pFigures[activeFigure]->possibleMovesCurrently[f].y()+BLOCK_HEIGHT);
            //qDebug()<<"f";
        }
    }


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
    //qDebug() << "press";
    int figureOnPos;
    figureOnPos = getFigureOnPos(event->x(),event->y());

    //if()

    if(figureOnPos != 999){
        //if(m_pFigures[figureOnPos]->getColor() == BLACK){
            if(m_pFigures[figureOnPos]->isThere == true)activeFigure = figureOnPos;
          //     }
    if(activeFigure != 999){
    m_pFigures[activeFigure]->posBeforeMove.setX(m_pFigures[activeFigure]->getPosX());
    m_pFigures[activeFigure]->posBeforeMove.setY(m_pFigures[activeFigure]->getPosY());
    }

    if(activeFigure != 999) m_pFigures[activeFigure]->isMoving = true;
    }

    refreshCurrentlyPossibleMoves();
    if(activeFigure !=999) qDebug() << activeFigure;
    update();

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

    captured = false;
    //qDebug() << "released";
    if(activeFigure != 999) m_pFigures[activeFigure]->isMoving = false;
    //qDebug() << event->x();
    //qDebug() << event->y();
    bool moved = false;
    QPoint f = getField(event->x(),event->y());
    refreshCurrentlyPossibleMoves();
    if(activeFigure != 999){

    if(event->x() > 0 && event->y() > 0 && event->x() < WINDOW_WIDTH && event->y() < WINDOW_HEIGHT ){
        //qDebug() << "normal";
        //qDebug() << "fef" << m_pFigures[activeFigure]->possibleMovesCurrently.size();

        for(int i = 0;i<m_pFigures[activeFigure]->possibleMovesCurrently.size();i++){
            //qDebug() << "possible move" << m_pFigures[activeFigure]->posBeforeMove.x()+m_pFigures[activeFigure]->possibleMovesCurrently[i].x();
            //qDebug() << "possible move" << m_pFigures[activeFigure]->posBeforeMove.y()+m_pFigures[activeFigure]->possibleMovesCurrently[i].y();
            //qDebug() << "move" <<f.x();
            //qDebug() << "move" <<f.y();
            //qDebug() << i;
            //qDebug() << "mem";
            //qDebug() << m_pFigures[activeFigure]->possibleMovesCurrently[i].x();
            //qDebug() << m_pFigures[activeFigure]->possibleMovesCurrently[i].y();
            if(m_pFigures[activeFigure]->possibleMovesCurrently[i].x() == f.x() && m_pFigures[activeFigure]->possibleMovesCurrently[i].y() == f.y()){
                moved = true;
                m_pFigures[activeFigure]->firstMove = true;
                m_pFigures[activeFigure]->setPos(f.x(),f.y());
                if(colorTurn == BLACK) colorTurn = WHITE;
                else colorTurn = BLACK;
                //qDebug() << "move";

            }

        }
        if(moved == false){
            //qDebug() << "no move";
            m_pFigures[activeFigure]->setPos(m_pFigures[activeFigure]->posBeforeMove.x(),m_pFigures[activeFigure]->posBeforeMove.y());
        }

    }

    else m_pFigures[activeFigure]->setPos(m_pFigures[activeFigure]->posBeforeMove.x(),m_pFigures[activeFigure]->posBeforeMove.y());




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


    if(m_pFigures[activeFigure]->posBeforeMove.x() != m_pFigures[activeFigure]->getPosX() || m_pFigures[activeFigure]->posBeforeMove.y() != m_pFigures[activeFigure]->getPosY()){
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


    if(activeFigure != 999 && moved == true){
        refreshCurrentlyPossibleMoves();
        getAiMove();
    for(int i = 0;i<m_amountFigures;i++){
        if(i != bestAiMoveFigure){
            if(m_pFigures[i]->getPosX() == m_pFigures[bestAiMoveFigure]->getPosX() && m_pFigures[i]->getPosY() == m_pFigures[bestAiMoveFigure]->getPosY() && m_pFigures[i]->isThere == true){
                musicPlayer->setMedia(QUrl("qrc:/sounds/capture.mp3"));
                musicPlayer->play();
                //qDebug() << "mem";
                m_pFigures[i]->isThere = false;
                captured = true;
                }
            }

        }


    if(m_pFigures[bestAiMoveFigure]->posBeforeMove.x() != m_pFigures[bestAiMoveFigure]->getPosX() || m_pFigures[bestAiMoveFigure]->posBeforeMove.y() != m_pFigures[bestAiMoveFigure]->getPosY()){
        if(captured == false){
        musicPlayer->setMedia(QUrl("qrc:/sounds/move.mp3"));
        musicPlayer->play();
        }

        }

}

    if(activeFigure != 999)if(m_pFigures[activeFigure]->isMoving == false) activeFigure = 999;

    //qDebug() << m_pFigures[19]->possibleMovesCurrently.size();
    //getAiMove();

    update();

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << event->key();



    //qDebug() << m_pFigures[16]->possibleMoves.size();


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
    //if(activeFigure!=999)qDebug() << activeFigure;
    //if(activeFigure != 999)qDebug() << m_pFigures[activeFigure]->possibleMovesCurrently.size();
    //qDebug() << m_pFigures[2]->firstMove;

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
    for(int i = 0;i<m_amountFigures;i++){
        if(f.x() == m_pFigures[i]->getPosX() && f.y() == m_pFigures[i]->getPosY() && m_pFigures[i]->isThere == true) figure = i;
    }

    return figure;
}

void MainWindow::refreshCurrentlyPossibleMoves()
{
    //qDebug() << m_amountFigures;
    for(int i = 0;i<m_amountFigures;i++){
        //qDebug() << m_pFigures[i]->getType();
        m_pFigures[i]->possibleMovesCurrently.clear();
        QPoint f;
                //move rules for knights
                if(m_pFigures[i]->getType() >= 20 && m_pFigures[i]->getType() < 24){
                    for(int j = 0;j<m_pFigures[i]->possibleMoves.size();j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                        //qDebug() << m_pFigures[i]->possibleMoves[j];
                    bool figureInfront = false;
                    for(int g = 0;g<m_amountFigures;g++){
                        if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->getColor() == m_pFigures[i]->getColor() && m_pFigures[g]->isThere == true){

                            figureInfront = true;
                        }
                    }
                    //qDebug() <<"m"<< figureInfront;
                    if(figureInfront == false){

                        f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                        f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                        m_pFigures[i]->possibleMovesCurrently.append(f);
                            }
                        }
                    }
                }
                //move rules for pawns
                if(m_pFigures[i]->getType() >= 0 && m_pFigures[i]->getType() < 16){
                    for(int j = 0;j<m_pFigures[i]->possibleMoves.size();j++){

                    if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){

                        if(m_pFigures[i]->possibleMoves[j].x() == 0 && m_pFigures[i]->possibleMoves[j].y() == 125){
                            bool figureInfront = false;
                            for(int g = 0;g<m_amountFigures;g++){
                              if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->isThere == true) figureInfront = true;
                            }
                          if(figureInfront == false){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                          }
                        }
                        if(m_pFigures[i]->possibleMoves[j].x() == 0 && m_pFigures[i]->possibleMoves[j].y() == -125){

                                bool figureInfront = false;
                                for(int g = 0;g<m_amountFigures;g++){
                                  if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->isThere == true) figureInfront = true;
                                }
                                if(figureInfront == false){
                                    f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                                    f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                                    m_pFigures[i]->possibleMovesCurrently.append(f);
                                }
                          }
                            if(m_pFigures[i]->possibleMoves[j].x() == 0 && m_pFigures[i]->possibleMoves[j].y() == 250 && m_pFigures[i]->firstMove == false){
                                bool figureInfront = false;
                                for(int g = 0;g<m_amountFigures;g++){
                                  if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->isThere == true) figureInfront = true;
                                  //qDebug() << "f"<<figureInfront;
                                }
                              if(figureInfront == false){
                                f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                                f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                                m_pFigures[i]->possibleMovesCurrently.append(f);
                              }
                            }
                            if(m_pFigures[i]->possibleMoves[j].x() == 0 && m_pFigures[i]->possibleMoves[j].y() == -250 && m_pFigures[i]->firstMove == false){
                                    //qDebug() << "fef";
                                    bool figureInfront = false;
                                    for(int g = 0;g<m_amountFigures;g++){
                                      if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->isThere == true) figureInfront = true;
                                    }
                                    //qDebug() <<"m"<< figureInfront;
                                    if(figureInfront == false){
                                        f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                                        f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                                        m_pFigures[i]->possibleMovesCurrently.append(f);
                                    }
                              }


                            if(m_pFigures[i]->possibleMoves[j].x() == 125 && m_pFigures[i]->possibleMoves[j].y() == 125){
                                bool figureInfront = false;
                                for(int g = 0;g<m_amountFigures;g++){
                                  if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->getColor() != m_pFigures[i]->getColor() && m_pFigures[g]->isThere == true) figureInfront = true;
                                  //qDebug() << "f"<<figureInfront;
                                }
                              if(figureInfront == true){
                                f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                                f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                                m_pFigures[i]->possibleMovesCurrently.append(f);
                              }
                            }
                            if(m_pFigures[i]->possibleMoves[j].x() == -125 && m_pFigures[i]->possibleMoves[j].y() == 125){
                                    //qDebug() << "fef";
                                    bool figureInfront = false;
                                    for(int g = 0;g<m_amountFigures;g++){
                                      if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->getColor() != m_pFigures[i]->getColor() && m_pFigures[g]->isThere == true) figureInfront = true;
                                    }
                                    //qDebug() <<"m"<< figureInfront;
                                    if(figureInfront == true){
                                        f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                                        f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                                        m_pFigures[i]->possibleMovesCurrently.append(f);
                                    }
                              }

                            if(m_pFigures[i]->possibleMoves[j].x() == 125 && m_pFigures[i]->possibleMoves[j].y() == -125){
                                bool figureInfront = false;
                                for(int g = 0;g<m_amountFigures;g++){
                                  if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->getColor() != m_pFigures[i]->getColor() && m_pFigures[g]->isThere == true) figureInfront = true;
                                  //qDebug() << "f"<<figureInfront;
                                }
                              if(figureInfront == true){
                                f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                                f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                                m_pFigures[i]->possibleMovesCurrently.append(f);
                              }
                            }
                            if(m_pFigures[i]->possibleMoves[j].x() == -125 && m_pFigures[i]->possibleMoves[j].y() == -125){
                                    //qDebug() << "fef";
                                    bool figureInfront = false;
                                    for(int g = 0;g<m_amountFigures;g++){
                                      if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->getColor() != m_pFigures[i]->getColor() && m_pFigures[g]->isThere == true) figureInfront = true;
                                    }
                                    //qDebug() <<"m"<< figureInfront;
                                    if(figureInfront == true){
                                        f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                                        f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                                        m_pFigures[i]->possibleMovesCurrently.append(f);
                                    }
                              }
                            //qDebug() << "memerfef";





                        /*else{

                            for(int k = 0;k<m_amountFigures;k++){
                                if(m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() == m_pFigures[k]->getPosX() && m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y()== m_pFigures[k]->getPosY() && m_pFigures[i]->getColor() != m_pFigures[k]->getColor() && m_pFigures[k]->isThere == true){
                                    //qDebug() << "else";
                                    f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                                    f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                                    m_pFigures[i]->possibleMovesCurrently.append(f);
                                }
                            }
                        }*/
                            }
                        }
                }
                    //kings move rules
                    if(m_pFigures[i]->getType() == 30 || m_pFigures[i]->getType() == 31){

                        for(int j = 0;j<m_pFigures[i]->possibleMoves.size();j++){
                            if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            //qDebug() << m_pFigures[i]->possibleMoves[j];
                        bool figureInfront = false;
                        for(int g = 0;g<m_amountFigures;g++){
                            if(g!=i)if(m_pFigures[g]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[g]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() && m_pFigures[g]->getColor() == m_pFigures[i]->getColor() && m_pFigures[g]->isThere == true){

                                figureInfront = true;
                            }
                        }
                        //qDebug() <<"m"<< figureInfront;
                        if(figureInfront == false){

                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                                }
                            }
                        }
                    }
                //rook move rules

                if(m_pFigures[i]->getType() > 23 && m_pFigures[i]->getType() < 28){

                    for(int j = 0;j<7;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 7;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }

                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();
                    for(int j = 7;j<14;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 14;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();

                    for(int j = 14;j<21;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 21;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();

                    for(int j = 21;j<28;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 28;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();
                }
                //bishop move rules

                if(m_pFigures[i]->getType() > 15 && m_pFigures[i]->getType() < 20){
                    for(int j = 0;j<7;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 7;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }

                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();
                    for(int j = 7;j<14;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 14;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();

                    for(int j = 14;j<21;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 21;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();

                    for(int j = 21;j<28;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 28;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();


                }

                //queen move rules
                if(m_pFigures[i]->getType() == 28 || m_pFigures[i]->getType() == 29){
                    for(int j = 0;j<7;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 7;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }

                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();
                    for(int j = 7;j<14;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 14;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();

                    for(int j = 14;j<21;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 21;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();

                    for(int j = 21;j<28;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 28;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();
                    for(int j = 28;j<35;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 35;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }

                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();
                    for(int j = 35;j<42;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 42;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();

                    for(int j = 42;j<49;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 49;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();

                    for(int j = 49;j<56;j++){
                        if(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() > -1 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() > -1 && m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x() < 876 && m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y() < 876){
                            bool figureInWay = false;
                            for(int k = 0;k<m_amountFigures;k++){
                            if(m_pFigures[k]->getPosX() == m_pFigures[i]->possibleMoves[j].x() + m_pFigures[i]->posBeforeMove.x() && m_pFigures[k]->getPosY() == m_pFigures[i]->possibleMoves[j].y() + m_pFigures[i]->posBeforeMove.y() &&  m_pFigures[k]->isThere == true){
                                if(k!=i){
                                figureInWay = true;
                                //qDebug()<<"mem";

                                }
                            }


                        }
                        if(figureInWay == true){
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            j = 56;
                        }
                        else{
                            f.setX(m_pFigures[i]->posBeforeMove.x()+m_pFigures[i]->possibleMoves[j].x());
                            f.setY(m_pFigures[i]->posBeforeMove.y()+m_pFigures[i]->possibleMoves[j].y());
                            m_pFigures[i]->possibleMovesCurrently.append(f);
                            //qDebug()<<"mem";

                        }
                    }
                    }
                    for(int h = 0;h<m_amountFigures;h++)if(h!=i)if(m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].x() == m_pFigures[h]->getPosX() && m_pFigures[i]->possibleMovesCurrently[m_pFigures[i]->possibleMovesCurrently.size()-1].y() == m_pFigures[h]->getPosY() && m_pFigures[i]->getColor() == m_pFigures[h]->getColor() && m_pFigures[h]->isThere == true)m_pFigures[i]->possibleMovesCurrently.pop_back();
                }

    }

}


void MainWindow::getAiMove()
{



    for(int t = 0;t<m_amountFigures;t++){
    m_pFiguresCopy[t]->setPos(m_pFigures[t]->getPosX(),m_pFigures[t]->getPosY());
    m_pFiguresCopy[t]->firstMove = m_pFigures[t]->firstMove;
    m_pFiguresCopy[t]->isThere = m_pFigures[t]->isThere;
    m_pFiguresCopy[t]->posBeforeMove = m_pFigures[t]->posBeforeMove;

    }
    refreshCurrentlyPossibleMoves();

    bestAiMoveFigure = 0;
    int aiValue = 0;
    unsigned long f = 0;

    highestAiValue = -99999;


        for(int i1 = 0;i1<m_amountFigures;i1++){
            if(i1 != 8){
            if(m_pFigures[i1]->getColor() == WHITE && m_pFigures[i1]->isThere == true){
                for(int j1 = 0;j1<m_pFigures[i1]->possibleMovesCurrently.size();j1++){

                    //for(int i2 = 0;i2<m_amountFigures;i2++){
                      //  if(m_pFigures[i2]->getColor() == BLACK && m_pFigures[i2]->isThere == true){

                        //    for(int j2 = 0;j2<m_pFigures[i2]->possibleMovesCurrently.size();j2++){

                          //      for(int i3 = 0;i3<m_amountFigures;i3++){
                            //        if(m_pFigures[i3]->getColor() == WHITE && m_pFigures[i3]->isThere == true){

                              //          for(int j3 = 0;j3<m_pFigures[i3]->possibleMovesCurrently.size();j3++){

                                //            for(int i4 = 0;i4<m_amountFigures;i4++){
                                             //   if(m_pFigures[i4]->getColor() == BLACK){

                                                   // for(int j4 = 0;j4<m_pFigures[i4]->possibleMovesCurrently.size();i4++){

                                                        //f++;
                                                        //qDebug() << "me" << f;

                                                        for(int t = 0;t<m_amountFigures;t++){
                                                            m_pFigures[t]->setPos(m_pFiguresCopy[t]->getPosX(),m_pFiguresCopy[t]->getPosY());
                                                            m_pFigures[t]->firstMove = m_pFiguresCopy[t]->firstMove;
                                                            m_pFigures[t]->isThere = m_pFiguresCopy[t]->isThere;
                                                            m_pFigures[t]->posBeforeMove = m_pFiguresCopy[t]->posBeforeMove;
                                                        }

                                                        aiValue = 0;
                                                        refreshCurrentlyPossibleMoves();
                                                        m_pFigures[i1]->setPos(m_pFigures[i1]->possibleMovesCurrently[j1].x(),m_pFigures[i1]->possibleMovesCurrently[j1].y());

                                                        //qDebug() << i1 << m_pFigures[i1]->possibleMovesCurrently[j1]/125;
                                                        //qDebug() << m_pFigures[i1]->getPosX()/125 << m_pFigures[i1]->getPosY()/125;
                                                        for(int q = 0;q<m_amountFigures;q++)if(q!=i1)if(m_pFigures[i1]->getPosX() == m_pFigures[q]->getPosX() && m_pFigures[i1]->getPosY() == m_pFigures[q]->getPosY() && m_pFigures[q]->getColor() != m_pFigures[i1]->getColor() && m_pFigures[q]->isThere == true)
                                                        {
                                                            //f++;
                                                            //qDebug() << f;
                                                            aiValue += m_pFigures[q]->getValue();
                                                            //qDebug() << m_pFigures[q]->getValue();
                                                            m_pFigures[q]->isThere = false;
                                                            m_pFigures[q]->firstMove = true;
                                                            //qDebug() << aiValue;

                                                        }
                                                        //refreshCurrentlyPossibleMoves();
                                                        //m_pFigures[i2]->setPos(m_pFigures[i2]->possibleMovesCurrently[j2].x(),m_pFigures[i2]->possibleMovesCurrently[j2].y());

                                                        //for(int f = 0;f<m_amountFigures;f++)if(f!=i2)if(m_pFigures[i2]->getPosX() == m_pFigures[f]->getPosX() && m_pFigures[i2]->getPosY() == m_pFigures[f]->getPosY() && m_pFigures[f]->getColor() != m_pFigures[i2]->getColor() && m_pFigures[f]->isThere == true){
                                                        //    aiValue += m_pFigures[f]->getValue();
                                                        //    m_pFigures[f]->isThere = false;
                                                        //    m_pFigures[f]->firstMove = true;
                                                        //}

                                                        //qDebug() << m_pFigures[25]->possibleMovesCurrently.size();
                                                        //refreshCurrentlyPossibleMoves();
                                                        //m_pFigures[i3]->setPos(m_pFigures[i3]->possibleMovesCurrently[j3].x(),m_pFigures[i3]->possibleMovesCurrently[j3].y());

                                                        //for(int a = 0;a<m_amountFigures;a++)if(a!=i3)if(m_pFigures[i3]->getPosX() == m_pFigures[a]->getPosX() && m_pFigures[i3]->getPosY() == m_pFigures[a]->getPosY() && m_pFigures[a]->getColor() != m_pFigures[i3]->getColor() && m_pFigures[a]->isThere == true){
                                                        //    aiValue += m_pFigures[a]->getValue();
                                                        //    m_pFigures[a]->isThere = false;
                                                        //   m_pFigures[a]->firstMove = true;
                                                        //}
                                                        //refreshCurrentlyPossibleMoves();
                                                        //m_pFigures[i4]->setPos(m_pFigures[i4]->possibleMovesCurrently[j4].x(),m_pFigures[i4]->possibleMovesCurrently[j4].y());
                                                        //for(int q = 0;q<m_amountFigures;q++)if(q!=i4)if(m_pFigures[i4]->possibleMovesCurrently[j4].x() == m_pFigures[q]->getPosX() && m_pFigures[i4]->possibleMovesCurrently[j4].y() == m_pFigures[q]->getPosY()){
                                                        //    aiValue += m_pFigures[q]->getValue();
                                                          //  m_pFigures[q]->isThere = false;
                                                        //m_pFigures[q]->firstMove = true;
                                                        //}


                                                        //if(i1 == 8)for(int f = 0;f<m_pFigures[i1]->possibleMovesCurrently.size();f++)qDebug()<<m_pFigures[i1]->possibleMovesCurrently[f]/125;

                                                        for(int t = 0;t<m_amountFigures;t++){
                                                            m_pFigures[t]->setPos(m_pFiguresCopy[t]->getPosX(),m_pFiguresCopy[t]->getPosY());
                                                            m_pFigures[t]->firstMove = m_pFiguresCopy[t]->firstMove;
                                                            m_pFigures[t]->isThere = m_pFiguresCopy[t]->isThere;
                                                            m_pFigures[t]->posBeforeMove = m_pFiguresCopy[t]->posBeforeMove;
                                                            refreshCurrentlyPossibleMoves();
                                                        }


                                                        //qDebug() << aiValue;
                                                        if(aiValue > highestAiValue && m_pFigures[i1]->getColor() == WHITE){
                                                            highestAiValue = aiValue;
                                                            bestAiMoveFigure = i1;
                                                            bestAiMove = m_pFigures[i1]->possibleMovesCurrently[j1];
                                                            qDebug() << "mem" << aiValue << m_pFigures[i1]->possibleMovesCurrently[j1] << bestAiMoveFigure;
                                                        }

                                                        //qDebug() << f;

                                                    }
                                               }
                                            }

                                        //}
                                    //}
                                //}
                            //}
                        //}
                    //}

                //}
            //}

        //}

}
        //qDebug()<< m_pFigures[8]->getPosX() << m_pFigures[8]->getPosY();

        for(int t = 0;t<m_amountFigures;t++){
            m_pFigures[t]->setPos(m_pFiguresCopy[t]->getPosX(),m_pFiguresCopy[t]->getPosY());
            m_pFigures[t]->firstMove = m_pFiguresCopy[t]->firstMove;
            m_pFigures[t]->isThere = m_pFiguresCopy[t]->isThere;
            m_pFigures[t]->posBeforeMove = m_pFiguresCopy[t]->posBeforeMove;
        }


    //qDebug() << bestAiMoveFigure << bestAiMove;
    m_pFigures[bestAiMoveFigure]->setPos(bestAiMove.x(),bestAiMove.y());
    refreshCurrentlyPossibleMoves();
    //qDebug() << m_pFigures[1]->getPosX() << m_pFigures[1]->getPosY();
    //f++;


}







