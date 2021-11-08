#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <string>

using namespace std;
class Grid {
public:
    struct Pair {
        int row; int col;
        bool operator< (const Pair& p) const {
            return p.row == this->row ? this->col < p.col : this->row < p.row;
        }
        bool operator== (const Pair& p) const {
            return p.row == this->row && p.col == this->col;
        }
    };
private:
    int numBlocks{};
    vector<string> board;
    vector<vector<Pair> > parent;
    set<Pair> blocks;
    set<Pair> uniqueBlocks;
    bool disjointCreated;
public:
    Grid(vector<string>& board);
    Grid(Grid& original);
    Grid(const Grid& original);
    void prepareBlocks();
    void updateBoard();
    void printBoard();
    void printParents();
    void createDisjoint();
    Grid removeSet(Pair p);
    int getNumBlocks() const {return this->numBlocks;}
    const int getNumUniqueBlocks() const {return this->uniqueBlocks.size();}
    set<Pair>& getBlocks();
    set<Pair>& getUniqueBlocks();
};
class GameState {
    Grid grid;
    GameState* parent;
    int moves;
    vector<GameState> children;
    bool boardFinished;
    Grid::Pair lastRemoved;
public:
    GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved);
    GameState(const GameState& original);
    vector<GameState>& getChildren();
    Grid& getGrid();
    bool operator> (const GameState& g) const  {
        return this->grid.getNumUniqueBlocks() >  g.grid.getNumUniqueBlocks();
    }
    [[nodiscard]] bool getBoardFinished() const {
        return this->boardFinished;
    }
    GameState* getParent() {
        return this->parent;
    }
    int getMoves() {
        return this->moves;
    }
    Grid::Pair getLastRemoved() { return this->lastRemoved; }
};
Grid::Grid(vector<string>& board) {
    this->board = board;
    updateBoard();
    prepareBlocks();
    this->disjointCreated = false;
}

Grid::Grid(Grid& original) : board(original.board), parent(original.parent),  blocks(original.blocks) {
    this->numBlocks = original.numBlocks;
    this->disjointCreated = original.disjointCreated;
}

Grid::Grid(const Grid& original) : board(original.board), parent(original.parent), blocks(original.blocks) {
    this->numBlocks = original.numBlocks;
    this->disjointCreated = original.disjointCreated;
}

void Grid::prepareBlocks() {
    vector<vector<Pair> > parent;
    set<Pair> blocks;
    int numBlocks = 0;
    for (int i = 0; i < board.size(); i++) {
        vector<Pair> row;
        for (int j = 0; j < board[i].size(); j++) {
            struct Pair point = {i, j};
            if (this->board[i][j] != '-') {
                blocks.insert(point);
                numBlocks++;
            }
            row.push_back(point);
        }
        parent.push_back(row);
    }
    this->blocks = blocks;
    this->parent = parent;
    this->numBlocks = numBlocks;
}

void Grid::updateBoard() {
    for (int i = board.size()-2; i>=0; i--) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != '-' && board[i+1][j] == '-') {
                int howFar = 1;
                for (int k = 1; k+i < board.size(); k++) {
                    if (board[i+k][j] != '-') {
                        howFar = k-1;
                        break;
                    } else if (board[i+k][j] == '-' && i+k == board.size()-1) {
                        howFar = k;
                    }
                }
                string fallLine = board[i+howFar].substr(0, j) + board[i][j] + board[i+howFar].substr(j+1);
                board[i+howFar].swap(fallLine);
                string newLine = board[i].substr(0, j) + '-' + board[i].substr(j+1);
                board[i].swap(newLine);
            }
        }
    }
    for (int j = 0; j < board[0].size(); j++) {
        bool shift = false;
        for (int i = 0; i < board.size(); i++) {
            if (board[i][j] != '-') break;
            else if (i == board.size()-1) shift = true;
        }
        if (shift) {
            for (int i = 0; i < board.size(); i++) {
                string newLine = board[i].substr(0, j) + board[i].substr(j+1) + '-';
                board[i].swap(newLine);
            }
        }
    }
}

