#include "Checkers.h"
#include <fstream>
#include <random>
#include <chrono>

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
    newChildren[0]->getBoard().printBoard();
    Board::Move chosen = newChildren[0]->getLastMove();
    cout << chosen.moves.size() << "\n";
    cout << chosen.initialPos.first << " " << chosen.initialPos.second << "\n";
    for (pair<int, int> p : chosen.moves) {
        cout << p.first << " " << p.second << "\n";
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    ifstream infile;
    infile.open("board1.txt");
    char turn;
    int size;
    infile >> turn >> size;
    vector<string> board;
    for (int i = 0; i < size; i++) {
        string s;
        infile >> s;
        board.push_back(s);
    }
    Checkers c(board, turn);
    c.nextMove();
    infile.close();
    return 0;
}