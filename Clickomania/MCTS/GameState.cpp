#include "GameState.h"
#include <cmath>

GameState::GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved) : grid(grid) {
    this->parent = parent;
    this->moves = moves;
    this->lastRemoved = lastRemoved;
    this->visited = 0;
    this->rewardSum = 0;
    this->rewardCount = 0;
    this->boardFinished = this->grid.getBlocks().empty();
    this->uniqueNum = this->grid.getNumUniqueBlocks();
}

GameState::GameState(const GameState& original) : grid(original.grid), children(original.children) {
    this->parent = original.parent;
    this->moves = original.moves;
    this->visited = original.visited;
    this->rewardSum = original.rewardSum;
    this->rewardCount = original.rewardCount;
    this->lastRemoved = original.lastRemoved;
    this->boardFinished = this->grid.getBlocks().empty();
    this->uniqueNum = this->grid.getNumUniqueBlocks();
}

vector<GameState*> GameState::getChildren() {
    if (children.empty()) {
        for (Grid::Pair p : grid.getUniqueBlocks()) {
            GameState* newState = new GameState(grid.removeSet(p), this, this->moves+1, p);
            children.push_back(newState);
        }
    }
    return children;
}

Grid& GameState::getGrid() {
    return this->grid;
}

double GameState::getUCTValue() const {
    if (this->rewardCount == 0 || parent->rewardCount == 0) return 0;
    double sigmaSquared = 0;
    for (GameState* s : parent->children) if (s->rewardCount > 0) sigmaSquared += (s->rewardSum/s->rewardCount) * (s->rewardSum/s->rewardCount);
    double secondTerm = C * sqrt(log(parent->rewardCount)/this->rewardCount);
    double thirdTerm = sqrt((sigmaSquared-this->rewardCount*(parent->rewardSum/parent->rewardCount)+D)/(this->rewardCount));
    return (this->rewardSum/this->rewardCount) + secondTerm + thirdTerm;
}
