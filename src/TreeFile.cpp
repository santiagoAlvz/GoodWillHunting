#include "TreeFile.hpp"

TreeFile::TreeFile(string filename){
    file.open(filename);

    file<<"graph {"<<endl;
}

void TreeFile::newTree(unsigned int n){
}

void TreeFile::addEdge(pair<unsigned int, unsigned int> edge){
}

void TreeFile::close(){
    file<<"}"<<endl;
    file.close();
}
