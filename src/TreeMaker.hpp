#ifndef TREEMAKER_H
#define TREEMAKER_H

#include <utility>
#include <vector>

using std::pair;
using std::vector;

class TreeMaker{
	private:
		unsigned n;
		vector<vector<vector<pair<unsigned,unsigned>>>> *arrangements;
		vector<vector<unsigned>> usedBranches;
	public:
		TreeMaker();
		TreeMaker(vector<vector<vector<pair<unsigned,unsigned>>>> *);
		void createArrangements(unsigned);
		void decompose(vector<vector<unsigned>> &,unsigned, unsigned);
		vector<unsigned> createSingleArrangement(unsigned);
		bool isUnique(vector<pair<unsigned,unsigned>>);
		vector<unsigned> measureBranches(vector<vector<unsigned>> &, unsigned, int);
};

#endif