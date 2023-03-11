#include "FinalTree.hpp"

FinalTree::FinalTree(unsigned a){
    n = a;
    arrangements.resize(n + 1);

    arrangements[2].resize(1);
    arrangements[2][0].push_back(std::make_pair(0,1));
}

void FinalTree::calculate(){
    unsigned offset = n - 2;

    generateEdgesCount(offset, offset);

    for(unsigned long i = 0; i < edgesCount.size(); i++){
        for(unsigned long j = 0; j < edgesCount[i].size(); j++){
            edgesCount[i][j]++;
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
            edgesCount.push_back(edgesCount[lastPos]);
            edgesCount.back().push_back(i);
            generateEdgesCount(remaining - i, i);
        }
    }

    if(lastPos >= 0) edgesCount.erase(edgesCount.begin() + lastPos);
}

void FinalTree::printArrangements(){
    for(unsigned long i = 1; i < n + 1; i++){
        cout<<i<<":"<<endl;
        for(unsigned long j = 0; j < arrangements[i].size(); j++){
            cout<<"\t";
            for(unsigned long k = 0; k < arrangements[i][j].size(); k++){
                cout<<"["<<arrangements[i][j][k].first<<","<<arrangements[i][j][k].second<<"] ";
            }
            cout<<endl;
        }
    }

    /*for(unsigned long i = 0; i < edgesCount.size(); i++){
        for(unsigned long j = 0; j < edgesCount[i].size(); j++){
            cout<<edgesCount[i][j]<<",";
        }
        cout<<endl;
    }*/
}
