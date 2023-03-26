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

    edgeList temp;
    vector<unsigned> usedEdges;
    unsigned seedLength;
    bool valid = true;
    unsigned cont;

    //build the first tree (a single branch node)
    for(unsigned long i = 1; i < n; i++){

        //relate all nodes to node 0
        temp.push_back(edge(0, i));
    }
    (*arrangements)[n].push_back(make_pair(temp,seeds[0])); //add the tree to the arrangements table

    //for every generated seed, excluding the first one
    for(unsigned long i = 1; i < seeds.size(); i++){
        seedLength = seeds[i].size();
        temp.clear();

        //if there aren't any arrangements for the number of branch nodes we need,
        //make a recursive call to create them
        if((*arrangements)[seedLength].empty()){

            //Create the arrangements for its size
            TreeMaker secondaryTreeMaker(arrangements, seedLength, false);
        }

        //for every arrangement that fits our branch nodes
        //(*arrangements)[seedLength][j] is our arrangement
        for(unsigned long j = 0; j < (*arrangements)[seedLength].size(); j++){
            usedLeafNodeClusters.clear();

            //for every possible way to assign our branch nodes into the arrangement
            do {

                valid = true;

                for(unsigned long k = 0; k < (*arrangements)[seedLength][j].second.size(); k++){
                    if (seeds[i][k] < (*arrangements)[seedLength][j].second[k]){
                        valid = false;
                        break;
                    }
                }

                if (!valid) continue;

                vector<vector<unsigned>> adjList(n);

                for(edge k : (*arrangements)[seedLength][j].first){
                    adjList[k.first].push_back(k.second);
                    adjList[k.second].push_back(k.first);
                }

                cont = 0;
                for(unsigned long k = seedLength; k < n; k++){

                    if (seeds[i][cont] == adjList[cont].size()){
                        cont++;
                        k--;
                        continue;
                    }

                    adjList[cont].push_back(k);
                    adjList[k].push_back(cont);
                }

                if(isUnique(adjList, (*arrangements)[seedLength][j].second)){

                    cont = 0;
                    temp.clear();

                    while (cont < n){

                        if (adjList[cont].empty()){
                            cont++;
                            continue;
                        }

                        temp.push_back(edge(cont,adjList[cont].front()));
                        adjList[adjList[cont].front()].erase(adjList[adjList[cont].front()].begin());
                        adjList[cont].erase(adjList[cont].begin());
                    }

                    (*arrangements)[n].push_back(make_pair(temp, seeds[i]));
                }

            } while ( std::prev_permutation(seeds[i].begin(),seeds[i].end()));
        }
    }
}

//main function for decomposing the n value, a.k.a. splitting it into unique sums
void TreeMaker::decompose(){

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

bool TreeMaker::isUnique(vector<vector<unsigned>> adjList, seed arr){
    leafNodeClusters.clear();

    measureLeafNodeClusters(adjList,0, -1, 0);

    if (usedLeafNodeClusters.find(leafNodeClusters) != usedLeafNodeClusters.end()) return false;

    usedLeafNodeClusters.insert(leafNodeClusters);

    if(arr.size() == 0 || (arr.size() % 2 == 0 && arr.front() == 2 && arr.back() == 2)){

        leafNodeClusters.clear();
        measureLeafNodeClusters(adjList, 1, -1, 0);
        usedLeafNodeClusters.insert(leafNodeClusters);
    }

    return true;
}

void TreeMaker::measureLeafNodeClusters(vector<vector<unsigned int>> &adjList, unsigned node, int parent, unsigned level){

    int cont = 0;
    for(int neighbour: adjList[node]){
        if(neighbour != parent){
            if(adjList[neighbour].size() == 1){
                cont++;
            }
            measureLeafNodeClusters(adjList, neighbour, node, level + 1);
        }
    }

    if (cont > 0) leafNodeClusters.insert(leafNodeCluster(level, cont));
}
