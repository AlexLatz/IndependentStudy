//
// Created by Alex Latz on 11/7/21.
//

#ifndef CLICKOMANIA_CLICKOMANIA_H
#define CLICKOMANIA_CLICKOMANIA_H

class Clickomania {
        GameState* root;
        int runTime;
        int numRollouts;
        int nodeCount;
    public:
        Clickomania(vector<string> board);
        GameState* selection();
        void simulation(GameState* node);
        void nextMove();
};

#endif //CLICKOMANIA_CLICKOMANIA_H
