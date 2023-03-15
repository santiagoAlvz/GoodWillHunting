#ifndef ARRANGEMENTSTABLE_H
#define ARRANGEMENTSTABLE_H

#include <iostream>
#include <vector>
#include <utility>
#include "TreeFile.hpp"
#include "definitions.hpp"

using std::endl;
using std::vector;
using std::string;
using std::pair;

class ArrangementsTable: public vector<vector<pair<edgeList,seed>>>{
	private:
		unsigned n = 0;
	public:
		ArrangementsTable(unsigned);
		void printToFile(string, unsigned);
		void printStats();

	friend std::ostream& operator<<(std::ostream& os, const ArrangementsTable arr){
		for(unsigned long i = 1; i < arr.n + 1; i++){
			//For every node count in the table
		    os<<i<<":"<<endl;

		    for(unsigned long j = 0; j < arr[i].size(); j++){
		    	//For each arrangement with i size
		        os<<"\t";

		        for(edge e: arr[i][j].first){
		        	//for each edge in the arrangements list
		            os<<"["<<e.first<<","<<e.second<<"] ";
		        }
		        os<<"\t[";

		        for(unsigned u: arr[i][j].second){
		        	//for each number in the seed
		        	os<<u<<",";
		        }
		        os<<"]"<<endl;
		    }
		}
		return os;
	}
};

#endif
