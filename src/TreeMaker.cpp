#include "TreeMaker.hpp"

using namespace std;

//constructor for the class
TreeMaker::TreeMaker(ArrangementsTable *arr, unsigned nodes, bool hi){

    //assign parameters to the attributes
    arrangements = arr;
    n = nodes;
    minSeedValue = hi ? 2 : 1;

    //create arrangements for the n value
    createArrangement();
}

//creates all unique arrangements for the n value
void TreeMaker::createArrangement(){

    //generates all the seeds for the n value
    decompose();

    vector<vector<unsigned>> adjList(n);
    pair<edgeList,seed>* currentArrangement;
    unsigned seedLength;
    bool valid = true;

    //build the first tree, if there's a seed for it (a single branch node)
    if (seeds.size() > 0){
        (*arrangements)[n].resize(1);
        currentArrangement = &(*arrangements)[n].back();

        (*currentArrangement).second.resize(n);
        (*currentArrangement).second[0] = n - 1;

        for(unsigned long i = 1; i < n; i++){
            //relate all nodes to node 0
            (*currentArrangement).first.push_back(edge(0, i));
            (*currentArrangement).second[i] = 1;
        }
        
    }

    //for every generated seed, excluding the first one
    for(unsigned long i = 1; i < seeds.size(); i++){
        seedLength = seeds[i].size();

        //if there aren't any arrangements for the number of branch nodes we need,
        //make a recursive call to create them
        if((*arrangements)[seedLength].empty()){

            //Create the arrangements for its size
            TreeMaker secondaryTreeMaker(arrangements, seedLength, false);
        }

        //for every arrangement that fits our branch nodes
        //(*arrangements)[seedLength][j] is our arrangement
        for(unsigned long j = 0; j < (*arrangements)[seedLength].size(); j++){

            //register if the base arrangement is linear
            bool isLinear = (seedLength == 2 || ((*arrangements)[seedLength][j].second.size() % 2 == 0 && (*arrangements)[seedLength][j].second[0] == 2));

            //clear the clusters list, since only trees that come from the same
            //branch node arrangement can be identical
            usedLeafNodeCounts.clear();

            //for every possible way to assign our branch nodes into the arrangement
            do {

                //Have we already used an identical tree?
                if(validateTree((*arrangements)[seedLength][j], seeds[i], true)){
                    addTree(seeds[i], (*arrangements)[seedLength][j].first);
                }

            } while ( std::prev_permutation(seeds[i].begin(),seeds[i].end()));
        }
    }
}

bool TreeMaker::validateTree(pair<edgeList,seed> arrangement, seed s, bool checkForLinear = true){
    unsigned branchNodes = s.size();

    vector<unsigned> depth(branchNodes,0);
    for(edge e: arrangement.first){

        //Calculate depth (distance from node 0) for all nodes in the arrangement
        depth[e.second] = depth[e.first] + 1;
    }

    vector<unsigned> leafNodeCount = s;

    //if any of the branch nodes already has exceded its edge count, it isn't valid
    for(unsigned k = 0; k < leafNodeCount.size(); k++){
        if (leafNodeCount[k] < arrangement.second[k]){
            return false;
        } else {
            leafNodeCount[k] -= arrangement.second[k];
        }
    }

    for(int k = branchNodes - 2; k >= 0; k--){
        
        edge e = arrangement.first[k];

        //Since trees are built inside-out, we know that edges go as [closer to node 0 node, further away node]
        leafNodeCount[e.first] += leafNodeCount[e.second];
    }

    int first = 1;
    for(unsigned k = 2; k < branchNodes; k++){
        if(depth[first] != depth[k]){
            std::sort(leafNodeCount.begin() + first, leafNodeCount.begin() + k);

            first = k;
        }
    }
    std::sort(leafNodeCount.begin() + first, leafNodeCount.begin() + branchNodes);

    if (usedLeafNodeCounts.find(leafNodeCount) == usedLeafNodeCounts.end()){
        usedLeafNodeCounts.insert(leafNodeCount);

        if(checkForLinear && (branchNodes == 2 || arrangement.second.size() % 2 == 0 && arrangement.second[0] == 2)){
            for(int i = 0; i < branchNodes; i += 2){
                std::swap(s[i], s[i+1]);
            }

            validateTree(arrangement, s, false);
        }

        return true;
    }

    return false;
}

void TreeMaker::addTree(seed s, edgeList initialEdges){
    (*arrangements)[n].resize((*arrangements)[n].size() + 1);
    
    unsigned initialEdge = 0;
    unsigned lastNodeUsed = s.size();

    seed pending = s;

    //for every origin node
    for(int i = 0; i < s.size(); i++){

        while(initialEdge < initialEdges.size() && initialEdges[initialEdge].first == i){
            (*arrangements)[n].back().first.push_back(initialEdges[initialEdge]);
            pending[i]--;
            pending[initialEdges[initialEdge].second]--;
            initialEdge++;
        }

        while(pending[i] >= 1){
            (*arrangements)[n].back().first.push_back(edge(i,lastNodeUsed));
            lastNodeUsed++;
            pending[i]--;
        }
    }

    (*arrangements)[n].back().second = s;
    while((*arrangements)[n].back().second.size() < n){
        (*arrangements)[n].back().second.push_back(1);
    }
}

//main function for decomposing the n value, a.k.a. splitting it into unique sums
void TreeMaker::decompose(){
    if(n <= 2) return;

    if(n - 1 > minSeedValue){
        //add the first seed (one single branch node)
        seeds.resize(1);
        seeds[0].push_back(n - 1);
    }

    //traverse the rest of the possible seed values
    for(unsigned i = n - 3; i >= minSeedValue; i--){

        //if using this as a component doesn't leave us with a less than minimum pending value
        if ( (n - 2) - i >= minSeedValue){

            //add a row to the seeds list with i as a value, and execute
            //the decomposition process for the pending value.
            //This acts as a half-constructed seed
            seeds.resize(seeds.size() + 1);
            seeds.back().push_back(i + 1);
            decompose((n - 2) - i, i);

        }
    }
}

//recursive function for decomposition
void TreeMaker::decompose(unsigned remaining, unsigned max){

    //if a decomposition is complete (i.e. there aren't any pending values), we are done
    if (remaining == 0) return;

    //position in the seeds list of the half-constructed seed to use
    int parentPos = seeds.size() - 1;

    //for all possible seed values (equal or lesser than the previous value used)
    for(unsigned i = std::min(remaining, max); i >= minSeedValue; i--){

        //if using this as a component doesn't leave us with a less than minimum pending value
        if (i == remaining || remaining - i >= minSeedValue){

            //duplicate the half-constructed seed, and add the iterated component
            seeds.push_back(seeds[parentPos]);
            seeds.back().push_back(i + 1);
            decompose(remaining - i, i);
        }
    }

    //delete the half-constructed seed
    seeds.erase(seeds.begin() + parentPos);
}
