#include "ArrangementsTable.hpp"

ArrangementsTable::ArrangementsTable(unsigned n){
	this->n = n;
	this->resize(n + 1);

    (*this)[2].resize(1);
    (*this)[2][0].first.push_back(edge(0,1));
}

void ArrangementsTable::printToFile(string filename, unsigned n){
    TreeFile file(filename);

    for(unsigned long i = 0; i < (*this)[n].size(); i++){
        file.newTree(n, (*this)[n][i].second );
        for(unsigned long j = 0; j < (*this)[n][i].first.size(); j++){
            file.addEdge((*this)[n][i].first[j]);
        }
    }

    file.close();
}

void ArrangementsTable::printStats(){
    std::cout<<"For N = "<<n<<", there are "<<(*this)[n].size()<<" arrangements"<<std::endl;
}
