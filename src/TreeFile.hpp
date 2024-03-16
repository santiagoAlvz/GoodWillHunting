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
		unsigned treeNumber = 0; //number of trees built so far
		unsigned currentNode = 0; //current node to be built for the current tree
		string currentId; //Id of the current tree
		ofstream file; //name of the output file
		bool darkmode = false;
		void makeCurrentId();
	public:
		TreeFile(string, bool);
		void newTree(treeSeed);
		void newNode(unsigned, unsigned);
		void newNode(unsigned);
		void addEdge(edge);
		void close();
};

#endif
