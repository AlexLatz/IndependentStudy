//
// Created by Alex Latz on 11/7/21.
//

#ifndef CLICKOMANIA_CLICKOMANIA_H
#define CLICKOMANIA_CLICKOMANIA_H
#include <deque>

class Clickomania {
    deque<GameState> stack;
    public:
        void nextMove(vector<string> board);
        double search(double cost, double bound);
        double heuristic(GameState node);
};

#endif //CLICKOMANIA_CLICKOMANIA_H
