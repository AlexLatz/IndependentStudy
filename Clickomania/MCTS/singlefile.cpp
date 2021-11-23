#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <chrono>
#include <random>
#include <fstream>

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
    int points;
    int numBlocks{};
    vector<string> board;
    vector<vector<Pair> > parent;
    set<Pair> blocks;
    set<Pair> uniqueBlocks;
    bool disjointCreated;
    vector<int> colors;
public:
    int getPoints() {return this->points;}
    static map<char, int> colorRef;
    vector<string> getBoard() {return this->board;}
    vector<int> getColors() {return this->colors;}
    char colorAt(Grid::Pair p);
    bool isVS(Grid::Pair p);
    static void prepColors(vector<string> board, int k);
    Grid(vector<string>& board);
    Grid(vector<string>& board, int points);
    Grid(Grid& original);
    Grid(const Grid& original);
    void prepareBlocks();
    void updateBoard();
    void printBoard();
    void printParents();
    void createDisjoint();
    Pair getAbsParent(int i, int j);
    Grid removeSet(Pair p);
    int getNumBlocks() const {return this->numBlocks;}
    const int getNumUniqueBlocks() const {return this->uniqueBlocks.size();}
    const int getBlocksSize() const {return this->blocks.size();}
    set<Pair>& getBlocks();
    set<Pair>& getUniqueBlocks();
};
class GameState {
    Grid grid;
    GameState* parent;
    int moves;
    static constexpr double C = 0.4;
    static constexpr double D = 10000;
    vector<GameState*> children;
    bool childrenGenerated;
    bool boardFinished;
    int uniqueNum;
    Grid::Pair lastRemoved;
public:
    int visited;
    double rewardSum;
    double rewardCount;
    void deleteRecurse();
    GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved);
    GameState(const GameState& original);
    double getUCTValue() const;
    vector<GameState*> getChildren();
    Grid& getGrid();
    [[nodiscard]] bool getBoardFinished() const {
        return this->boardFinished;
    }
    GameState* getParent() {
        return this->parent;
    }
    int getMoves() const {
        return this->moves;
    }
    int getUniqueNum() const {
        return this->uniqueNum;
    }
    Grid::Pair getLastRemoved() { return this->lastRemoved; }
};
struct UCTCompare {
    bool operator() (const GameState* t, const GameState* g) {
        return t->rewardCount == g->rewardCount ? t->getUCTValue() > g->getUCTValue() : (t->rewardCount == 0 || g->rewardCount == 0 ? t->rewardCount < g->rewardCount : t->getUCTValue() > g->getUCTValue());
    }
};
struct HeuristicCompare {
    bool operator() (GameState* t, GameState* g) {
        return t->rewardCount == g->rewardCount ? compareStates(t, g) : (t->rewardCount == 0 || g->rewardCount == 0 ? t->rewardCount < g->rewardCount : compareStates(t, g));
    }
    bool compareStates(GameState* t, GameState* g) {
        if (t->getGrid().getBlocksSize() - t->getGrid().getNumUniqueBlocks() !=
            g->getGrid().getBlocksSize() - g->getGrid().getNumUniqueBlocks()) {
            return t->getGrid().getBlocksSize() - t->getGrid().getNumUniqueBlocks() >
                   g->getGrid().getBlocksSize() - g->getGrid().getNumUniqueBlocks();
        } else if (t->getGrid().getNumUniqueBlocks() == g->getGrid().getNumUniqueBlocks()) {
            return t->getGrid().getNumUniqueBlocks() > g->getGrid().getNumUniqueBlocks();
        } else return true;
    }
};
struct CountCompare {
    bool operator() (const GameState* t, const GameState* g) {
        return t->rewardCount > g->rewardCount;
    }
};
class Clickomania {
    GameState* root;
public:
    Clickomania(vector<string> board);
    GameState* selection();
    void simulation(GameState* node);
    vector<string> nextMove();
    void setBoard(vector<string> board);
};
Grid::Grid(vector<string>& board) {
    this->board = board;
    vector<int> colors(colorRef.size(), 0);
    this->colors = colors;
    updateBoard();
    prepareBlocks();
    this->disjointCreated = false;
    this->points = 0;
}

Grid::Grid(vector<string>& board, int points) : Grid(board) {
    this->points = points;
}

Grid::Grid(Grid& original) : board(original.board), parent(original.parent),  blocks(original.blocks), uniqueBlocks(original.uniqueBlocks), colors(original.colors){
    this->numBlocks = original.numBlocks;
    this->disjointCreated = original.disjointCreated;
    this->points = original.points;
}

Grid::Grid(const Grid& original) : board(original.board), parent(original.parent),  blocks(original.blocks), uniqueBlocks(original.uniqueBlocks), colors(original.colors){
    this->numBlocks = original.numBlocks;
    this->disjointCreated = original.disjointCreated;
    this->points = original.points;
}

