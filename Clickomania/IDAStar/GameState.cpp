#include "GameState.h"

GameState::GameState(Grid grid, int moves, Grid::Pair lastRemoved) : grid(grid) {
    this->moves = moves;
    this->lastRemoved = lastRemoved;
    this->boardFinished = this->grid.getBlocks().empty();
    this->uniqueNum = this->grid.getNumUniqueBlocks();
}

GameState::GameState(const GameState& original) : grid(original.grid) {
    this->moves = original.moves;
    this->lastRemoved = original.lastRemoved;
    this->boardFinished = this->grid.getBlocks().empty();
    this->uniqueNum = this->grid.getNumUniqueBlocks();
}

vector<GameState>& GameState::getChildren() {
    if (children.empty()) {
        for (Grid::Pair p : grid.getUniqueBlocks()) {
            GameState newState(grid.removeSet(p), this->moves+1, p);
            children.push_back(newState);
        }
    }
    sort(children.begin(), children.end());
    return children;
}

double GameState::getHeuristic() {
    if (!grid.disjointCreated) grid.createDisjoint();
    double value = 0;
    if (boardFinished) value += 1000;
    else if (getChildren().empty()) {
        for (int count : grid.getColors()) {
            if (count > 2) value -= (count - 2) * (count - 2);
        }
    }
    bool unsolvable = false;
    for (int count : grid.getColors()) {
        if (count == 1) unsolvable = true;
        value += (count-2) ^ 2;
    }
    if (unsolvable) value -= 1000;
    if(value <= 0) return 1;
    return value/1.0;
}

double GameState::getCost() {
    if (this->grid.getNumBlocks() == 2) return 1;
    else return 0/((this->grid.getNumBlocks()-2) * (this->grid.getNumBlocks()-2));
}

Grid& GameState::getGrid() {
    return this->grid;
}