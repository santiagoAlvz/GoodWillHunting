#include "ArrangementsTable.hpp"

//constructor for the arrangements table
ArrangementsTable::ArrangementsTable(unsigned n){

    //resize the table to fit the specified number of elements
	this->n = n;
	this->resize(n + 1);

    //add the arrangement for 2 nodes
    if(n < 2) return;

    (*this)[2].resize(1);
    (*this)[2][0].edges.push_back(edge(0,1));
    (*this)[2][0].seed.resize(2);
    (*this)[2][0].seed[0] = 1;
    (*this)[2][0].seed[1] = 1;
}

//outputs the arrangement table as a graphviz file
void ArrangementsTable::printToFile(string filename, unsigned n, bool dm){
    TreeFile file(filename, dm);

    //if n = 1, output a single tree with a single node (special case)
    if(n == 1) {
        treeSeed s;
        file.newTree(s);
        file.newNode(0);
    }
    
    unsigned long j;

    //Make a tree for every arrangement of size n in the arrangements table
    for(unsigned long i = 0; i < (*this)[n].size(); i++){

        //Create the tree
        file.newTree((*this)[n][i].seed);

        //Add the tree's nodes,
        j = 0;

        //add branch nodes
        while(j < (*this)[n][i].seed.size()){
            file.newNode((*this)[n][i].seed[j], (*this)[n][i].seed[j]);
            j++;
        }

        //add the rest of the nodes (leaf nodes)
        while(j < n){
            file.newNode(1);
            j++;
        }

        //Add all edges of the arrangement
        for(unsigned long j = 0; j < (*this)[n][i].seed.size(); j++){
            //add them into the file
            file.addEdge((*this)[n][i].edges[j]);
        }
    }

    //Close the file
    file.close();
}

//prints number of trees for the n value
void ArrangementsTable::printStats(){
    if(n == 1){
        std::cout<<"For N = "<<n<<", there is 1 arrangement"<<std::endl;    
    } else {
        std::cout<<"For N = "<<n<<", there are "<<(*this)[n].size()<<" arrangements"<<std::endl;
    }
}
