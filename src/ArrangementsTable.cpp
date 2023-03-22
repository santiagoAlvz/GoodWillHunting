#include "ArrangementsTable.hpp"

ArrangementsTable::ArrangementsTable(unsigned n){
	this->n = n;
	this->resize(n + 1);

    (*this)[2].resize(1);
    (*this)[2][0].first.push_back(edge(0,1));
}

void ArrangementsTable::printToFile(string filename, unsigned n){
    TreeFile file(filename);
    unsigned long j;

    //Make a tree for every arrangement of size n in the arrangements table
    for(unsigned long i = 0; i < (*this)[n].size(); i++){

        //Create the tree
        file.newTree();

        //Add the tree's nodes,
        j = 0;
        while(j < (*this)[n][i].second.size()){
            file.newNode((*this)[n][i].second[j], (*this)[n][i].second[j]);
            j++;
        }
        while(j < n){
            file.newNode(1);
            j++;
        }


        //Add all edges of the arrangement
        for(unsigned long j = 0; j < (*this)[n][i].first.size(); j++){
            file.addEdge((*this)[n][i].first[j]);
        }
    }

    //Close the file
    file.close();
}

void ArrangementsTable::printStats(){
    std::cout<<"For N = "<<n<<", there are "<<(*this)[n].size()<<" arrangements"<<std::endl;
}
