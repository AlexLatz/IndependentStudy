#include "Grid.h"
#include <iostream>

Grid::Grid(vector<string>& board) {
    this->board = board;
    updateBoard();
    prepareBlocks();
    this->disjointCreated = false;
}

Grid::Grid(Grid& original) : board(original.board), parent(original.parent),  blocks(original.blocks), uniqueBlocks(original.uniqueBlocks){
    this->numBlocks = original.numBlocks;
    this->disjointCreated = original.disjointCreated;
}

Grid::Grid(const Grid& original) : board(original.board), parent(original.parent), blocks(original.blocks), uniqueBlocks(original.uniqueBlocks) {
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
    vector<string> newBoard(board);
    for (int i = 0; i < newBoard.size(); i++) {
        for (int j = 0; j < newBoard[i].size(); j++) {
            if (getAbsParent(i, j) == p) newBoard[i][j] = '-';
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
