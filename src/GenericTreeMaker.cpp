#include "GenericTreeMaker.hpp"

GenericTreeMaker::GenericTreeMaker(){}

GenericTreeMaker::GenericTreeMaker(ArrangementsTable *arr){
    this->arrangements = arr;
}

void GenericTreeMaker::createArrangements(unsigned n){
    decomposedEdgeCount.clear();
    decompose(n - 2, n - 2);

    for(unsigned long i = 0; i < decomposedEdgeCount.size(); i++){
        for(unsigned long j = 0; j < decomposedEdgeCount[i].size(); j++){
            decomposedEdgeCount[i][j]++;
        }
    }

    edgeList temp;
    vector<unsigned> usedEdges;
    unsigned length;
    bool valid = true;
    unsigned cont;

    for(unsigned long i = 0; i < decomposedEdgeCount.size(); i++){
        length = decomposedEdgeCount[i].size();
        temp.clear();

        if(length == 1){
            while(temp.size() < n - 1){
                temp.push_back(edge(0, temp.size() + 1));
            }
            (*arrangements)[n].push_back(make_pair(temp,decomposedEdgeCount[i]));
            continue;
        }

        if((*arrangements)[decomposedEdgeCount[i].size()].empty()){
            //Create the arrangements for its size
            createMissingArrangements(decomposedEdgeCount[i].size());
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
                    if(usedEdges[k] > decomposedEdgeCount[i][k]) valid = false;
                }

                if(!valid) continue;

                temp = (*arrangements)[length][j].first;
                cont = 0;
                while(temp.size() < n - 1){

                    while(usedEdges[cont] == decomposedEdgeCount[i][cont]){
                        cont++;
                    }
                    temp.push_back(edge(cont, temp.size() + 1));
                    usedEdges[cont]++;
                }

                if(isUnique(temp, (*arrangements)[length][j].second)){
                    (*arrangements)[n].push_back(make_pair(temp,decomposedEdgeCount[i]));
                }

            } while ( std::prev_permutation(decomposedEdgeCount[i].begin(),decomposedEdgeCount[i].end()));
        }
    }
}

bool GenericTreeMaker::isUnique(edgeList edges, seed arr){
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

void GenericTreeMaker::measureLeafNodeClusters(vector<vector<unsigned int>> &adjList, unsigned node, int parent, unsigned level){

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
