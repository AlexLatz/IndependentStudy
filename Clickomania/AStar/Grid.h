#ifndef GRID_H
#define GRID_H
#include <vector>
#include <string>
#include <set>

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
#endif