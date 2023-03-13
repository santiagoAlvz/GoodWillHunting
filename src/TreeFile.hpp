#ifndef TREEFILE_H
#define TREEFILE_H

#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>

using std::pair;
using std::string;
using std::ofstream;
using std::endl;
using std::vector;

class TreeFile {
	private:
		unsigned treeNumber = 0;
		string id;
		ofstream file;
		void makeId();
	public:
		TreeFile(string);
		void newTree(unsigned, vector<unsigned>);
		void addEdge(pair<unsigned,unsigned>);
		void close();
};

#endif