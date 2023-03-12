#ifndef ARRANGEMENTSTABLE_H
#define ARRANGEMENTSTABLE_H

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;

class ArrangementsTable: public vector<vector<vector<pair<unsigned,unsigned>>>>{
	private:
		unsigned n = 0;
	public:
		ArrangementsTable(unsigned);
		void print();
};

#endif
