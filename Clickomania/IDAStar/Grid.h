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
        int numBlocks{};
        vector<string> board;
        vector<vector<Pair> > parent;
        set<Pair> blocks;
        set<Pair> uniqueBlocks;
        vector<int> colors;
        static map<char, int> colorRef;
public:
        bool disjointCreated;
        static void prepColors(vector<string> board, int k);
        Grid(vector<string>& board);
        Grid(Grid& original);
        Grid(const Grid& original);
        void prepareBlocks();
        void updateBoard();
        void printBoard();
        void printParents();
        vector<int> getColors() {return this->colors;}
        void createDisjoint();
        Pair getAbsParent(int i, int j);
        Grid removeSet(Pair p);
        int getNumBlocks() const {return this->numBlocks;}
        const int getNumUniqueBlocks() const {return this->uniqueBlocks.size();}
        set<Pair>& getBlocks();
        set<Pair>& getUniqueBlocks();
        bool operator== (const Grid& g) const {
            return this->blocks==g.blocks && this->uniqueBlocks==g.uniqueBlocks && this->numBlocks==g.numBlocks;
        }
};
#endif