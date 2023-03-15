#ifndef GENERICTREE_H
#define GENERICTREE_H

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include "ArrangementsTable.hpp"
#include "definitions.hpp"

using std::vector;
using std::make_pair;
using std::pair;

class GenericTreeMaker{
	protected:
		vector<vector<leafNodeCluster>> usedLeafNodeClusters;
		vector<seed> decomposedEdgeCount;
		vector<leafNodeCluster> leafNodeClusters;
		ArrangementsTable *arrangements;
	public:
		GenericTreeMaker();
		GenericTreeMaker(ArrangementsTable *);
		void createArrangements(unsigned);
		bool isUnique(edgeList, seed);
		void measureLeafNodeClusters(vector<vector<unsigned int>> &, unsigned, int, unsigned);
		virtual void decompose(unsigned, unsigned) = 0;
		virtual void createMissingArrangements(unsigned) = 0;
};

#endif