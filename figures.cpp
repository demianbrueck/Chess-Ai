 #include "figures.h"
#include "mainwindow.h"

Figures::Figures(int pos_x,int pos_y,FIGURE_NAMES originalType)
{
    posX = pos_x;
    posY = pos_y;
    setType(originalType);
    isThere = true;
    type = originalType;
}
Figures::Figures(){

}

void Figures::moveForward(int amount)
{
    for(int i = 0;i<amount;i++)
        if(posY>0)posY -= BLOCK_HEIGHT;
}

void Figures::moveBack(int amount)
{
    for(int i = 0;i<amount;i++)
        if(posY+BLOCK_HEIGHT<WINDOW_HEIGHT)posY += BLOCK_HEIGHT;
}

void Figures::moveLeft(int amount)
{
    for(int i = 0;i<amount;i++)
        if(posX>0)posX -= BLOCK_WIDTH;
}

void Figures::moveRight(int amount)
{
    for(int i = 0;i<amount;i++)
        if(posX+BLOCK_WIDTH<WINDOW_WIDTH) posX = posX + BLOCK_WIDTH;
}

void Figures::setType(FIGURE_NAMES type)
{
    if(type == KING_W_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_klt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(7);
       moveRight(3);
       color = WHITE;
       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(0);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(0);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       value = 900;
    }
    if(type == KING_B_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_kdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveRight(3);
       color = BLACK;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(0);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(0);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       value = -900;
    }
    if(type == PAWN_W_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_plt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(6);
       color = WHITE;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(-250);
       possibleMoves.append(f);

       value = 10;
    }
    if(type == PAWN_W_2){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_plt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(6);
       moveRight(1);
       color = WHITE;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(-250);
       possibleMoves.append(f);

       value = 10;
    }
    if(type == PAWN_W_3){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_plt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(6);
       moveRight(2);
       color = WHITE;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(-250);
       possibleMoves.append(f);

       value = 10;
    }
    if(type == PAWN_W_4){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_plt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(6);
       moveRight(3);
       color = WHITE;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(-250);
       possibleMoves.append(f);

       value = 10;
    }
    if(type == PAWN_W_5){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_plt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(6);
       moveRight(4);
       color = WHITE;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(-250);
       possibleMoves.append(f);

       value = 10;
    }
    if(type == PAWN_W_6){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_plt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(6);
       moveRight(5);
       color = WHITE;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(-250);
       possibleMoves.append(f);

       value = 10;
    }
    if(type == PAWN_W_7){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_plt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(6);
       moveRight(6);
       color = WHITE;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(-250);
       possibleMoves.append(f);

       value = 10;
    }
    if(type == PAWN_W_8){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_plt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(6);
       moveRight(7);
       color = WHITE;

       QPoint f(0,-125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(-250);
       possibleMoves.append(f);

       value = 10;
    }
    if(type == PAWN_B_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_pdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(1);
       color = BLACK;

       QPoint f(0,125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(250);
       possibleMoves.append(f);

       value = -10;
    }
    if(type == PAWN_B_2){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_pdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(1);
       moveRight(1);
       color = BLACK;

       QPoint f(0,125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(250);
       possibleMoves.append(f);

       value = -10;

    }
    if(type == PAWN_B_3){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_pdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(1);
       moveRight(2);
       color = BLACK;

       QPoint f(0,125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(250);
       possibleMoves.append(f);

       value = -10;
    }
    if(type == PAWN_B_4){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_pdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(1);
       moveRight(3);
       color = BLACK;

       QPoint f(0,125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(250);
       possibleMoves.append(f);

       value = -10;
    }
    if(type == PAWN_B_5){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_pdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(1);
       moveRight(4);
       color = BLACK;

       QPoint f(0,125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(250);
       possibleMoves.append(f);

       value = -10;
    }
    if(type == PAWN_B_6){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_pdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(1);
       moveRight(5);
       color = BLACK;

       QPoint f(0,125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(250);
       possibleMoves.append(f);

       value = -10;
    }
    if(type == PAWN_B_7){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_pdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(1);
       moveRight(6);
       color = BLACK;

       QPoint f(0,125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(250);
       possibleMoves.append(f);

       value = -10;
    }
    if(type == PAWN_B_8){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_pdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(1);
       moveRight(7);
       color = BLACK;

       QPoint f(0,125);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(0);
       f.setY(250);
       possibleMoves.append(f);

       value = -10;
    }
    if(type == KNIGHT_W_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_nlt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(7);
       moveRight(1);
       color = WHITE;

       QPoint f(125,250);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(250);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-250);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-250);
       possibleMoves.append(f);


       f.setX(250);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-250);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(250);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(-250);
       f.setY(-125);
       possibleMoves.append(f);

       value = 30;
    }
    if(type == KNIGHT_W_2){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_nlt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(7);
       moveRight(6);
       color = WHITE;

       QPoint f(125,250);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(250);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-250);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-250);
       possibleMoves.append(f);

       f.setX(250);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-250);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(250);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(-250);
       f.setY(-125);
       possibleMoves.append(f);

       value = 30;
    }
    if(type == KNIGHT_B_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_ndt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveRight(1);
       color = BLACK;

       QPoint f(125,250);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(250);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-250);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-250);
       possibleMoves.append(f);

       f.setX(250);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-250);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(250);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(-250);
       f.setY(-125);
       possibleMoves.append(f);

       value = -30;
    }
    if(type == KNIGHT_B_2){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_ndt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveRight(6);
       color = BLACK;

       QPoint f(125,250);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(250);
       possibleMoves.append(f);

       f.setX(-125);
       f.setY(-250);
       possibleMoves.append(f);

       f.setX(125);
       f.setY(-250);
       possibleMoves.append(f);

       f.setX(250);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(-250);
       f.setY(125);
       possibleMoves.append(f);

       f.setX(250);
       f.setY(-125);
       possibleMoves.append(f);

       f.setX(-250);
       f.setY(-125);
       possibleMoves.append(f);

       value = -30;
    }
    if(type == BISHOP_W_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_blt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(7);
       moveRight(2);
       color = WHITE;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }
       value = 30;
    }
    if(type == BISHOP_W_2){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_blt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(7);
       moveRight(5);
       color = WHITE;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }

       value = 30;
    }
    if(type == BISHOP_B_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_bdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveRight(2);
       color = BLACK;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }

       value = -30;
    }
    if(type == BISHOP_B_2){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_bdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveRight(5);
       color = BLACK;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }

       value = -30;
    }
    if(type == ROOK_W_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_rlt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(7);
       color = BLACK;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(-125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(0);
           possibleMoves.append(f);
           }

       value = 50;
    }
    if(type == ROOK_W_2){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_rlt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveBack(7);
       moveRight(7);
       color = WHITE;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(-125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(0);
           possibleMoves.append(f);
           }

       value = 50;
    }
    if(type == ROOK_B_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_rdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       color = BLACK;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(-125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       value = -50;
    }
    if(type == ROOK_B_2){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_rdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveRight(7);
       color = BLACK;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(-125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       value = -50;
    }
    if(type == QUEEN_W_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_qlt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveRight(4);
       moveBack(7);
       color = WHITE;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(-125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(125*i);
           possibleMoves.append(f);
    }
       value = 90;
    }
    if(type == QUEEN_B_1){
       QPixmap pm(125,125);
       pm.load(":/res/img/Chess_qdt45.svg");
       m_Picture = pm.scaled(BLOCK_WIDTH,BLOCK_HEIGHT);
       moveRight(4);
       color = BLACK;

       QPoint f;
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(-125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(0);
           f.setY(125*i);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(0);
           possibleMoves.append(f);
           }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(125*i);
           f.setY(-125*i);
           possibleMoves.append(f);
       }
       for(int i = 1;i<8;i++){
           f.setX(-125*i);
           f.setY(125*i);
           possibleMoves.append(f);
        }
       value = -90;
     }


}
void Figures::setPos(int pos_x,int pos_y)
{
    posX = pos_x;
    posY = pos_y;
}

int Figures::getPosX()
{
    return posX;
}
int Figures::getPosY()
{
    return posY;
}

bool Figures::getColor()
{
    return color;
}

int Figures::getType()
{
    return type;
}

int Figures::getValue()
{
    return value;
}
