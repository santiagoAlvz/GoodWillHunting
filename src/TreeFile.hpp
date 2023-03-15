#ifndef TREEFILE_H
#define TREEFILE_H

#include <string>
#include <fstream>
#include <iostream>
#include "definitions.hpp"

using std::string;
using std::ofstream;
using std::endl;

class TreeFile {
	private:
		unsigned treeNumber = 0;
		string id;
		ofstream file;
		void makeId();
	public:
		TreeFile(string);
		void newTree(unsigned, seed);
		void addEdge(edge);
		void close();
};

#endif