#ifndef ARRANGEMENTSTABLE_H
#define ARRANGEMENTSTABLE_H

#include <iostream>
#include <vector>

using std::endl;
using std::vector;
using std::pair;
using std::make_pair;

class ArrangementsTable: public vector<vector<vector<pair<unsigned,unsigned>>>>{
	private:
		unsigned n = 0;
	public:
		ArrangementsTable(unsigned);

	friend std::ostream& operator<<(std::ostream& os, const ArrangementsTable arr){
		for(unsigned long i = 1; i < arr.n + 1; i++){
		    os<<i<<":"<<endl;
		    for(unsigned long j = 0; j < arr[i].size(); j++){
		        os<<"\t";
		        for(unsigned long k = 0; k < arr[i][j].size(); k++){
		            os<<"["<<arr[i][j][k].first<<","<<arr[i][j][k].second<<"] ";
		        }
		        os<<endl;
		    }
		}
		return os;
	}
};

#endif
