#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include <vector>
#include <string>
#include <set>

using namespace std;

class Board {
    struct Move {
        int bigOn;
        pair<int, int> initialPos;
        vector<pair<int, int> > moves;
        vector<pair<int, int> > removedPieces;
        Move(pair<int, int> initialPos, pair<int, int> move, int bigOn) {
            this->bigOn = bigOn;
            this->initialPos = initialPos;
            vector<pair<int, int> > moves;
            moves.push_back(move);
            this->moves;
        }
        Move(pair<int, int> initialPos, pair<int, int> move, pair<int, int> removedPiece, int bigOn) : Move(initialPos, move) {
            this->bigOn = bigOn;
            vector<pair<int, int> > removedPieces;
            removedPieces.push_back(removedPiece);
            this->removedPieces = removedPieces;
        }
        Move(Move m, pair<int, int> move, pair<int, int> removedPiece, int bigOn) {
            this->bigOn = bigOn;
            this->initialPos = m.initialPos;
            this->moves = m.moves;
            this->removedPieces = m.removedPieces;
            this->moves.push_back(move);
            this->removedPieces.push_back(removedPiece);
        }
    };
    char turn;
    bool capture;
    vector<Board> children;
    vector<string> board;
    set<pair<int, int> > pieces;
    void prepareBoard();
    void chainMove(Move m, vector<Move>& moves);
    Board applyMove(Move m);
    public:
        Board(vector<string>& board, char turn);
        Board(vector<string>& board, char turn, set<pair<int, int> >& pieces);
        vector<Board> getChildren();
        static char opposite(char c);
        static bool isUpper(char c);
};


#endif //CHECKERS_BOARD_H
