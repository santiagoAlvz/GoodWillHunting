#include "FinalTreeMaker.hpp"

FinalTreeMaker::FinalTreeMaker(ArrangementsTable *arr){
    arrangements = arr;

    treeMaker = TreeMaker(arr);
}

void FinalTreeMaker::decompose(unsigned remaining, unsigned max){
    int lastPos = decomposedEdgeCount.size() - 1;

    if (remaining == 0) return;

    for(unsigned i = (remaining < max) ? remaining : max; i > 1; i--){
        if(remaining == i){
            if(lastPos < 0){
                decomposedEdgeCount.resize(1);
                decomposedEdgeCount.back().push_back(i);
            } else {
                decomposedEdgeCount.push_back(decomposedEdgeCount[lastPos]);
                decomposedEdgeCount.back().push_back(i);
            }
        } else if ( remaining - i > 1) {
            if(lastPos < 0){
                decomposedEdgeCount.resize(decomposedEdgeCount.size() + 1);
            } else {
                decomposedEdgeCount.push_back(decomposedEdgeCount[lastPos]);
            }

            decomposedEdgeCount.back().push_back(i);
            decompose(remaining - i, i);
        }
    }

    if(lastPos >= 0) decomposedEdgeCount.erase(decomposedEdgeCount.begin() + lastPos);
}

void FinalTreeMaker::createMissingArrangements(unsigned n){
    treeMaker.createArrangements(n);
}
