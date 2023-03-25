#include "ArrangementsTable.hpp"

//constructor for the arrangements table
ArrangementsTable::ArrangementsTable(unsigned n){

    //resize the table to fit the specified number of elements
	this->n = n;
	this->resize(n + 1);

    //add the arrangement for 2 nodes
    (*this)[2].resize(1);
    (*this)[2][0].first.push_back(edge(0,1));
}

//outputs the arrangement table as a graphviz file
void ArrangementsTable::printToFile(string filename, unsigned n){
    TreeFile file(filename);
    unsigned long j;

    //Make a tree for every arrangement of size n in the arrangements table
    for(unsigned long i = 0; i < (*this)[n].size(); i++){

        //Create the tree
        file.newTree();

        //Add the tree's nodes,
        j = 0;

        //add branch nodes
        while(j < (*this)[n][i].second.size()){
            file.newNode((*this)[n][i].second[j], (*this)[n][i].second[j]);
            j++;
        }

        //add the rest of the nodes (leaf nodes)
        while(j < n){
            file.newNode(1);
            j++;
        }

        //Add all edges of the arrangement
        for(unsigned long j = 0; j < (*this)[n][i].first.size(); j++){
            //add them into the file
            file.addEdge((*this)[n][i].first[j]);
        }
    }

    //Close the file
    file.close();
}

//prints number of trees for the n value
void ArrangementsTable::printStats(){
    std::cout<<"For N = "<<n<<", there are "<<(*this)[n].size()<<" arrangements"<<std::endl;
}
