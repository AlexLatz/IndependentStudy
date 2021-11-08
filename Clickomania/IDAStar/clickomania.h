//
// Created by Alex Latz on 11/7/21.
//

#ifndef CLICKOMANIA_CLICKOMANIA_H
#define CLICKOMANIA_CLICKOMANIA_H
#include <deque>

class Clickomania {
    deque<GameState> stack;
    public:
        void nextMove(int x, int y, int k, vector<string> board);
        int search(int cost, int bound);
        int heuristic(GameState node);
};

#endif //CLICKOMANIA_CLICKOMANIA_H
