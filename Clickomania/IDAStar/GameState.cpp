#include "GameState.h"

GameState::GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved) : grid(grid) {
    this->parent = parent;
    this->moves = moves;
    this->lastRemoved = lastRemoved;
    this->boardFinished = this->grid.getBlocks().empty();
    this->uniqueNum = this->grid.getNumUniqueBlocks();
}

GameState::GameState(const GameState& original) : grid(original.grid) {
    this->parent = original.parent;
    this->moves = original.moves;
    this->lastRemoved = original.lastRemoved;
    this->boardFinished = this->grid.getBlocks().empty();
    this->uniqueNum = this->grid.getNumUniqueBlocks();
}

vector<GameState>& GameState::getChildren() {
    if (children.empty()) {
        for (Grid::Pair p : grid.getUniqueBlocks()) {
            GameState newState(grid.removeSet(p), this, this->moves+1, p);
            children.push_back(newState);
        }
    }
    return children;
}

Grid& GameState::getGrid() {
    return this->grid;
}