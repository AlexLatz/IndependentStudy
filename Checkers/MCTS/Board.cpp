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
            if (board[i][j] != '_') {
                pieces.insert(pair<int, int>(i, j));
            }
        }
    }
    this->pieces = pieces;
}

vector<Board::Move> Board::getMoves() {
    if (childMoves.empty()) {
        bool capture = false;
        for (pair<int, int> p : pieces) {
            if (tolower(board[p.first][p.second]) == turn) {
                int bigOn = -1;
                if (isUpper(board[p.first][p.second])) bigOn = 0;
                if (p.first > 0 && (isUpper(board[p.first][p.second]) || board[p.first][p.second] == 'w')) {
                    if (p.first > 1 && p.second > 1 && board[p.first-2][p.second-2] == '_' && tolower(board[p.first-1][p.second-1]) == opposite(turn)) {
                        if (!capture) {
                            this->childMoves.clear();
                            capture = true;
                        }
                        if (bigOn != 0 && p.first-2 == 0) bigOn = 1;
                        Move m(p, pair<int, int>(p.first-2, p.second-2), pair<int, int>(p.first-1, p.second-1), bigOn);
                        this->childMoves.push_back(m);
                        chainMove(m);
                    }
                    else if (p.second > 0 && !capture && board[p.first-1][p.second-1] == '_') {
                        if (bigOn != 0 && p.first-1 == 0) bigOn = 1;
                        this->childMoves.push_back(Move(p, pair<int, int>(p.first-1, p.second-1), bigOn));
                    }
                    if (p.first > 1 && p.second < board[0].size()-2 && board[p.first-2][p.second+2] == '_' && tolower(board[p.first-1][p.second+1]) == opposite(turn)) {
                        if (!capture) {
                            this->childMoves.clear();
                            capture = true;
                        }
                        if (bigOn != 0 && p.first-2 == board.size()-1) bigOn = 1;
                        Move m(p, pair<int, int>(p.first-2, p.second+2), pair<int, int>(p.first-1, p.second+1), bigOn);
                        this->childMoves.push_back(m);
                        chainMove(m);
                    } else if (p.second < board[0].size()-1 && !capture && board[p.first-1][p.second+1] == '_') {
                        if (bigOn != 0 && p.first-1 == 0) bigOn = 1;
                        this->childMoves.push_back(Move(p, pair<int, int>(p.first-1, p.second+1), bigOn));
                    }
                }
                if (p.first < board.size()-1 && (isUpper(board[p.first][p.second]) || board[p.first][p.second] == 'b')) {
                    if (p.first < board.size()-2 && p.second > 1 && board[p.first+2][p.second-2] == '_' && tolower(board[p.first+1][p.second-1]) == opposite(turn)) {
                        if (!capture) {
                            this->childMoves.clear();
                            capture = true;
                        }
                        if (bigOn != 0 && p.first+2 == board.size()-1) bigOn = 1;
                        Move m(p, pair<int, int>(p.first+2, p.second-2), pair<int, int>(p.first+1, p.second-1), bigOn);
                        this->childMoves.push_back(m);
                        chainMove(m);
                    } else if (p.second > 0 && !capture && board[p.first+1][p.second-1] == '_') {
                        if (bigOn != 0 && p.first+1 == board.size()-1) bigOn = 1;
                        this->childMoves.push_back(Move(p, pair<int, int>(p.first+1, p.second-1), bigOn));
                    }
                    if (p.first < board.size()-2 && p.second < board[0].size()-2 && board[p.first+2][p.second+2] == '_' && tolower(board[p.first+1][p.second+1]) == opposite(turn)) {
                        if (!capture) {
                            this->childMoves.clear();
                            capture = true;
                        }
                        if (bigOn != 0 && p.first+2 == board.size()-1) bigOn = 1;
                        Move m(p, pair<int, int>(p.first+2, p.second+2), pair<int, int>(p.first+1, p.second+1), bigOn);
                        this->childMoves.push_back(m);
                        chainMove(m);
                    } else if (p.second < board[0].size()-1 && !capture && board[p.first+1][p.second+1] == '_') {
                        if (bigOn != 0 && p.first+1 == board.size()-1) bigOn = 1;
                        this->childMoves.push_back(Move(p, pair<int, int>(p.first+1, p.second+1), bigOn));
                    }
                }
            }
        }
    }
    return this->childMoves;
}

 void Board::chainMove(Move m) {
    pair<int, int> l  = m.moves[m.moves.size()-1];
    int bigOn = m.bigOn;
    bool origDel = false;
    if (m.bigOn == -1 && (l.first-2 == 0 && board[m.initialPos.first][m.initialPos.second] == 'w') || (l.first+2 == board.size()-1 && board[m.initialPos.first][m.initialPos.second] == 'b')) {
        bigOn = m.moves.size()+1;
    }
     if (l.first > 1 && (m.bigOn >= 0 || board[m.initialPos.first][m.initialPos.second] == 'w')) {
        if (l.second > 1 && board[l.first-2][l.second-2] == '_' && board[l.first-1][l.second-1] == opposite(board[m.initialPos.first][m.initialPos.second]) && m.removedPieces.find(pair<int, int>(l.first-1, l.second-1)) == m.removedPieces.end()) {
            Move newM(m, pair<int, int>(l.first-2, l.second-2), pair<int, int>(l.first-1, l.second-1), bigOn);
            if (!origDel) {
                origDel = true;
                this->childMoves[this->childMoves.size()-1] = newM;
            } else this->childMoves.push_back(newM);
            chainMove(newM);
        }
        if (l.second < board[0].size()-2 && board[l.first-2][l.second+2] == '_' && board[l.first-1][l.second+1] == opposite(board[m.initialPos.first][m.initialPos.second]) && m.removedPieces.find(pair<int, int>(l.first-1, l.second+1)) == m.removedPieces.end()) {
            Move newM(m, pair<int, int>(l.first-2, l.second+2), pair<int, int>(l.first-1, l.second+1), bigOn);
            if (!origDel) {
                origDel = true;
                this->childMoves[this->childMoves.size()-1] = newM;
            } else this->childMoves.push_back(newM);
            chainMove(newM);
        }
    }
    if (l.first < board.size()-2 && (m.bigOn >= 0 || board[m.initialPos.first][m.initialPos.second] == 'b')) {
        if (l.second > 1 && board[l.first+2][l.second-2] == '_' && board[l.first+1][l.second-1] == opposite(board[m.initialPos.first][m.initialPos.second]) && m.removedPieces.find(pair<int, int>(l.first+1, l.second-1)) == m.removedPieces.end()) {
            Move newM(m, pair<int, int>(l.first+2, l.second-2), pair<int, int>(l.first+1, l.second-1), bigOn);
            if (!origDel) {
                origDel = true;
                this->childMoves[this->childMoves.size()-1] = newM;
            } else this->childMoves.push_back(newM);
            chainMove(newM);
        }
        if (l.second < board[0].size()-2 && board[l.first+2][l.second+2] == '_' && board[l.first+1][l.second+1] == opposite(board[m.initialPos.first][m.initialPos.second]) && m.removedPieces.find(pair<int, int>(l.first+1, l.second+1)) == m.removedPieces.end()) {
            Move newM(m, pair<int, int>(l.first+2, l.second+2), pair<int, int>(l.first+1, l.second+1), bigOn);
            if (!origDel) {
                origDel = true;
                this->childMoves[this->childMoves.size()-1] = newM;
            } else this->childMoves.push_back(newM);
            chainMove(newM);
        }
    }
}

Board Board::applyMove(Move m) {
    vector<string> newBoard(board);
    set<pair<int, int> > newPieces(pieces);
    char newTurn = opposite(turn);
    pair<int, int> l = m.moves[m.moves.size()-1];
    newPieces.erase(m.initialPos);
    newBoard[m.initialPos.first][m.initialPos.second] = '_';
    for (pair<int, int> p : m.removedPieces) {
        newPieces.erase(p);
        newBoard[p.first][p.second] = '_';
    }
    newPieces.insert(l);
    if (m.bigOn >= 0) newBoard[l.first][l.second] = toupper(board[m.initialPos.first][m.initialPos.second]);
    else if (m.bigOn == -1) newBoard[l.first][l.second] = board[m.initialPos.first][m.initialPos.second];
    return Board(newBoard, newTurn, newPieces);
}

void Board::printBoard() {
    for (auto & i : board) {
        cout << i << endl;
    }
}
