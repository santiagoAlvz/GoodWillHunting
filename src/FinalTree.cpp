#include "FinalTree.hpp"

FinalTree::FinalTree(unsigned a){
    n = a;
    arrangements.resize(n + 1);

    arrangements[2].resize(1);
    arrangements[2][0].push_back(std::make_pair(0,1));
}

void FinalTree::calculate(){

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
}