char Grid::colorAt(Grid::Pair p) {
    return this->board[p.row][p.col];
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
    for (int j = board[0].size()-1; j >= 0; j--) {
        for (int i = 0; i < board.size(); i++) {
            if (board[i][j] != '-') break;
            else if (i == board.size()-1) {
                for (int k = 0; k < board.size(); k++) {
                    string newLine = board[k].substr(0, j) + board[k].substr(j+1) + '-';
                    board[k].swap(newLine);
                }
            }
        }
    }
}

void Grid::createDisjoint() {
    set<Pair> uniqueBlocks;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != '-') {
                colors[Grid::colorRef.at(board[i][j])]++;
                if (j < board[i].size()-1 && board[i][j] == board[i][j+1] && !(getAbsParent(i, j) == getAbsParent(i, j+1))) {
                    Grid::Pair ap = getAbsParent(i, j);
                    Grid::Pair apR = getAbsParent(i, j+1);
                    if (uniqueBlocks.count(apR) > 0) {
                        blocks.erase(ap);
                        uniqueBlocks.erase(ap);
                        parent[ap.row][ap.col] = apR;
                        uniqueBlocks.insert(apR);
                    } else {
                        blocks.erase(apR);
                        uniqueBlocks.erase(apR);
                        parent[apR.row][apR.col] = ap;
                        uniqueBlocks.insert(ap);
                    }
                }
                if (i < board.size()-1 && board[i][j] == board[i+1][j] && !(getAbsParent(i, j) == getAbsParent(i+1, j))) {
                    Grid::Pair ap = getAbsParent(i, j);
                    Grid::Pair apD = getAbsParent(i+1, j);
                    if (uniqueBlocks.count(apD) > 0) {
                        blocks.erase(ap);
                        uniqueBlocks.erase(ap);
                        parent[ap.row][ap.col] = apD;
                        uniqueBlocks.insert(apD);
                    } else {
                        blocks.erase(apD);
                        uniqueBlocks.erase(apD);
                        parent[apD.row][apD.col] = ap;
                        uniqueBlocks.insert(ap);
                    }
                }
            }
        }
    }
    this->uniqueBlocks = uniqueBlocks;
}

Grid Grid::removeSet(Grid::Pair p) {
    p = getAbsParent(p.row, p.col);
    vector<string> newBoard(board);
    int blocksRemoved = 0;
    for (int i = 0; i < newBoard.size(); i++) {
        for (int j = 0; j < newBoard[i].size(); j++) {
            if (getAbsParent(i, j) == p) {
                newBoard[i][j] = '-';
                blocksRemoved++;
            }
        }
    }
    Grid newGrid(newBoard);
    return newGrid;
}

Grid::Pair Grid::getAbsParent(int i, int j) {
    Grid::Pair p = {i, j};
    Grid::Pair current = parent[i][j];
    while (!(p == current)) {
        p = current;
        current = parent[current.row][current.col];
    }
    return current;
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
            Grid::Pair absParent = getAbsParent(i, j);
            cout << absParent.row << absParent.col << " ";
        }
        cout << "\n";
    }
    for (auto& item : uniqueBlocks) cout << item.row << " " << item.col << ", ";
}

set<Grid::Pair>& Grid::getUniqueBlocks() {
    return this->uniqueBlocks;
}

bool Grid::isVS(Grid::Pair p) {
    int count = 0;
    if (p.row > 0 && board[p.row-1][p.col] == '-') return false;
    for (int i = 0; i < board.size() - p.row; i++) {
        if (board[p.row][p.col] == board[p.row+i][p.col] &&
            (p.col - 1 < 0 || board[p.row + i][p.col - 1] == board[p.row][p.col]) &&
            (p.col + 1 >= board[0].size() || board[p.row + i][p.col + 1] == board[p.row][p.col])) {
            count++;
            if (count > 1) return true;
        } else break;
    }
    return count > 1;
}


map<char, int> Grid::colorRef;

void Grid::prepColors(vector<string> board, int k) {
    set<char> colors;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != '-') {
                colors.insert(board[i][j]);
                if (colors.size() >= k) break;
            }
        }
    }
    map<char, int> colorRefNew;
    int index = 0;
    for (char c : colors) {
        colorRefNew.insert(pair<char, int>(c, index));
        index++;
    }
    colorRef = colorRefNew;
}

GameState::GameState(Grid grid, GameState* parent, int moves, Grid::Pair lastRemoved) : grid(grid) {
    this->parent = parent;
    this->moves = moves;
    this->lastRemoved = lastRemoved;
    this->visited = 0;
    this->rewardSum = 0;
    this->rewardCount = 0;
    this->boardFinished = this->grid.getBlocks().empty();
    this->uniqueNum = this->grid.getNumUniqueBlocks();
}

