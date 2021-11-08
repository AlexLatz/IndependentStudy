#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Grid.h"

class GameState {
    Grid grid;
    GameState* parent;
    int moves;
    vector<GameState> children;
    bool boardFinished;
    int uniqueNum;
    Grid::Pair lastRemoved;
    public:
        GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved);
        GameState(const GameState& original);
        vector<GameState>& getChildren();
        Grid& getGrid();
        bool operator> (const GameState& g) const  {
            return this->grid.getNumBlocks() > g.grid.getNumBlocks();
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
        bool operator==(const GameState& g) const {
            return this->grid==g.grid && this->moves==g.moves && this->lastRemoved == g.lastRemoved;
        }
};

template <class Container>
class Adapter : public Container {
public:
    typedef typename Container::container_type container_type;
    container_type &get_container() { return this->c; }
};
#endif