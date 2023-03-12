#ifndef TREEMAKER_H
#define TREEMAKER_H

#include <utility>
#include <vector>
#include "GenericTreeMaker.hpp"

using std::pair;
using std::vector;

class TreeMaker: public GenericTreeMaker{
	public:
		using GenericTreeMaker::GenericTreeMaker;
		void decompose(unsigned, unsigned);
		void createMissingArrangements(unsigned);
};

#endif