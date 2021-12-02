#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include <vector>
#include <string>
#include <set>
#include <iostream>

using namespace std;

class Board {
public:
    struct Move {
        int bigOn;
        pair<int, int> initialPos;
        vector<pair<int, int> > moves;
        set<pair<int, int> > removedPieces;
        Move(Move const &m) {
            this->removedPieces = m.removedPieces;
            this->moves = m.moves;
            this->initialPos = m.initialPos;
            this->bigOn = m.bigOn;
        }
        Move(pair<int, int> initialPos, pair<int, int> move, int bigOn) {
            this->bigOn = bigOn;
            this->initialPos = initialPos;
            vector<pair<int, int> > moves;
            moves.push_back(move);
            this->moves = moves;
        }
        Move(pair<int, int> initialPos, pair<int, int> move, pair<int, int> removedPiece, int bigOn) : Move(initialPos, move, bigOn) {
            this->bigOn = bigOn;
            set<pair<int, int> > removedPieces;
            removedPieces.insert(removedPiece);
            this->removedPieces = removedPieces;
        }
        Move(Move m, pair<int, int> move, pair<int, int> removedPiece, int bigOn) {
            this->bigOn = bigOn;
            this->initialPos = m.initialPos;
            this->moves = m.moves;
            this->removedPieces = m.removedPieces;
            this->moves.push_back(move);
            this->removedPieces.insert(removedPiece);
        }
        bool operator==(const Move& m) const{
            if (this->initialPos == m.initialPos) {
                if (this->removedPieces.size() == m.removedPieces.size()) {
                    auto tIt = this->removedPieces.begin();
                    auto mIt = m.removedPieces.begin();
                    while (tIt != this->removedPieces.end()) {
                        if (*tIt != *mIt) return false;
                        tIt++;
                        mIt++;
                    }
                    if (this->moves.size() == m.moves.size()) {
                        for (int i = 0; i < this->moves.size(); i++) {
                            if (this->moves[i] != m.moves[i]) return false;
                        }
                    } else return false;
                } else return false;
            } else return false;
            return true;
        }
    };
private:
    char turn;
    vector<string> board;
    vector<Move> childMoves;
    set<pair<int, int> > pieces;
    void prepareBoard();
    void chainMove(Move m);
    public:
        Board(vector<string>& board, char turn);
        Board(vector<string>& board, char turn, set<pair<int, int> >& pieces);
        void printBoard();
        char getTurn() {return this->turn;}
        Board applyMove(Move m);
        vector<Move> getMoves();
        static char opposite(char c);
        static bool isUpper(char c);
};


#endif //CHECKERS_BOARD_H
