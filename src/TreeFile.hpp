#ifndef TREEFILE_H
#define TREEFILE_H

#include <string>
#include <utility>
#include <fstream>
#include <iostream>

using std::pair;
using std::string;
using std::ofstream;
using std::endl;

class TreeFile {
	private:
		unsigned index;
		string id;
		ofstream file;
	public:
		TreeFile(string);
		void newTree(unsigned);
		void addEdge(pair<unsigned,unsigned>);
		void close();
};

#endif