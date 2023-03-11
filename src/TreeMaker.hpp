#ifndef TREEMAKER_H
#define TREEMAKER_H

#include <utility>
#include <vector>

using std::pair;
using std::vector;

class TreeMaker{
	private:
		unsigned n;
		vector<vector<vector<pair<int,int>>>> *arrangements;
	public:
		TreeMaker();
		TreeMaker(vector<vector<vector<pair<int,int>>>> *);
		void createArrangements(unsigned);
};

#endif