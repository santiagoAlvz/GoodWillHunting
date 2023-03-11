#ifndef FINALTREE_H
#define FINALTREE_H

#include <vector>
#include <utility>
#include <iostream>
#include "TreeMaker.hpp"

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
		TreeMaker treeMaker;
	public:
		FinalTree(unsigned);
		void calculate();
		void generateEdgesCount(unsigned, unsigned);
		void printArrangements();
};

#endif
