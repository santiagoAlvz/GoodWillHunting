#include "FinalTree.hpp"

FinalTree::FinalTree(unsigned a, ArrangementsTable *arr){
    arrangements = arr;

    treeMaker = TreeMaker(arr);
    n = a;
}

void FinalTree::calculate(){
    unsigned offset = n - 2;

    generateEdgesCount(offset, offset);

    for(unsigned long i = 0; i < edgesCount.size(); i++){
        for(unsigned long j = 0; j < edgesCount[i].size(); j++){
            edgesCount[i][j]++;
        }
    }

    (*arrangements)[n].resize(1);
    for(unsigned long i = 1; i <= edgesCount[0][0]; i++){
        (*arrangements)[n].back().push_back(make_pair(0,i));
    }

    vector<unsigned> usedEdges;

    for(unsigned long i = 1; i < edgesCount.size(); i++){
        usedEdges = vector<unsigned>(edgesCount[i].size(),0);
        if(edgesCount[i].size() == 2){
            usedEdges[0] = 1;
            usedEdges[1] = 1;
            (*arrangements)[n].push_back((*arrangements)[2][0]);
            while((*arrangements)[n].back().size() < n - 1){
                if(edgesCount[i][0] > usedEdges[0]){
                    (*arrangements)[n].back().push_back(make_pair(0, (*arrangements)[n].back().size() + 1));
                    usedEdges[0]++;
                } else {
                    (*arrangements)[n].back().push_back(make_pair(1, (*arrangements)[n].back().size() + 1));
                    usedEdges[1]++;
                }
            }
        } else {
            if((*arrangements)[edgesCount[i].size()].empty()){
                //Create the (*arrangements) for its size
                treeMaker.createArrangements(edgesCount[i].size());
            }
        }
    }
}

void FinalTree::generateEdgesCount(unsigned remaining, unsigned max){
    int lastPos = edgesCount.size() - 1;

    if (remaining == 0) return;

    for(unsigned i = (remaining < max) ? remaining : max; i > 1; i--){
        if(remaining == i){
            if(lastPos < 0){
                edgesCount.resize(1);
                edgesCount.back().push_back(i);
            } else {
                edgesCount.push_back(edgesCount[lastPos]);
                edgesCount.back().push_back(i);
            }
        } else if ( remaining - i > 1) {
            if(lastPos < 0){
                edgesCount.resize(edgesCount.size() + 1);
            } else {
                edgesCount.push_back(edgesCount[lastPos]);
            }

            edgesCount.back().push_back(i);
            generateEdgesCount(remaining - i, i);
        }
    }

    if(lastPos >= 0) edgesCount.erase(edgesCount.begin() + lastPos);
}
