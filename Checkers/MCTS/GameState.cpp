#include "GameState.h"

GameState::GameState(Board board, GameState *parent, Board::Move lastMove) : board(board), lastMove(lastMove) {
    this->parent = parent;
    this->wins = 0;
    this->visited = 0;
}

vector<GameState*> GameState::getChildren() {
    if (children.empty()) {
        for (Board::Move m : board.getMoves()) {
            this->children.push_back(new GameState(board.applyMove(m), this, m));
        }
    }
    return this->children;
}

double GameState::getUCTValue() {
    if (this->visited == 0 || parent->visited == 0) return 0;
    double secondTerm = C * sqrt(log(parent->visited)/this->visited);
    return (this->wins/this->visited) + secondTerm;
}
