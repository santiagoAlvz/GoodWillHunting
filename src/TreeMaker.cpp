#include "TreeMaker.hpp"

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
    unsigned cont;

    //build the first tree (a single branch node)
    (*arrangements)[n].resize(1);
    currentArrangement = &(*arrangements)[n].back();

    for(unsigned long i = 1; i < n; i++){
        //relate all nodes to node 0
        (*currentArrangement).first.push_back(edge(0, i));
    }
    (*currentArrangement).second = seeds[0];

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

            //clear the clusters list, since only trees that come from the same
            //branch node arrangement can be identical
            usedLeafNodeClusters.clear();

            //for every possible way to assign our branch nodes into the arrangement
            do {

                valid = true; //the branch node arrangement is valid by default

                //if any of the branch nodes already has exceded its edge count, it isn't valid
                for(unsigned k = 0; k < (*arrangements)[seedLength][j].second.size(); k++){
                    if (seeds[i][k] < (*arrangements)[seedLength][j].second[k]){
                        valid = false;
                        break;
                    }
                }

                //if not valid, continue to the next positions of our branch nodes
                if (!valid) continue;

                //make an adjacency list from the edges of our branch node arrangement
                adjList.clear();
                adjList.resize(n);

                for(edge k : (*arrangements)[seedLength][j].first){
                    adjList[k.first].push_back(k.second);
                    adjList[k.second].push_back(k.first);
                }

                //complete the adjacency list by completing the edge count of every branch node
                cont = 0;
                for(unsigned k = seedLength; k < n; k++){

                    if (seeds[i][cont] == adjList[cont].size()){
                        cont++;
                        k--;
                        continue;
                    }

                    adjList[cont].push_back(k);
                    adjList[k].push_back(cont);
                }

                //verify if the generated tree is unique
                if(isUnique(adjList, (*arrangements)[seedLength][j].second)){

                    //if it is, add it to the arrangements table

                    //create a row in the arr table
                    (*arrangements)[n].resize((*arrangements)[n].size() + 1);
                    currentArrangement = &(*arrangements)[n].back();

                    //add every edge into the row (ascending only to ignore duplicates)
                    for (unsigned k = 0; k < seedLength; k++){
                        for(unsigned l = 0; l < adjList[k].size(); l++){
                            if (adjList[k][l] > k){
                                (*currentArrangement).first.push_back(edge(k, adjList[k][l]));
                            }
                        }
                    }

                    //add the seed to the row
                    (*currentArrangement).second = seeds[i];
                }

            } while ( std::prev_permutation(seeds[i].begin(),seeds[i].end()));
        }
    }
}

//main function for decomposing the n value, a.k.a. splitting it into unique sums
void TreeMaker::decompose(){
    if(n < 4) return;

    //add the first seed (one single branch node)
    seeds.resize(1);
    seeds[0].push_back(n - 1);

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

//returns if a tree is unique or has already been generated
bool TreeMaker::isUnique(vector<vector<unsigned>> &adjList, seed arr){
    leafNodeClusters.clear();

    //measure the leaf node clusters of a tree. Stores them into leafNodeClusters
    measureLeafNodeClusters(adjList,0, -1, 0);

    //if the used clusters contains a cluster identical to our current tree's,
    //the tree is a duplicate
    if (usedLeafNodeClusters.find(leafNodeClusters) != usedLeafNodeClusters.end()) return false;

    //add our tree clusters to the cluster list
    usedLeafNodeClusters.insert(leafNodeClusters);

    //if we have a linear branch node arrangement, count the clusters from node 1 too, so we don't get
    //two mirrored trees (which are duplicates)
    if(arr.size() == 0 || (arr.size() % 2 == 0 && arr.front() == 2 && arr.back() == 2)){

        leafNodeClusters.clear();
        measureLeafNodeClusters(adjList, 1, -1, 0);
        usedLeafNodeClusters.insert(leafNodeClusters);
    }

    //the tree is unique
    return true;
}

//recursive function to count group of leaf nodes that descend from the same branch node
void TreeMaker::measureLeafNodeClusters(vector<vector<unsigned int>> &adjList, unsigned node, int parent, unsigned level){

    int cont = 0; //variable to count the leaf nodes that descend from the current node

    //for every neighbouring node
    for(int neighbour: adjList[node]){

        //excluding the node where we came from
        if(neighbour != parent){

            //if the node is a leaf, increase the count
            if(adjList[neighbour].size() == 1){
                cont++;
            } else { //otherwise, repeat the same process for it
                measureLeafNodeClusters(adjList, neighbour, node, level + 1);
            }
        }
    }

    //if this node had any leafs, note them in the clusters list
    if (cont > 0) leafNodeClusters.insert(leafNodeCluster(level, cont));
}
