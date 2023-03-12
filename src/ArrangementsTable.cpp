#include "ArrangementsTable.hpp"

ArrangementsTable::ArrangementsTable(unsigned n){
	this->n = n;
	this->resize(n + 1);

    (*this)[2].resize(1);
    (*this)[2][0].push_back(std::make_pair(0,1));
}

void ArrangementsTable::print(){
    for(unsigned long i = 1; i < n + 1; i++){
        cout<<i<<":"<<endl;
        for(unsigned long j = 0; j < (*this)[i].size(); j++){
            cout<<"\t";
            for(unsigned long k = 0; k < (*this)[i][j].size(); k++){
                cout<<"["<<(*this)[i][j][k].first<<","<<(*this)[i][j][k].second<<"] ";
            }
            cout<<endl;
        }
    }
}
