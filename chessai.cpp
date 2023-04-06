#include "chessai.h"

ChessAi::ChessAi(MainWindow *pMainWindow)
{
    m_pMainWindow = pMainWindow;
    for(int t = 0;t<AMOUNT_FIGURES;t++){
        Figures f;
        m_figuresCopy.append(f);
    }
}

void ChessAi::slotGetAiMove(QVector<Figures*> pFigures, int depth)
{
    m_pFigures = pFigures;
    m_aiDepth = depth;
    start(QThread::HighestPriority);
}

void ChessAi::run()
{
    qDebug() << "fef";

    aiValue = 0;
    aiMoves = 0;
    highestAiValue = -9999;
    capturedAtWhichAiMove = 0;
    MainWindow::Move move;


    for(int t = 0;t<AMOUNT_FIGURES;t++){
        m_figuresCopy[t].setPos(m_pFigures[t]->getPosX(),m_pFigures[t]->getPosY());
        m_figuresCopy[t].firstMove = m_pFigures[t]->firstMove;
        m_figuresCopy[t].isThere = m_pFigures[t]->isThere;
        m_figuresCopy[t].posBeforeMove = m_pFigures[t]->posBeforeMove;
    }

    m_pMainWindow->refreshCurrentlyPossibleMoves(BLACK);
    m_pMainWindow->refreshCurrentlyPossibleMoves(WHITE);

    for(int i=0;i<m_pMainWindow->allCurrentlyPossibleMoves.size();i++){
        if(m_pFigures[m_pMainWindow->allCurrentlyPossibleMoves[i].figureIndex]->getColor() == BLACK){
            move.figureIndex = m_pMainWindow->allCurrentlyPossibleMoves[i].figureIndex;
            move.point = m_pMainWindow->allCurrentlyPossibleMoves[i].point;
            initalPossibleAiMoves.append(move);
        }
    }

    for(int f=0;f<initalPossibleAiMoves.size();f++){

        aiValue = 0;

        for(int t = 0;t<AMOUNT_FIGURES;t++){
            m_pFigures[t]->setPos(m_figuresCopy[t].getPosX(),m_figuresCopy[t].getPosY());
            m_pFigures[t]->firstMove = m_figuresCopy[t].firstMove;
            m_pFigures[t]->isThere = m_figuresCopy[t].isThere;
            m_pFigures[t]->posBeforeMove = m_figuresCopy[t].posBeforeMove;

        }
        move = initalPossibleAiMoves[f];

        m_pFigures[move.figureIndex]->setPos(move.point.x(),move.point.y());

        for(int q=0;q<AMOUNT_FIGURES;q++){
            if(q!=move.figureIndex){
                if(m_pFigures[move.figureIndex]->getPosX() == m_pFigures[q]->getPosX() && m_pFigures[move.figureIndex]->getPosY() == m_pFigures[q]->getPosY() && m_pFigures[q]->getColor() != m_pFigures[move.figureIndex]->getColor() && m_pFigures[q]->isThere == true){
                    aiValue += m_pFigures[q]->getValue();
                    m_pFigures[q]->isThere = false;
                    m_pFigures[q]->firstMove = true;

                    //qDebug() << aiValue;
                    //capturedAtWhichAiMove = aiMoves;
                }
            }
        }

        for(int d=0;d<m_aiDepth;d++){

            if(d!=0){
                m_pMainWindow->refreshCurrentlyPossibleMoves(BLACK);
                m_pMainWindow->refreshCurrentlyPossibleMoves(WHITE);

                for(int m=0;m<m_pMainWindow->allCurrentlyPossibleMoves.size();m++){
                    move = m_pMainWindow->allCurrentlyPossibleMoves[m];

                    if(m_pFigures[move.figureIndex]->getColor() == BLACK){


                        m_pFigures[move.figureIndex]->setPos(move.point.x(),move.point.y());

                        for(int q = 0;q<AMOUNT_FIGURES;q++)
                        {
                            if(q!=move.figureIndex){
                                if(m_pFigures[move.figureIndex]->getPosX() == m_pFigures[q]->getPosX() && m_pFigures[move.figureIndex]->getPosY() == m_pFigures[q]->getPosY() && m_pFigures[q]->getColor() != m_pFigures[move.figureIndex]->getColor() && m_pFigures[q]->isThere == true){
                                    aiValue += m_pFigures[q]->getValue();
                                    m_pFigures[q]->isThere = false;
                                    m_pFigures[q]->firstMove = true;
                                    if(DEBUG_MODE){
                                        if(!m_pMainWindow->paintingActive()) m_pMainWindow->repaint();
                                    }

                                    //qDebug() << aiValue;
                                    //capturedAtWhichAiMove = aiMoves;
                                }
                            }
                        }
                    }
                }
                m_pMainWindow->refreshCurrentlyPossibleMoves(WHITE);
                m_pMainWindow->refreshCurrentlyPossibleMoves(BLACK);
            }

            for(int n=0;n<m_pMainWindow->allCurrentlyPossibleMoves.size();n++){
                move = m_pMainWindow->allCurrentlyPossibleMoves[n];
                if(m_pFigures[move.figureIndex]->getColor() == WHITE){
                    move = m_pMainWindow->allCurrentlyPossibleMoves[n];
                    m_pFigures[move.figureIndex]->setPos(move.point.x(),move.point.y());
                    for(int q = 0;q<AMOUNT_FIGURES;q++)
                    {
                        if(q!=move.figureIndex){
                            if(m_pFigures[move.figureIndex]->getPosX() == m_pFigures[q]->getPosX() && m_pFigures[move.figureIndex]->getPosY() == m_pFigures[q]->getPosY() && m_pFigures[q]->getColor() != m_pFigures[move.figureIndex]->getColor() && m_pFigures[q]->isThere == true){
                                aiValue += m_pFigures[q]->getValue();
                                m_pFigures[q]->isThere = false;
                                m_pFigures[q]->firstMove = true;
                                if(DEBUG_MODE){
                                    if(!m_pMainWindow->paintingActive()) m_pMainWindow->repaint();
                                }
                                //qDebug() << aiValue;
                                //capturedAtWhichAiMove = aiMoves;
                            }
                        }
                    }
                }
            }


        }
        if(aiValue > highestAiValue && m_pFigures[initalPossibleAiMoves[f].figureIndex]->getColor() == BLACK){
            highestAiValue = aiValue;
            m_pMainWindow->bestAiMoveFigure = initalPossibleAiMoves[f].figureIndex;
            m_pMainWindow->bestAiMove = initalPossibleAiMoves[f].point;
            //qDebug() << "mem" << aiValue << m_pFigures[i1]->possibleMovesCurrently[j1] << bestAiMoveFigure;
            //qDebug() << i2 <<m_pFigures[i2]->possibleMovesCurrently[j2];

        }

    }

    for(int t = 0;t<AMOUNT_FIGURES;t++){
        m_pFigures[t]->setPos(m_figuresCopy[t].getPosX(),m_figuresCopy[t].getPosY());
        m_pFigures[t]->firstMove = m_figuresCopy[t].firstMove;
        m_pFigures[t]->isThere = m_figuresCopy[t].isThere;
        m_pFigures[t]->posBeforeMove = m_figuresCopy[t].posBeforeMove;
    }

    emit sigAiMoveReady();
}

