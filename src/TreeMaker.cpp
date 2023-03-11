#include "TreeMaker.hpp"
#include <iostream>

using std::cout;
using std::endl;

TreeMaker::TreeMaker(){}

TreeMaker::TreeMaker(vector<vector<vector<pair<int,int>>>> *arrang){
    this->arrangements = arrang;
}

void TreeMaker::createArrangements(unsigned n){}
