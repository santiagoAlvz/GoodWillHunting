/* Header file for the class TreeFile
 * TreeFile. Outputs trees (in dot format) to a file
 */

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
		string currentId;
		ofstream file; //name of the output file
		void makeCurrentId();
	public:
		TreeFile(string);
		void newTree(std::vector<unsigned>);
		void addEdge(edge);
		void close();
};

#endif