/*if(aiValue > highestAiValue && m_pFigures[firstMoveFigure]->getColor() == WHITE){
        highestAiValue = aiValue;
        bestAiMoveFigure = firstMoveFigure;
        bestAiMove = firstMove;
        lowestAiMoves = capturedAtWhichAiMove;
        m_pFigures[bestAiMoveFigure]->firstMove = true;
        //qDebug() << "mem" << aiValue << m_pFigures[i1]->possibleMovesCurrently[j1] << bestAiMoveFigure;
        //qDebug() << i2 <<m_pFigures[i2]->possibleMovesCurrently[j2];

    }


    for(int i1 = 0;i1<AMOUNT_FIGURES;i1++){

        if(m_pFigures[i1]->getColor() == WHITE && m_pFigures[i1]->isThere == true){
            refreshCurrentlyPossibleMoves();
            for(int j1 = 0;j1<m_pFigures[i1]->possibleMovesCurrently.size();j1++){

                for(int i2 = 0;i2<AMOUNT_FIGURES;i2++){
                    if(m_pFigures[i2]->getColor() == BLACK && m_pFigures[i2]->isThere == true){

                        for(int j2 = 0;j2<m_pFigures[i2]->possibleMovesCurrently.size();j2++){

                            for(int i3 = 0;i3<AMOUNT_FIGURES;i3++){
                                if(m_pFigures[i3]->getColor() == WHITE && m_pFigures[i3]->isThere == true){

                                    for(int j3 = 0;j3<m_pFigures[i3]->possibleMovesCurrently.size();j3++){

                                        //            for(int i4 = 0;i4<m_amountFigures;i4++){
                                        //   if(m_pFigures[i4]->getColor() == BLACK){

                                        // for(int j4 = 0;j4<m_pFigures[i4]->possibleMovesCurrently.size();i4++){

                                        //f++;
                                        //qDebug() << "me" << f;

                                        for(int t = 0;t<m_amountFigures;t++){
                                            m_pFigures[t]->setPos(m_figuresCopy[t]->getPosX(),m_figuresCopy[t]->getPosY());
                                            m_pFigures[t]->firstMove = m_figuresCopy[t]->firstMove;
                                            m_pFigures[t]->isThere = m_figuresCopy[t]->isThere;
                                            m_pFigures[t]->posBeforeMove.setX(m_pFigures[t]->getPosX());
                                            m_pFigures[t]->posBeforeMove.setY(m_pFigures[t]->getPosY());
                                        }
                                        aiValue = 0;
                                        aiMoves = 0;
                                        refreshCurrentlyPossibleMoves();
                                        m_pFigures[i1]->setPos(m_pFigures[i1]->possibleMovesCurrently[j1].x(),m_pFigures[i1]->possibleMovesCurrently[j1].y());
                                        firstMove.setX(m_pFigures[i1]->possibleMovesCurrently[j1].x());
                                        firstMove.setY(m_pFigures[i1]->possibleMovesCurrently[j1].y());
                                        firstMoveFigure = i1;
                                        //qDebug() << i1 << m_pFigures[i1]->possibleMovesCurrently[j1]/125;
                                        //qDebug() << m_pFigures[i1]->getPosX()/125 << m_pFigures[i1]->getPosY()/125;
                                        aiMoves++;
                                        for(int q = 0;q<m_amountFigures;q++)if(q!=i1)if(m_pFigures[i1]->getPosX() == m_pFigures[q]->getPosX() && m_pFigures[i1]->getPosY() == m_pFigures[q]->getPosY() && m_pFigures[q]->getColor() != m_pFigures[i1]->getColor() && m_pFigures[q]->isThere == true)
                                        {
                                            f++;
                                            //qDebug() << f;
                                            aiValue += m_pFigures[q]->getValue();
                                            //qDebug() << m_pFigures[q]->getValue();
                                            m_pFigures[q]->isThere = false;
                                            m_pFigures[q]->firstMove = true;
                                            //qDebug() << aiValue;

                                            capturedAtWhichAiMove = aiMoves;
                                        }
                                        aiMoves++;
                                        refreshCurrentlyPossibleMoves();
                                        m_pFigures[i2]->setPos(m_pFigures[i2]->possibleMovesCurrently[j2].x(),m_pFigures[i2]->possibleMovesCurrently[j2].y());

                                        for(int f = 0;f<m_amountFigures;f++)if(f!=i2)if(m_pFigures[i2]->getPosX() == m_pFigures[f]->getPosX() && m_pFigures[i2]->getPosY() == m_pFigures[f]->getPosY() && m_pFigures[f]->getColor() != m_pFigures[i2]->getColor() && m_pFigures[f]->isThere == true){
                                            aiValue += m_pFigures[f]->getValue();
                                            m_pFigures[f]->isThere = false;
                                            m_pFigures[f]->firstMove = true;
                                            capturedAtWhichAiMove = aiMoves;
                                        }
                                        aiMoves++;
                                        update();
                                        //qDebug() << m_pFigures[25]->possibleMovesCurrently.size();
                                        refreshCurrentlyPossibleMoves();
                                        m_pFigures[i3]->setPos(m_pFigures[i3]->possibleMovesCurrently[j3].x(),m_pFigures[i3]->possibleMovesCurrently[j3].y());

                                        for(int a = 0;a<m_amountFigures;a++)if(a!=i3)if(m_pFigures[i3]->getPosX() == m_pFigures[a]->getPosX() && m_pFigures[i3]->getPosY() == m_pFigures[a]->getPosY() && m_pFigures[a]->getColor() != m_pFigures[i3]->getColor() && m_pFigures[a]->isThere == true){
                                            aiValue += m_pFigures[a]->getValue();
                                            m_pFigures[a]->isThere = false;
                                            m_pFigures[a]->firstMove = true;
                                            capturedAtWhichAiMove = aiMoves;
                                        }

                                        //refreshCurrentlyPossibleMoves();
                                        //m_pFigures[i4]->setPos(m_pFigures[i4]->possibleMovesCurrently[j4].x(),m_pFigures[i4]->possibleMovesCurrently[j4].y());
                                        //for(int q = 0;q<m_amountFigures;q++)if(q!=i4)if(m_pFigures[i4]->possibleMovesCurrently[j4].x() == m_pFigures[q]->getPosX() && m_pFigures[i4]->possibleMovesCurrently[j4].y() == m_pFigures[q]->getPosY()){
                                        //    aiValue += m_pFigures[q]->getValue();
                                        //  m_pFigures[q]->isThere = false;
                                        //m_pFigures[q]->firstMove = true;
                                        //}

                                        //if(i1 == 8)for(int f = 0;f<m_pFigures[i1]->possibleMovesCurrently.size();f++)qDebug()<<m_pFigures[i1]->possibleMovesCurrently[f]/125;

                                        for(int t = 0;t<m_amountFigures;t++){
                                            m_pFigures[t]->setPos(m_figuresCopy[t]->getPosX(),m_figuresCopy[t]->getPosY());
                                            m_pFigures[t]->firstMove = m_figuresCopy[t]->firstMove;
                                            m_pFigures[t]->isThere = m_figuresCopy[t]->isThere;
                                            m_pFigures[t]->posBeforeMove = m_figuresCopy[t]->posBeforeMove;

                                        }
                                        //refreshCurrentlyPossibleMoves();

                                        //qDebug() << aiValue;
                                        if(aiValue > highestAiValue && m_pFigures[i1]->getColor() == WHITE){
                                            highestAiValue = aiValue;
                                            bestAiMoveFigure = firstMoveFigure;
                                            bestAiMove = firstMove;
                                            lowestAiMoves = capturedAtWhichAiMove;
                                            m_pFigures[bestAiMoveFigure]->firstMove = true;
                                            //qDebug() << "mem" << aiValue << m_pFigures[i1]->possibleMovesCurrently[j1] << bestAiMoveFigure;
                                            //qDebug() << i2 <<m_pFigures[i2]->possibleMovesCurrently[j2];

                                        }
                                        if(aiValue == highestAiValue && lowestAiMoves>capturedAtWhichAiMove && m_pFigures[i1]->getColor() == WHITE){
                                            highestAiValue = aiValue;
                                            bestAiMoveFigure = firstMoveFigure;
                                            bestAiMove = firstMove;
                                            m_pFigures[bestAiMoveFigure]->firstMove = true;
                                            //qDebug() << "mem" << aiValue << m_pFigures[i1]->possibleMovesCurrently[j1] << bestAiMoveFigure;
                                            //qDebug() << i2 <<m_pFigures[i2]->possibleMovesCurrently[j2];

                                        }


                                        //qDebug() << f;
                                    }
                                }


                            }
                        }
                    }
                }
            }
        }

        //}
        //}

        //}

    }
    //qDebug()<< m_pFigures[8]->getPosX() << m_pFigures[8]->getPosY();

    for(int t = 0;t<m_amountFigures;t++){
        m_pFigures[t]->setPos(m_figuresCopy[t]->getPosX(),m_figuresCopy[t]->getPosY());
        m_pFigures[t]->firstMove = m_figuresCopy[t]->firstMove;
        m_pFigures[t]->isThere = m_figuresCopy[t]->isThere;
        m_pFigures[t]->posBeforeMove = m_figuresCopy[t]->posBeforeMove;
    }

}

*/
