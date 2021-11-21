/*
Clickomania is a 1-player game consisting of a rectangular grid of square blocks, each colored in one of k colors. Adjacent blocks horizontally and vertically of the same color are considered to be a part of the same group. A move selects a group containing at least two blocks and removes those blocks, followed by two "falling" rules;

Any blocks remaining above the holes created, fall down through the same column.
Any empty columns are removed by sliding the succeeding columns left.


In this game, you have to code a bot such that it eliminates as many possible blocks from the grid. The top left of the grid is indexed (0,0) and the bottom right of the grid is indexed (rows-1,columns-1).

Input Format
The first line of the input is 3 space separated integers, x y k where x and y are the row index and the column index of the grid respectively, and k is the number of colors the grid has.

An empty cell in the grid will be denoted by '-'.

Output Format
Output 2 space separated integers that represent the co-ordinates of the block you choose to remove from the grid. You can output any one of the nodes of the group which you choose to remove.

Constraints
1 ≤ k ≤ 7
Each color can be any of 'V','I','B','G','Y','O','R' (VIBGYOR)

Sample Input

20 10 2
BBRBRBRBBB
RBRBRBBRRR
RRRBBRBRRR
RBRBRRRBBB
RBRBRRRRBB
RBBRBRRRRR
BBRBRRBRBR
BRBRBBRBBB
RBBRRRRRRB
BBRBRRBBRB
BBBRBRRRBB
BRBRRBRRBB
BRRBBBBBRB
RRBBRRBRRR
RRRBRRRBBB
RRRRRBBBRR
BRRRBRRRBB
BBBBRBRRRB
BRBBBBBRBB
RRRRRBBRRR
Sample Output
0 1

Explanation
In this output, the player chooses to remove all the adjacent blocks of the group (0,0), (0,1) and (1,1) which forms one group.

Challenge
Complete the function nextMove which takes integers x, y - the row and column size of the grid, color - the number of colors the grid has, and grid - a 2D array of characters which is the board.

Scoring
Your score depends on the number of blocks left (count), the size of the board and the number of colors (k).
Score = (1 - count/20) x 5 x k

if count ≥ 20, a nominal score of 0.01 would be given.

The maximum scores for the testcases of this challenge are 10, 15, 25, and 30. Hence you can get a total score of 80.
*/
#include "GameState.h"
#include "clickomania.h"
#include <fstream>
#include <queue>
#include <iostream>
#include <random>

Clickomania::Clickomania(vector<string> board) {
    this->root = new GameState(board, nullptr, 0, (Grid::Pair){-1, -1});
    this->nodeCount = 0;
    this->numRollouts = 0;
    this->runTime = 0;
}


GameState* Clickomania::selection() {
    //SELECTION/EXPANSION
    GameState* node = root;
    while (node->getChildren().size() != 0 && node->getChildren().size() <= node->rewardCount) {
        vector<GameState*> newChildren(node->getChildren());
        sort(newChildren.begin(), newChildren.end(), UCTCompare());
        node = newChildren[0];
        if (node->rewardCount == 0) return node;
    }
    if (node->getChildren().size() > 0 && node->getChildren().size() > node->rewardCount) {
        vector<GameState*> newChildren(node->getChildren());
        sort(newChildren.begin(), newChildren.end(), UCTCompare());
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
        vector<Grid::Pair> list(grid.getUniqueBlocks().begin(), grid.getUniqueBlocks().end());
        shuffle(list.begin(), list.end(), default_random_engine());
        Grid::Pair chosen = (Grid::Pair){-1, -1};
        for (Grid::Pair p : grid.getUniqueBlocks()) if (grid.colorAt(p) != color) chosen = p;
        if (chosen.row == -1) chosen = *grid.getUniqueBlocks().begin();
        grid = grid.removeSet(chosen);
        grid.createDisjoint();
    }
    //BACKPROPAGATION
    while (node != nullptr) {
        node->rewardSum += grid.getPoints();
        node->rewardCount++;
        node = node->getParent();
        if (node != nullptr) node->updateSigma();
    }
}

void Clickomania::nextMove() {
    auto start = chrono::high_resolution_clock::now();
    while (chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count() < 1750000) {
        simulation(selection());
    }
    while (!this->root->getBoardFinished()) {
        vector<GameState*> children(this->root->getChildren());
        sort(children.begin(), children.end(), CountCompare());
        Grid::Pair move = children[0]->getLastRemoved();
        cout << move.row << " " << move.col << endl;
        this->root = children[0];
    }
}

int main(int argc, char const *argv[])
{
    ifstream infile;
    infile.open("input.txt");
    int x = 0, y = 0, k = 0;
    infile >> x >> y >> k;
    vector<string> board;
    for (int i = 0; i < x; i++) {
        string s;
        infile >> s;
        board.push_back(s);
    }
    Grid::prepColors(board, k);
    Clickomania c(board);
    c.nextMove();
    infile.close();
    return 0;
}

