#include "TreeFile.hpp"

//Constructor for the TreeFile class
//Prints the beggining of the dot file
TreeFile::TreeFile(string filename, bool dm){
    file.open(filename);
    darkmode = dm;

    file<<"graph {"<<'\n';
    //declare the colorscheme to be used to color non-leaf nodes
    if (!darkmode){
        file<<"\tnode [colorscheme=blues9, fontname=\"sans\"]"<<'\n';
    } else {
        file<<"\tbgcolor = \"#011437\""<<'\n';
        file<<"\tnode [colorscheme=blues9, fontname=\"sans\", color=white, fontcolor=white]"<<'\n';
        file<<"\tedge [color=white]"<<'\n';
    }
}

//Creates a new tree, and turns it into the current tree
void TreeFile::newTree(seed s){
    makeCurrentId(); //update id to be used for the new tree

    currentNode = 0;

    file<<"\t//Tree with id "<<currentId<<" and seed [";
    for(int i: s){
      file<<i<<',';
    }
    file<<"]\n";

    //Increase the number of trees used so far
    treeNumber++;
}

//Adds a new, filled node
void TreeFile::newNode(unsigned label, unsigned color){

    //normalize the color, and invert it if in dark mode
    color = color > 9 ? 9: color;
    if (darkmode){
        color = 10 - color;
    }

    file<<"\t"<<currentId<<currentNode<<"[label="<<label<<", shape=circle";
    file<<", style=filled, penwidth=0, fillcolor="<<color;

    if (color > 5){
        file<<", fontcolor=white]"<<'\n';
    } else {
        file<<", fontcolor=black]"<<'\n';
    }

    currentNode++;
}

//Adds a simple node
void TreeFile::newNode(unsigned label){
    file<<"\t"<<currentId<<currentNode<<"[label="<<label<<", shape=circle]"<<'\n';

    currentNode++;
}

//Adds an edge between two nodes in the active tree
void TreeFile::addEdge(edge connection){
    file<<"\t"<<currentId<<connection.first<<" -- "<<currentId<<connection.second<<'\n';
}

//Adds the file ending and closes the file
void TreeFile::close(){
    file<<"}"<<'\n';
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
