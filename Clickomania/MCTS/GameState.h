#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Grid.h"

class GameState {
    Grid grid;
    GameState* parent;
    int moves;
    static constexpr double C = 0.5;
    static constexpr double D = 10000;
    vector<GameState>* children;
    bool childrenGenerated;
    bool boardFinished;
    int uniqueNum;
    Grid::Pair lastRemoved;
    public:
        int visited;
        double rewardSum;
        double rewardCount;
        GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved);
        GameState(const GameState& original);
        double getUCTValue() const;
        vector<GameState>* getChildren();
        Grid& getGrid();
        bool operator< (const GameState& g) const {
            return this->rewardCount == g.rewardCount ? this->getUCTValue() > g.getUCTValue() : (this->rewardCount == 0 || g.rewardCount == 0 ? this->rewardCount < g.rewardCount : this->getUCTValue() > g.getUCTValue());
        }
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
#endif