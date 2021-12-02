//
// Created by Alex Latz on 11/26/21.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <chrono>
#include <random>

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

class GameState {
    Board board;
    static constexpr double C = 1.4;
    GameState* parent;
    vector<GameState*> children;
    Board::Move lastMove;
public:
    int visited;
    int wins;
    GameState(Board board, GameState* parent, Board::Move lastMove);
    vector<GameState*> getChildren();
    Board::Move getLastMove() {return this->lastMove;}
    Board getBoard() {return this->board;}
    GameState* getParent() {return this->parent;}
    double getUCTValue();
};

GameState::GameState(Board board, GameState *parent, Board::Move lastMove) : board(board), lastMove(lastMove) {
    this->parent = parent;
    this->wins = 0;
    this->visited = 0;
}

vector<GameState*> GameState::getChildren() {
    if (children.empty()) {
        for (Board::Move m : board.getMoves()) {
            this->children.push_back(new GameState(board.applyMove(m), this, m));
        }
    }
    return this->children;
}

double GameState::getUCTValue() {
    if (this->visited == 0 || parent->visited == 0) return 0;
    double secondTerm = C * sqrt(log(parent->visited)/this->visited);
    return (this->wins/this->visited) + secondTerm;
}

class Checkers {
    GameState* root;
public:
    Checkers(vector<string> board, char turn);
    GameState* selection();
    void simulation(GameState* node);
    void nextMove();
};
struct UCTCompare {
    bool operator()(GameState* t, GameState* g) {
        return t->visited == g->visited ? t->getUCTValue() > g->getUCTValue() : (t->visited == 0 || g->visited == 0 ? t->visited < g->visited : t->getUCTValue() > g->getUCTValue());
    }
};
struct CountCompare {
    bool operator() (const GameState* t, const GameState* g) {
        return t->visited > g->visited;
    }
};

Checkers::Checkers(vector<string> board, char turn) {
    this->root = new GameState(Board(board, turn), nullptr, Board::Move(pair<int, int>(-1, -1), pair<int, int>(-1, -1), -1));
}

GameState* Checkers::selection() {
    //SELECTION/EXPANSION
    GameState* node = root;
    while (node->getChildren().size() != 0 && node->getChildren().size() <= node->visited) {
        vector<GameState*> newChildren(node->getChildren());
        sort(newChildren.begin(), newChildren.end(), UCTCompare());
        node = newChildren[0];
        if (node->visited == 0) return node;
    }
    if (node->getChildren().size() > 0 && node->getChildren().size() > node->visited) {
        vector<GameState*> newChildren(node->getChildren());
        sort(newChildren.begin(), newChildren.end(), UCTCompare());
        node = newChildren[0];
    }
    return node;
}

void Checkers::simulation(GameState* node) {
    //SIMULATION
    Board board = node->getBoard();
    vector<Board::Move> pastMoves;
    while(!board.getMoves().empty())  {
        vector<Board::Move> list(board.getMoves());
        shuffle(list.begin(), list.end(), default_random_engine());
        while (list.size() > 0 && find(pastMoves.begin(), pastMoves.end(), list[0]) != pastMoves.end()) {
            list.erase(list.begin());
        }
        if (list.size() > 0) {
            board = board.applyMove(list[0]);
            pastMoves.push_back(list[0]);
        } else break;
    }
    //BACKPROPAGATION
    while (node != nullptr) {
        if (root->getBoard().getTurn() != board.getTurn()) node->wins++;
        node->visited++;
        node = node->getParent();
    }
}

void Checkers::nextMove() {
    auto start = chrono::high_resolution_clock::now();
    while (chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count() < 2000000) {
        simulation(selection());
    }
    vector<GameState*> newChildren(this->root->getChildren());
    sort(newChildren.begin(), newChildren.end(), CountCompare());
    Board::Move chosen = newChildren[0]->getLastMove();
    cout << chosen.moves.size() << "\n";
    cout << chosen.initialPos.first << " " << chosen.initialPos.second << "\n";
    for (pair<int, int> p : chosen.moves) {
        cout << p.first << " " << p.second << "\n";
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    char turn;
    int size;
    cin >> turn >> size;
    vector<string> board;
    for (int i = 0; i < size; i++) {
        string s;
        cin >> s;
        board.push_back(s);
    }
    Checkers c(board, turn);
    c.nextMove();
    return 0;
}