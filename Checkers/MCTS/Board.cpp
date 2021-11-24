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
        bool capture = false;
        vector<Board> children;
        vector<Move> moves;
        for (pair<int, int> p : pieces) {
            if (p.first > 0) {
                if (p.first > 1 && p.second > 1 && board[p.first-2][p.second-2] == '-' && tolower(board[p.first-1][p.second-1]) == opposite(turn)) {
                    if (!capture) {
                        moves.clear();
                        capture = true;
                    }
                    moves.push_back(Move(p, pair<int, int>(p.first-2, p.second-2), pair<int, int>(p.first-1, p.second-1)));
                }
                if (p.second > 0 && !capture && board[p.first-1][p.second-1] == '-') {
                    moves.push_back(Move(p, pair<int, int>(p.first-1, p.second-1)));
                }
                if (p.first > 1 && p.second < board[0].size()-2 && board[p.first-2][p.second+2] == '-' && tolower(board[p.first-1][p.second+1]) == opposite(turn)) {
                    if (!capture) {
                        moves.clear();
                        capture = true;
                    }
                    moves.push_back(Move(p, pair<int, int>(p.first-2, p.second+2), pair<int, int>(p.first-1, p.second+1)));
                } else if (p.second < board[0].size()-1 && !capture && board[p.first-1][p.second+1] == '-') {
                    moves.push_back(Move(p, pair<int, int>(p.first-1, p.second+1)));
                }
            }
            if (p.first < board.size()-1 && isUpper(board[p.first][p.second])) {
                if (p.first < board.size()-2 && p.second > 1 && board[p.first+2][p.second-2] == '-' && tolower(board[p.first+1][p.second-1]) == opposite(turn)) {
                    if (!capture) {
                        moves.clear();
                        capture = true;
                    }
                    moves.push_back(Move(p, pair<int, int>(p.first+2, p.second-2), pair<int, int>(p.first+1, p.second-1)));
                } else if (p.second > 0 && !capture && board[p.first+1][p.second-1] == '-') {
                    moves.push_back(Move(p, pair<int, int>(p.first+1, p.second-1)));
                }
                if (p.first < board.size()-2 && p.second < board[0].size()-2 && board[p.first+2][p.second+2] == '-' && tolower(board[p.first+1][p.second+1]) == opposite(turn)) {
                    if (!capture) {
                        moves.clear();
                        capture = true;
                    }
                    moves.push_back(Move(p, pair<int, int>(p.first+2, p.second+2), pair<int, int>(p.first+1, p.second+1)));
                } else if (p.second < board[0].size()-1 && !capture && board[p.first+1][p.second+1] == '-') {
                    moves.push_back(Move(p, pair<int, int>(p.first+1, p.second+1)));
                }
            }
        }
        if (capture) {
            for (Move m : moves) {
                chainMove(m, moves);
            }
        }
        this->capture = capture;
        this->children = children;
    }
    return children;
}
