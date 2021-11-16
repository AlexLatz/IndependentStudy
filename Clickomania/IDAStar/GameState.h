#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Grid.h"

class GameState {
    Grid grid;
    int moves;
    vector<GameState> children;
    bool boardFinished;
    int uniqueNum;
    Grid::Pair lastRemoved;
    public:
        GameState(Grid grid, int moves, Grid::Pair lastRemoved);
        GameState(const GameState& original);
        vector<GameState>& getChildren();
        Grid& getGrid();
        bool operator< (const GameState& g) const  {
            return this->grid.getNumBlocks() < g.grid.getNumBlocks();
        }
        [[nodiscard]] bool getBoardFinished() const {
            return this->boardFinished;
        }
        int getMoves() const {
            return this->moves;
        }
        int getUniqueNum() const {
            return this->uniqueNum;
        }
        double getHeuristic();
        double getCost();
        Grid::Pair getLastRemoved() { return this->lastRemoved; }
        bool operator==(const GameState& g) const {
            return this->grid==g.grid && this->moves==g.moves && this->lastRemoved == g.lastRemoved;
        }
};
#endif