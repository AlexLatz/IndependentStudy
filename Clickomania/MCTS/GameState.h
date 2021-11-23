#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Grid.h"

class GameState {
    Grid grid;
    GameState* parent;
    int moves;
    static constexpr double C = 0.1;
    static constexpr double D = 32;
    vector<GameState*> children;
    bool boardFinished;
    int uniqueNum;
    double sigmaSquared;
    Grid::Pair lastRemoved;
    public:
        double rewardSum;
        double rewardCount;
        GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved);
        GameState(const GameState& original);
        void updateSigma();
        double getUCTValue() const;
        vector<GameState*> getChildren();
        Grid& getGrid();
        [[nodiscard]] bool getBoardFinished() const {
            return this->boardFinished;
        }
        GameState* getParent() {
            return this->parent;
        }
        int getMoves() const {
            return this->moves;
        }
        int getUniqueNum() const {
            return this->uniqueNum;
        }
        Grid::Pair getLastRemoved() { return this->lastRemoved; }
};
struct UCTCompare {
    bool operator() (const GameState* t, const GameState* g) {
        return t->rewardCount == g->rewardCount ? t->getUCTValue() > g->getUCTValue() : (t->rewardCount == 0 || g->rewardCount == 0 ? t->rewardCount < g->rewardCount : t->getUCTValue() > g->getUCTValue());
    }
};
struct CountCompare {
    bool operator() (const GameState* t, const GameState* g) {
        return t->rewardCount > g->rewardCount;
    }
};
#endif