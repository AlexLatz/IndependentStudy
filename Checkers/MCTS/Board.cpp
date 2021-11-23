#include "Board.h"

Board::Board(vector<string>& board, char turn) {
    this->board = board;
    this->turn = turn;
    prepareBoard();
}

char Board::opposite(char c) {
    if (tolower(c) == 'w') return 'b';
    else return 'w';
}

bool Board::isUpper(char c) {
    return c == 'W' || c == 'B';
}

void Board::prepareBoard() {
    vector<pair<int, int> > pieces;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (tolower(board[i][j]) == turn) {
                pieces.push_back(pair<int, int>(i, j));
            }
        }
    }
    this->pieces = pieces;
}

vector<Board> Board::getChildren() {
    if (children.empty()) {
        vector<Board> children;
        vector<Move> moves;
        set<pair<int, int> > canCapture;
        for (pair<int, int> p : pieces) {
            if (p.first > 0) {
                if (p.second > 0) {
                    if (tolower(board[p.first-1][p.second-1]) == opposite(turn)) {
                        capture = true;
                        canCapture.insert(p);
                    } else if (!capture && board[p.first-1][p.second-1] == '-') {
                        moves.push_back(Move(p, pair<int, int>(p.first-1, p.second-1)));
                    }
                }
                if (p.second < board[0].size()-1) {
                    if (tolower(board[p.first-1][p.second+1]) == opposite(turn)) {
                        capture = true;
                        canCapture.insert(p);
                    } else if (!capture && board[p.first-1][p.second+1] == '-') {
                        moves.push_back(Move(p, pair<int, int>(p.first-1, p.second+1)));
                    }
                }
            }
            if (p.first < board.size()-1 && isUpper(board[p.first][p.second])) {
                if (p.second > 0) {
                    //TODO: fix the capturing needing an open space after
                    if (p.second > 1 && tolower(board[p.first+1][p.second-1]) == opposite(turn) && board[p.first+2]) {
                        capture = true;
                        canCapture.insert(p);
                    } else if (!capture && board[p.first+1][p.second-1] == '-') {
                        moves.push_back(Move(p, pair<int, int>(p.first+1, p.second-1)));
                    }
                }
                if (p.second < board[0].size()-1) {
                    if (tolower(board[p.first+1][p.second+1]) == opposite(turn)) {
                        capture = true;
                        canCapture.insert(p);
                    } else if (!capture && board[p.first+1][p.second+1] == '-') {
                        moves.push_back(Move(p, pair<int, int>(p.first+1, p.second+1)));
                    }
                }
            }
        }
        if (!canCapture.empty()) {
            moves.clear();
            for (pair<int, int> p : canCapture) {
                if (p.first > 0) {
                    if (p.second > 0) {
                        if (board[p.first-1][p.second-1] == opposite(turn)) {

                        }
                    }
                }
            }
        }
        this->capture = capture;
        this->children = children;
    }
    return children;
}