GameState::GameState(const GameState& original) : grid(original.grid), children(original.children) {
    this->parent = original.parent;
    this->moves = original.moves;
    this->visited = original.visited;
    this->rewardSum = original.rewardSum;
    this->rewardCount = original.rewardCount;
    this->lastRemoved = original.lastRemoved;
    this->boardFinished = this->grid.getBlocks().empty();
    this->uniqueNum = this->grid.getNumUniqueBlocks();
}

vector<GameState*> GameState::getChildren() {
    if (children.empty()) {
        for (Grid::Pair p : grid.getUniqueBlocks()) {
            GameState* newState = new GameState(grid.removeSet(p), this, this->moves+1, p);
            children.push_back(newState);
        }
    }
    return children;
}

Grid& GameState::getGrid() {
    return this->grid;
}

double GameState::getUCTValue() const {
    if (this->rewardCount == 0 || parent->rewardCount == 0) return 0;
    double firstTerm = this->rewardSum/this->rewardCount;
    double secondTerm = C * sqrt((log(parent->rewardCount))/this->rewardCount);
    return firstTerm + secondTerm;
}

void GameState::deleteRecurse() {
    if (!children.empty()) {
        for (GameState* child : children) {
            child->deleteRecurse();
        }
    }
    delete this;
}
Clickomania::Clickomania(vector<string> board) {
    this->root = new GameState(board, nullptr, 0, (Grid::Pair){-1, -1});
}


GameState* Clickomania::selection() {
    //SELECTION/EXPANSION
    GameState* node = root;
    while (node->getChildren().size() != 0 && node->getChildren().size() <= node->rewardCount) {
        vector<GameState*> newChildren(node->getChildren());
        if (this->root->rewardSum == 0) sort(newChildren.begin(), newChildren.end(), HeuristicCompare());
        else sort(newChildren.begin(), newChildren.end(), UCTCompare());
        node = newChildren[0];
        if (node->rewardCount == 0) return node;
    }
    if (node->getChildren().size() > 0 && node->getChildren().size() > node->rewardCount) {
        vector<GameState*> newChildren(node->getChildren());
        if (this->root->rewardSum == 0) sort(newChildren.begin(), newChildren.end(), HeuristicCompare());
        else sort(newChildren.begin(), newChildren.end(), UCTCompare());
        node = newChildren[0];
    }
    return node;
}

void Clickomania::simulation(GameState* node) {
    //TabuColorRandom prep
    pair<int, int> max(0, 0);
    map<int, char> reverseRef;
    for (auto elem : Grid::colorRef) reverseRef.insert(pair<int,char>(elem.second, elem.first));
    for (int i = 0; i < node->getGrid().getColors().size(); i++) {
        if (max.second < node->getGrid().getColors()[i]) {
            max.first = i;
            max.second = node->getGrid().getColors()[i];
        }
    }
    char color = reverseRef.at(max.first);
    //SIMULATION
    Grid grid = node->getGrid();
    while(grid.getNumBlocks() != 0 && grid.getNumUniqueBlocks() != 0)  {
        for (int c : grid.getColors()) if (c == 1) break;
        vector<Grid::Pair> list(grid.getUniqueBlocks().begin(), grid.getUniqueBlocks().end());
        shuffle(list.begin(), list.end(), default_random_engine());
        Grid::Pair chosen = (Grid::Pair){-1, -1};
        for (Grid::Pair p : grid.getUniqueBlocks()) if (grid.colorAt(p) != color) chosen = p;
        if (chosen.row == -1) chosen = *grid.getUniqueBlocks().begin();
        grid = grid.removeSet(chosen);
        grid.createDisjoint();
    }
    if (grid.getNumBlocks() == 0) cout << "WIN FOUND" << endl;
    //BACKPROPAGATION
    while (node != nullptr) {
        if (grid.getNumBlocks() == 0) node->rewardSum++;
        node->rewardCount++;
        node = node->getParent();
    }
}

vector<string> Clickomania::nextMove() {
    auto start = chrono::high_resolution_clock::now();
    while (chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count() < 1950000) {
        simulation(selection());
    }
        vector<GameState*> children(this->root->getChildren());
        sort(children.begin(), children.end(), CountCompare());
        Grid::Pair move = children[0]->getLastRemoved();
        cout << move.row << " " << move.col << endl;
        children[0]->getGrid().printBoard();
        return children[0]->getGrid().getBoard();
}

void Clickomania::setBoard(vector<string> board) {
    this->root = new GameState(Grid(board), nullptr, 0, (Grid::Pair){-1, -1});
}

int main(int argc, char const *argv[])
{
    int x = 0, y = 0, k = 0;
    ifstream infile;
    infile.open("board3.txt");
    infile >> x >> y >> k;
    vector<string> board;
    for (int i = 0; i < x; i++) {
        string s;
        infile >> s;
        board.push_back(s);
    }
    Grid::prepColors(board, k);
    Clickomania c(board);
    while (true) {
        c.setBoard(c.nextMove());
    }
    return 0;
}
