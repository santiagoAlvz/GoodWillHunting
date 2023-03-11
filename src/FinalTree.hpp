#ifndef FINALTREE_H
#define FINALTREE_H

#include <vector>
#include <utility>
#include <iostream>

using std::vector;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

class FinalTree{
	private:
		unsigned n;
		vector<vector<vector<pair<int,int>>>> arrangements;
		vector<vector<unsigned>> edgesCount;
	public:
		FinalTree(unsigned);
		void calculate();
		void generateEdgesCount(unsigned, unsigned);
		void printArrangements();
};

#endif
