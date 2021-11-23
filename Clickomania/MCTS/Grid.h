#ifndef GRID_H
#define GRID_H
#include <vector>
#include <string>
#include <set>
#include <map>

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
#endif