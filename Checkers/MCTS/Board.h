#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include <vector>
#include <string>
#include <set>

using namespace std;

class Board {
    char turn;
    bool capture;
    vector<Board> children;
    vector<string> board;
    vector<pair<int, int> > pieces;
    void prepareBoard();
    public:
        Board(vector<string>& board, char turn);
        Board(vector<string>& board, char turn, vector<pair<int, int> > pieces);
        vector<Board> getChildren();
        static char opposite(char c);
        static bool isUpper(char c);
    struct Move {
        pair<int, int> initialPos;
        vector<pair<int, int> > moves;
        vector<pair<int, int> > removedPieces;
        Move(pair<int, int> pos, vector<pair<int, int> > moves) {
            this->initialPos = pos;
            this->moves = moves;
        }
        Move(pair<int, int> initialPos, pair<int, int> move) {
            this->initialPos = initialPos;
            vector<pair<int, int> > moves;
            moves.push_back(move);
            this->moves;
        }
        Move(pair<int, int> initialPos, pair<int, int> move, pair<int, int> removedPiece) : Move(initialPos, move) {
            vector<pair<int, int> > removedPieces;
            removedPieces.push_back(removedPiece);
            this->removedPieces = removedPieces;
        }
    };
};


#endif //CHECKERS_BOARD_H
