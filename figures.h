#ifndef FIGURES_H
#define FIGURES_H


#include <QPixmap>
#include <vector>

class Figures
{
public:

    enum FIGURE_NAMES{
        PAWN_B_1,
        PAWN_B_2,
        PAWN_B_3,
        PAWN_B_4,
        PAWN_B_5,
        PAWN_B_6,
        PAWN_B_7,
        PAWN_B_8,

        PAWN_W_1,
        PAWN_W_2,
        PAWN_W_3,
        PAWN_W_4,
        PAWN_W_5,
        PAWN_W_6,
        PAWN_W_7,
        PAWN_W_8,

        BISHOP_W_1,
        BISHOP_W_2,
        BISHOP_B_1,
        BISHOP_B_2,

        KNIGHT_W_1,
        KNIGHT_W_2,
        KNIGHT_B_1,
        KNIGHT_B_2,

        ROOK_W_1,
        ROOK_W_2,
        ROOK_B_1,
        ROOK_B_2,

        QUEEN_W_1,
        QUEEN_B_1,

        KING_W_1,
        KING_B_1

    };

    Figures();
    Figures(int pos_x,int pos_y,FIGURE_NAMES type);


    void moveForward(int amount);
    void moveBack(int amount);
    void moveLeft(int amount);
    void moveRight(int amount);
    void setType(FIGURE_NAMES type);
    void setPos(int pos_x,int pos_y);
    int getPosX();
    int getPosY();
    QPixmap m_Picture;
    bool isThere;
    bool isMoving;
    QVector<QPoint> possibleMoves;
    QVector<QPoint> possibleMovesCurrently;
    bool getColor();
    QPoint posBeforeMove;
    int getType();
    bool firstMove;
    int getValue();
private:
    bool color;
    int posX;
    int posY;
    int type;
    int value;
};

#endif // FIGURES_H
