#ifndef CHECKERS_GAMESTATE_H
#define CHECKERS_GAMESTATE_H

#include "Board.h"
#include <cmath>

class GameState {
    Board board;
    static constexpr double C = 1.4;
    GameState* parent;
    vector<GameState*> children;
    Board::Move lastMove;
    public:
        int visited;
        int wins;
        GameState(Board board, GameState* parent, Board::Move lastMove);
        vector<GameState*> getChildren();
        Board::Move getLastMove() {return this->lastMove;}
        Board getBoard() {return this->board;}
        GameState* getParent() {return this->parent;}
        double getUCTValue();
};


#endif //CHECKERS_GAMESTATE_H
