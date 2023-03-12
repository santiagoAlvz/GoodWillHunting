#ifndef GENERICTREE_H
#define GENERICTREE_H

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include "ArrangementsTable.hpp"

using std::vector;
using std::make_pair;
using std::pair;
using std::cout;
using std::endl;

class GenericTreeMaker{
	protected:
		vector<vector<unsigned>> usedBranches;
		vector<vector<unsigned>> decomposedEdgeCount;
		ArrangementsTable *arrangements;
	public:
		GenericTreeMaker();
		GenericTreeMaker(ArrangementsTable *);
		void createArrangements(unsigned);
		bool isUnique(vector<pair<unsigned,unsigned>>);
		vector<unsigned> measureBranches(vector<vector<unsigned int>> &, unsigned, int);
		virtual void decompose(unsigned, unsigned) = 0;
		virtual void createMissingArrangements(unsigned) = 0;
};

#endif