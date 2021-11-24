#include "Board.h"

Board::Board(vector<string>& board, char turn) {
    this->board = board;
    this->turn = turn;
    prepareBoard();
}

Board::Board(vector<string>& board, char turn, set<pair<int, int> >& pieces) {
    this->board = board;
    this->turn = turn;
    this->pieces = pieces;
}

char Board::opposite(char c) {
    if (tolower(c) == 'w') return 'b';
    else return 'w';
}

bool Board::isUpper(char c) {
    return c == 'W' || c == 'B';
}

void Board::prepareBoard() {
    set<pair<int, int> > pieces;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (tolower(board[i][j]) == turn) {
                pieces.insert(pair<int, int>(i, j));
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
            int bigOn = -1;
            if (isUpper(board[p.first][p.second])) bigOn = 0;
            else if ((p.first-2 == 0 && board[p.first][p.second] == 'w') || (p.first+2 == board.size()-1 && board[p.first][p.second] == 'b')) bigOn = 1;
            if (p.first > 0 && (isUpper(board[p.first][p.second]) || board[p.first][p.second] == 'w')) {
                if (p.first > 1 && p.second > 1 && board[p.first-2][p.second-2] == '-' && tolower(board[p.first-1][p.second-1]) == opposite(turn)) {
                    if (!capture) {
                        moves.clear();
                        capture = true;
                    }
                    if (p.first-2 == 0) bigOn = 1;
                    moves.push_back(Move(p, pair<int, int>(p.first-2, p.second-2), pair<int, int>(p.first-1, p.second-1), bigOn));
                }
                if (p.second > 0 && !capture && board[p.first-1][p.second-1] == '-') {
                    if (p.first-2 == 0) bigOn = 1;
                    moves.push_back(Move(p, pair<int, int>(p.first-1, p.second-1), bigOn));
                }
                if (p.first > 1 && p.second < board[0].size()-2 && board[p.first-2][p.second+2] == '-' && tolower(board[p.first-1][p.second+1]) == opposite(turn)) {
                    if (!capture) {
                        moves.clear();
                        capture = true;
                    }
                    moves.push_back(Move(p, pair<int, int>(p.first-2, p.second+2), pair<int, int>(p.first-1, p.second+1), bigOn));
                } else if (p.second < board[0].size()-1 && !capture && board[p.first-1][p.second+1] == '-') {
                    moves.push_back(Move(p, pair<int, int>(p.first-1, p.second+1), bigOn));
                }
            }
            if (p.first < board.size()-1 && (isUpper(board[p.first][p.second]) || board[p.first][p.second] == 'b')) {
                if (p.first < board.size()-2 && p.second > 1 && board[p.first+2][p.second-2] == '-' && tolower(board[p.first+1][p.second-1]) == opposite(turn)) {
                    if (!capture) {
                        moves.clear();
                        capture = true;
                    }
                    moves.push_back(Move(p, pair<int, int>(p.first+2, p.second-2), pair<int, int>(p.first+1, p.second-1), bigOn));
                } else if (p.second > 0 && !capture && board[p.first+1][p.second-1] == '-') {
                    moves.push_back(Move(p, pair<int, int>(p.first+1, p.second-1), bigOn));
                }
                if (p.first < board.size()-2 && p.second < board[0].size()-2 && board[p.first+2][p.second+2] == '-' && tolower(board[p.first+1][p.second+1]) == opposite(turn)) {
                    if (!capture) {
                        moves.clear();
                        capture = true;
                    }
                    moves.push_back(Move(p, pair<int, int>(p.first+2, p.second+2), pair<int, int>(p.first+1, p.second+1), bigOn));
                } else if (p.second < board[0].size()-1 && !capture && board[p.first+1][p.second+1] == '-') {
                    moves.push_back(Move(p, pair<int, int>(p.first+1, p.second+1), bigOn));
                }
            }
        }
        if (capture) {
            vector<Move> newMoves;
            for (Move m : moves) {
                chainMove(m, newMoves);
            }
            moves.insert(moves.end(), newMoves.begin(), newMoves.end());
        }
        for (Move m : moves) {
            children.push_back(applyMove(m));
        }
        this->capture = capture;
        this->children = children;
    }
    return children;
}

 void Board::chainMove(Move m, vector<Move>& moves) {
    pair<int, int> l  = m.moves[m.moves.size()-1];
    int bigOn = m.bigOn;
    if (m.bigOn == -1 && (l.first-2 == 0 && board[m.initialPos.first][m.initialPos.second] == 'w') || (l.first+2 == board.size()-1 && board[m.initialPos.first][m.initialPos.second] == 'b')) {
        bigOn = m.moves.size()+1;
    }
     if (l.first > 1) {
        if (l.second > 1 && board[l.first-2][l.second-2] == '-' && board[l.first-1][l.second-1] == opposite(board[m.initialPos.first][m.initialPos.second])) {
            Move newM(m, pair<int, int>(l.first-2, l.second-2), pair<int, int>(l.first-1, l.second-1), bigOn);
            moves.push_back(newM);
            chainMove(newM, moves);
        }
        if (l.second < board[0].size()-2 && board[l.first-2][l.second+2] == '-' && board[l.first-1][l.second+1] == opposite(board[m.initialPos.first][m.initialPos.second])) {
            Move newM(m, pair<int, int>(l.first-2, l.second+2), pair<int, int>(l.first-1, l.second+1), bigOn);
            moves.push_back(newM);
            chainMove(newM, moves);
        }
    }
    if (l.first < board.size()-2 && isUpper(board[m.initialPos.first][m.initialPos.second])) {
        if (l.second > 1 && board[l.first+2][l.second-2] == '-' && board[l.first+1][l.second-1] == opposite(board[m.initialPos.first][m.initialPos.second])) {
            Move newM(m, pair<int, int>(l.first+2, l.second-2), pair<int, int>(l.first+1, l.second-1), bigOn);
            moves.push_back(newM);
            chainMove(newM, moves);
        }
        if (l.second < board[0].size()-2 && board[l.first+2][l.second+2] == '-' && board[l.first+1][l.second+1] == opposite(board[m.initialPos.first][m.initialPos.second])) {
            Move newM(m, pair<int, int>(l.first+2, l.second+2), pair<int, int>(l.first+1, l.second+1), bigOn);
            moves.push_back(newM);
            chainMove(newM, moves);
        }
    }
}

Board Board::applyMove(Move m) {
    vector<string> newBoard(board);
    set<pair<int, int> > newPieces(pieces);
    char newTurn = opposite(turn);
    newBoard[m.initialPos.first][m.initialPos.second] = '-';
    newBoard[m.moves[m.moves.size()-1].first][m.moves[m.moves.size()-1].second] = board[m.initialPos.first][m.initialPos.second];
}
