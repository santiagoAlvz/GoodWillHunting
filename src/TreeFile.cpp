#include "TreeFile.hpp"

//Constructor for the TreeFile class
//Prints the beggining of the dot file
TreeFile::TreeFile(string filename){
    file.open(filename);

    file<<"graph {"<<endl;
    //declare the colorscheme to be used to color non-leaf nodes
    file<<"\tnode [colorscheme=blues9, fontname=\"sans\"]"<<endl;
}

//Creates a new tree, with n nodes, assigning the nodeScores as labels
void TreeFile::newTree(std::vector<unsigned> nodeScores){
    makeCurrentId(); //update id to be used for the new tree

    file<<"\t//Tree with id "<<currentId<<endl;

    //Add all nodes specified in nodeScores, with their corresponding score
    //as a label. All non-1 nodes are filled with a color on the scheme, according
    //to their value (greater the value, darker the color)
    for(unsigned long i = 0; i < nodeScores.size(); i++){
        file<<"\t"<<currentId<<i<<"[label="<<nodeScores[i]<<", shape=circle";

        //If greater than 1, fill the node with a color
        if (nodeScores[i] > 1){
            if(nodeScores[i] > 5){
                file<<", style=filled, fillcolor="<<(nodeScores[i] > 9 ? 9: nodeScores[i]);
                file<<", fontcolor=white, penwidth=0";
            } else {
                file<<", style=filled, fillcolor="<<nodeScores[i];
                file<<", fontcolor=black, penwidth=0";
            }
        }

        file<<"]"<<endl;
    }

    //Increase the number of trees used so far
    treeNumber++;
}

//Adds an edge between two nodes in the active tree
void TreeFile::addEdge(edge connection){
    file<<"\t"<<currentId<<connection.first<<" -- "<<currentId<<connection.second<<endl;
}

//Adds the file ending and closes the file
void TreeFile::close(){
    file<<"}"<<endl;
    file.close();
}

//Makes an id from the current tree number. IDs follow the pattern: a,b,c...z,aa,ab,ac...
void TreeFile::makeCurrentId(){
    currentId.clear();

    int temp = treeNumber + 1;

    //Obtain every character of the id, from the treeNumber
    do {
        temp--;
        currentId.insert(currentId.begin(),char(temp%26 + 97));
        temp -= temp%26;
        temp /= 26;

    } while (temp > 0);
}
