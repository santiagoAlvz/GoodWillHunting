#ifndef FINALTREE_H
#define FINALTREE_H

#include <vector>
#include <utility>
#include <iostream>
#include "TreeMaker.hpp"
#include "GenericTreeMaker.hpp"

using std::vector;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

class FinalTree: public GenericTreeMaker{
	private:
		TreeMaker treeMaker;
	public:
		FinalTree(ArrangementsTable *);
		void decompose(unsigned, unsigned);
		void createMissingArrangements(unsigned);
};

#endif
