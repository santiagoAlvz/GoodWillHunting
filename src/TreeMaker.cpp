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
    unsigned length;
    bool valid = true;
    unsigned cont;

    for(unsigned long i = 0; i < seeds.size(); i++){
        length = seeds[i].size();
        temp.clear();

        if(length == 1){
            while(temp.size() < n - 1){
                temp.push_back(edge(0, temp.size() + 1));
            }
            (*arrangements)[n].push_back(make_pair(temp,seeds[i]));
            continue;
        }

        if((*arrangements)[seeds[i].size()].empty()){
            //Create the arrangements for its size
            TreeMaker secondaryTreeMaker(arrangements, seeds[i].size(), false);
        }

        for(unsigned long j = 0; j < (*arrangements)[length].size(); j++){
            usedLeafNodeClusters.clear();

            do {

                usedEdges = vector<unsigned>(length, 0);
                valid = true;

                for(unsigned long k = 0; k < (*arrangements)[length][j].first.size(); k++){
                    usedEdges[(*arrangements)[length][j].first[k].first]++;
                    usedEdges[(*arrangements)[length][j].first[k].second]++;
                }

                for(unsigned long k = 0; k < length; k++){
                    if(usedEdges[k] > seeds[i][k]) valid = false;
                }

                if(!valid) continue;

                temp = (*arrangements)[length][j].first;
                cont = 0;
                while(temp.size() < n - 1){

                    while(usedEdges[cont] == seeds[i][cont]){
                        cont++;
                    }
                    temp.push_back(edge(cont, temp.size() + 1));
                    usedEdges[cont]++;
                }

                if(isUnique(temp, (*arrangements)[length][j].second)){
                    (*arrangements)[n].push_back(make_pair(temp,seeds[i]));
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

bool TreeMaker::isUnique(edgeList edges, seed arr){
    vector<vector<unsigned>> adjList(edges.size() + 1);
    leafNodeClusters.clear();

    for(unsigned long i = 0; i < edges.size(); i++){
        adjList[edges[i].first].push_back(edges[i].second);
        adjList[edges[i].second].push_back(edges[i].first);
    }

    measureLeafNodeClusters(adjList,0, -1, 0);
    std::sort(leafNodeClusters.begin(), leafNodeClusters.end());

    for(unsigned long i = 0; i < usedLeafNodeClusters.size(); i++){
        if(leafNodeClusters == usedLeafNodeClusters[i]){
            return false;
        }
    }

    usedLeafNodeClusters.push_back(leafNodeClusters);

    if(arr.size() == 0 || (arr.size() % 2 == 0 && arr.front() == 2 && arr.back() == 2)){

        leafNodeClusters.clear();
        measureLeafNodeClusters(adjList, 1, -1, 0);
        std::sort(leafNodeClusters.begin(), leafNodeClusters.end());
        usedLeafNodeClusters.push_back(leafNodeClusters);
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

    if (cont > 0) leafNodeClusters.push_back(leafNodeCluster(level, cont));

}
