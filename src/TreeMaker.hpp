/* Header file for the class TreeMaker
   TreeMaker. Creates all possible trees with a given amount of nodes, and
   saves them in an Arrangements Table */

#ifndef GENERICTREE_H
#define GENERICTREE_H

#include <vector>
#include <utility>
#include <algorithm>
#include "ArrangementsTable.hpp"
#include "definitions.hpp"

using std::vector;
using std::make_pair;
using std::pair;

class TreeMaker{
	protected:
		ArrangementsTable *arrangements; //pointer to an arrangements table
		unsigned minSeedValue; //minimum edge count that a branch node may have. Defines if a tree is
							   //irreducible or not
		unsigned n; //number of nodes
		vector<seed> seeds; //generated seeds for n

		//used for validation of unique trees
		vector<vector<leafNodeCluster>> usedLeafNodeClusters; //leafNodeClusters used for a given seed and
															  //branch node arrangement
		vector<leafNodeCluster> leafNodeClusters; //leafNodeClusters of a given tree

	public:
		TreeMaker(ArrangementsTable *, unsigned, bool);
		void createArrangement();
		void decompose();
		void decompose(unsigned, unsigned);
		bool isUnique(edgeList, seed);
		void measureLeafNodeClusters(vector<vector<unsigned int>> &, unsigned, int, unsigned);
};

#endif