void Grid::createDisjoint() {
    set<Pair> uniqueBlocks;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != '-') {
                if (j < board[i].size()-1 && board[i][j] == board[i][j+1] && !(parent[i][j] == parent[i][j+1])) {
                    if (parent[i][j+1].row != i || parent[i][j+1].col != j+1) {
                        blocks.erase(parent[i][j]);
                        parent[i][j] = parent[i][j+1];
                        uniqueBlocks.insert(parent[i][j]);
                    } else {
                        blocks.erase(parent[i][j+1]);
                        parent[i][j+1] = parent[i][j];
                        uniqueBlocks.insert(parent[i][j+1]);
                    }
                }
                if (i < board.size()-1 && board[i][j] == board[i+1][j] && !(parent[i][j] == parent[i+1][j])) {
                    if (parent[i+1][j].row != i+1 || parent[i+1][j].col != j) {
                        blocks.erase(parent[i][j]);
                        parent[i][j] = parent[i+1][j];
                        uniqueBlocks.insert(parent[i][j]);
                    } else {
                        blocks.erase(parent[i+1][j]);
                        parent[i+1][j] = parent[i][j];
                        uniqueBlocks.insert(parent[i+1][j]);
                    }
                }
            }
        }
    }
    this->uniqueBlocks = uniqueBlocks;
}

Grid Grid::removeSet(Grid::Pair p) {
    vector<string> newBoard(board);
    for (int i = 0; i < newBoard.size(); i++) {
        for (int j = 0; j < newBoard[i].size(); j++) {
            if (parent[i][j] == p) newBoard[i][j] = '-';
        }
    }
    Grid newGrid(newBoard);
    return newGrid;
}

set<Grid::Pair>& Grid::getBlocks() {
    if (!disjointCreated) {
        createDisjoint();
        disjointCreated = true;
    }
    return this->blocks;
}

void Grid::printBoard() {
    for (int i = 0; i < board.size(); i++) {
        cout << board[i] << "\n";
    }
}

void Grid::printParents() {
    for (int i = 0; i < parent.size(); i++) {
        for (int j = 0; j < parent[i].size(); j++) {
            cout << parent[i][j].row << parent[i][j].col << " ";
        }
        cout << "\n";
    }
    for (auto& item : uniqueBlocks) cout << item.row << " " << item.col << ", ";
}

set<Grid::Pair>& Grid::getUniqueBlocks() {
    return this->uniqueBlocks;
}
GameState::GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved) : grid(grid) {
    this->parent = parent;
    this->moves = moves;
    this->lastRemoved = lastRemoved;
    this->boardFinished = this->grid.getBlocks().empty();
}

GameState::GameState(const GameState& original) : grid(original.grid) {
    this->parent = original.parent;
    this->moves = original.moves;
    this->lastRemoved = original.lastRemoved;
    this->boardFinished = this->grid.getBlocks().empty();
}

vector<GameState>& GameState::getChildren() {
    if (children.empty()) {
        for (Grid::Pair p : grid.getBlocks()) {
            GameState newState(grid.removeSet(p), this, this->moves+1, p);
            children.push_back(newState);
        }
    }
    return children;
}

Grid& GameState::getGrid() {
    return this->grid;
}


void nextMove(int x, int y, int k, vector<string> board) {
    Grid grid(board);
    priority_queue<GameState, vector<GameState>, greater<GameState> > pq;
    GameState start(grid, nullptr,  0, (Grid::Pair){-1, -1});
    if (start.getBoardFinished()) cout << -1 << -1 << endl;
    pq.push(start);
    while (!pq.top().getBoardFinished()) {
        GameState *best = new GameState(pq.top());
        pq.pop();
        for (const GameState& child: best->getChildren()) {
            pq.push(child);
        }
    }
    GameState chosen = pq.top();
    while (chosen.getParent()->getParent() != nullptr) {
        chosen = *(chosen.getParent());
    }
    cout << chosen.getLastRemoved().row << " " << chosen.getLastRemoved().col << endl;
}

int main(int argc, char const *argv[])
{
    freopen("sample.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int x = 0, y = 0, k = 0;
    cin >> x >> y >> k;
    vector<string> board;
    for (int i = 0; i < x; i++) {
        string s;
        cin >> s;
        board.push_back(s);
    }
    nextMove(x, y, k, board);
    return 0;
}
