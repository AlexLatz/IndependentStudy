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
#include <fstream>
#include <queue>
#include <iostream>


void nextMove(int x, int y, int k, vector<string> board) {
    Grid grid(board);
    priority_queue<GameState, vector<GameState>, greater<GameState> > pq;
    GameState start(grid, nullptr,  0, (Grid::Pair){-1, -1});
    if (start.getBoardFinished()) cout << -1 << -1 << endl;
    pq.push(start);
    while (!pq.top().getBoardFinished() && pq.top().getUniqueNum() > 0) {
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
    ifstream infile;
    infile.open("input2.txt");
    int x = 0, y = 0, k = 0;
    infile >> x >> y >> k;
    vector<string> board;
    for (int i = 0; i < x; i++) {
        string s;
        infile >> s;
        board.push_back(s);
    }
    Grid grid(board);
    grid.createDisjoint();
    grid.printBoard();
    grid.printParents();
    //nextMove(x, y, k, board);
    infile.close();
    return 0;
}

