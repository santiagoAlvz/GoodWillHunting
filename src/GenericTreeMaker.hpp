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
		vector<vector<unsigned>> usedLevelDistributions;
		vector<vector<unsigned>> decomposedEdgeCount;
		vector<unsigned> levelDistribution;
		ArrangementsTable *arrangements;
	public:
		GenericTreeMaker();
		GenericTreeMaker(ArrangementsTable *);
		void createArrangements(unsigned);
		bool isUnique(vector<pair<unsigned,unsigned>>, vector<unsigned>);
		void measureLevelDistribution(vector<vector<unsigned int>> &, unsigned, int, unsigned);
		virtual void decompose(unsigned, unsigned) = 0;
		virtual void createMissingArrangements(unsigned) = 0;
};

#endif