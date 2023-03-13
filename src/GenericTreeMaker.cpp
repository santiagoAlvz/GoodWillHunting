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

    vector<pair<unsigned,unsigned>> temp;
    vector<unsigned> usedEdges;
    unsigned length;
    bool valid = true;
    unsigned cont;

    for(unsigned long i = 0; i < decomposedEdgeCount.size(); i++){
        length = decomposedEdgeCount[i].size();
        temp.clear();

        if(length == 1){
            while(temp.size() < n - 1){
                temp.push_back(make_pair(0, temp.size() + 1));
            }
            (*arrangements)[n].push_back(make_pair(temp,decomposedEdgeCount[i]));
            continue;
        }

        if(length == 2){

            for(unsigned long j = 1; j < n; j++){
                if(j <=  decomposedEdgeCount[i][0]){
                    temp.push_back(make_pair(0,j));
                } else temp.push_back(make_pair(1,j));
            }

            (*arrangements)[n].push_back(make_pair(temp,decomposedEdgeCount[i]));
            continue;
        }

        if((*arrangements)[decomposedEdgeCount[i].size()].empty()){
            //Create the (*arrangements) for its size
            createMissingArrangements(decomposedEdgeCount[i].size());
        }

        for(unsigned long j = 0; j < (*arrangements)[length].size(); j++){
            usedLevelDistributions.clear();
            std::sort(decomposedEdgeCount[i].begin(),decomposedEdgeCount[i].end());

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
                    temp.push_back(make_pair(cont, temp.size() + 1));
                    usedEdges[cont]++;
                }

                if(isUnique(temp)) (*arrangements)[n].push_back(make_pair(temp,decomposedEdgeCount[i]));

            } while ( std::next_permutation(decomposedEdgeCount[i].begin(),decomposedEdgeCount[i].end()));
        }
    }
}

bool GenericTreeMaker::isUnique(vector<pair<unsigned,unsigned>> edges){
    vector<vector<unsigned>> adjList(edges.size() + 1);
    levelDistribution.resize(edges.size() + 1);
    std::fill(levelDistribution.begin(), levelDistribution.end(), 0);

    for(unsigned long i = 0; i < edges.size(); i++){
        adjList[edges[i].first].push_back(edges[i].second);
        adjList[edges[i].second].push_back(edges[i].first);
    }

    measureLevelDistribution(adjList,0,0);

    for(unsigned long i = 0; i < usedLevelDistributions.size(); i++){
        if(levelDistribution == usedLevelDistributions[i]){
            return false;
        }
    }

    usedLevelDistributions.push_back(levelDistribution);

    return true;
}

void GenericTreeMaker::measureLevelDistribution(vector<vector<unsigned int>> &adjList, unsigned node, unsigned level){
    levelDistribution[level]++;

    for(unsigned neighbour: adjList[node]){
        if(neighbour > node) measureLevelDistribution(adjList, neighbour, level + 1);
    }
}
