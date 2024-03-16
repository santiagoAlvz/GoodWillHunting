/* Header file for the class ArrangementsTable
 * ArrangementsTable. Stores all the all trees generated during execution
 */

#ifndef ARRANGEMENTSTABLE_H
#define ARRANGEMENTSTABLE_H

#include <iostream>
#include <vector>
#include <utility>
#include "TreeFile.hpp"
#include "Tree.hpp"
#include "definitions.hpp"

using std::endl;
using std::vector;
using std::string;
using std::pair;

class ArrangementsTable: public vector<vector<Tree>>{
	private:
		unsigned n = 0; //initial n value
	public:
		ArrangementsTable(unsigned);
		void printToFile(string, unsigned, bool);
		void printStats();

	//outputs the contents of the arrangement table into the standard output
	friend std::ostream& operator<<(std::ostream& os, const ArrangementsTable arr){

		for(unsigned long i = 1; i < arr.n + 1; i++){
		    //For every node count in the table
		    os<<i<<":"<<'\n';

		    for(unsigned long j = 0; j < arr[i].size(); j++){
		    	//For each arrangement with i size
		        os<<"\t";

		        for(edge e: arr[i][j].edges){
		        	//for each edge in the arrangements list
		            os<<"["<<e.first<<","<<e.second<<"] ";
		        }
		        os<<"\t[";

		        for(unsigned u: arr[i][j].seed){
		        	//for each number in the seed
		        	os<<u<<",";
		        }
		        os<<"]"<<'\n';
		    }
		}
		return os;
	}
};

#endif
