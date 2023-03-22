#include "TreeFile.hpp"

//Constructor for the TreeFile class
//Prints the beggining of the dot file
TreeFile::TreeFile(string filename){
    file.open(filename);

    file<<"graph {"<<endl;
    //declare the colorscheme to be used to color non-leaf nodes
    file<<"\tnode [colorscheme=blues9, fontname=\"sans\"]"<<endl;
}

//Creates a new tree, and turns it into the current tree
void TreeFile::newTree(){
    makeCurrentId(); //update id to be used for the new tree

    currentNode = 0;

    file<<"\t//Tree with id "<<currentId<<endl;

    //Increase the number of trees used so far
    treeNumber++;
}

//Adds a new, filled node
void TreeFile::newNode(unsigned label, unsigned color){
    file<<"\t"<<currentId<<currentNode<<"[label="<<label<<", shape=circle";
    file<<", style=filled, penwidth=0, fillcolor="<<(color > 9 ? 9: color);

    if (color > 5){
        file<<", fontcolor=white]"<<endl;
    } else {
        file<<", fontcolor=black]"<<endl;
    }

    currentNode++;
}

//Adds a simple node
void TreeFile::newNode(unsigned label){
    file<<"\t"<<currentId<<currentNode<<"[label="<<label<<", shape=circle]"<<endl;

    currentNode++;
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
