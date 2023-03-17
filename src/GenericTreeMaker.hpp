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
		ArrangementsTable *arrangements;
		bool hIrreducible;
		unsigned n;
		vector<vector<leafNodeCluster>> usedLeafNodeClusters;
		vector<seed> decomposedEdgeCount;
		vector<leafNodeCluster> leafNodeClusters;
	public:
		GenericTreeMaker(ArrangementsTable *, unsigned, bool);
		void createArrangement();
		void decompose(unsigned, unsigned);
		bool isUnique(edgeList, seed);
		void measureLeafNodeClusters(vector<vector<unsigned int>> &, unsigned, int, unsigned);
};

#endif