#ifndef FIGURES_H
#define FIGURES_H


#include <QPixmap>
#include <vector>

/*#define BISHOP_W 1
#define BISHOP_B 2
#define KNIGHT_W 3
#define KNIGHT_B 4
#define ROOK_W 5
#define ROOK_B 6
#define PAWN_W 7
#define PAWN_B 8
#define QUEEN_W 9
#define QUEEN_B 10
#define KING_W 11
#define KING_B 12 */




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
private:
    bool color;
    int posX;
    int posY;
    int type;
};

#endif // FIGURES_H
