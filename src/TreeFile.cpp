#include "TreeFile.hpp"

TreeFile::TreeFile(string filename){
    file.open(filename);

    file<<"graph {"<<endl;
    file<<"\tnode [colorscheme=blues9, fontname=\"sans\"]"<<endl;
}

void TreeFile::newTree(unsigned int n, seed nodeScores){
    treeNumber++;
    makeId();

    file<<"\t//Tree with id "<<id<<endl;
    unsigned long i = 0;
    while(i < nodeScores.size() && i < n){
        file<<"\t"<<id<<i<<"[label="<<nodeScores[i]<<",";
        if(nodeScores[i] > 5){
            file<<"style=filled, fillcolor="<<(nodeScores[i] > 9 ? 9: nodeScores[i]);
            file<<", fontcolor=white, shape=circle, penwidth=0]"<<endl;
        } else {
            file<<"style=filled, fillcolor="<<nodeScores[i];
            file<<", fontcolor=black, shape=circle, penwidth=0]"<<endl;
        }

        i++;
    }
    while(i < n){
        file<<"\t"<<id<<i<<"[label=1, shape=circle]"<<endl;
        i++;
    }
}

void TreeFile::addEdge(edge connection){
    file<<"\t"<<id<<connection.first<<" -- "<<id<<connection.second<<endl;
}

void TreeFile::close(){
    file<<"}"<<endl;
    file.close();
}

void TreeFile::makeId(){
    id.clear();

    int temp = treeNumber;

    do{
        temp--;
        id.insert(id.begin(),char(temp%26 + 97));
        temp -= temp%26;
        temp /= 26;

    } while (temp > 0);
}
