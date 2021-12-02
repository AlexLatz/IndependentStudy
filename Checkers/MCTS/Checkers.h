//
// Created by Alex Latz on 11/23/21.
//

#ifndef CHECKERS_CHECKERS_H
#define CHECKERS_CHECKERS_H

#include "GameState.h"

class Checkers {
    GameState* root;
    public:
        Checkers(vector<string> board, char turn);
        GameState* selection();
        void simulation(GameState* node);
        void nextMove();
};
struct UCTCompare {
    bool operator()(GameState* t, GameState* g) {
        return t->visited == g->visited ? t->getUCTValue() > g->getUCTValue() : (t->visited == 0 || g->visited == 0 ? t->visited < g->visited : t->getUCTValue() > g->getUCTValue());
    }
};
struct CountCompare {
    bool operator() (const GameState* t, const GameState* g) {
        return t->visited > g->visited;
    }
};

#endif //CHECKERS_CHECKERS_H
