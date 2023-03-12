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

        if(length == 1){
            while(temp.size() < n - 1){
                temp.push_back(make_pair(0, temp.size() + 1));
            }
            (*arrangements)[n].push_back(temp);
            continue;
        }

        for(unsigned long j = 0; j < (*arrangements)[length].size(); j++){
            usedBranches.clear();
            std::sort(decomposedEdgeCount[i].begin(),decomposedEdgeCount[i].end());

            do {

                usedEdges = vector<unsigned>(length, 0);
                valid = true;

                for(unsigned long k = 0; k < (*arrangements)[length][j].size(); k++){
                    usedEdges[(*arrangements)[length][j][k].first]++;
                    usedEdges[(*arrangements)[length][j][k].second]++;
                }

                for(unsigned long k = 0; k < length; k++){
                    if(usedEdges[k] > decomposedEdgeCount[i][k]) valid = false;
                }

                if(!valid) continue;

                temp = (*arrangements)[length][j];
                cont = 0;
                while(temp.size() < n - 1){

                    while(usedEdges[cont] == decomposedEdgeCount[i][cont]){
                        cont++;
                    }
                    temp.push_back(make_pair(cont, temp.size() + 1));
                    usedEdges[cont]++;
                }

                if(isUnique(temp)) (*arrangements)[n].push_back(temp);

            } while ( std::next_permutation(decomposedEdgeCount[i].begin(),decomposedEdgeCount[i].end()));
        }
    }
}

bool GenericTreeMaker::isUnique(vector<pair<unsigned,unsigned>> edges){
    vector<vector<unsigned>> adjList(edges.size() + 1);
    vector<unsigned> branches;

    for(unsigned long i = 0; i < edges.size(); i++){
        adjList[edges[i].first].push_back(edges[i].second);
        adjList[edges[i].second].push_back(edges[i].first);
    }

    branches = measureBranches(adjList,0,-1);
    std::sort(branches.begin(), branches.end());

    for(unsigned long i = 0; i < usedBranches.size(); i++){
        if(branches == usedBranches[i]){
            return false;
        }
    }

    usedBranches.push_back(branches);

    return true;
}

vector<unsigned> GenericTreeMaker::measureBranches(vector<vector<unsigned int>> &adjList, unsigned node, int parent){
    vector<unsigned> result;
    vector<unsigned> temp;

    if(adjList[node].size() == 1 && parent != -1){
        result = {1};
        return result;
    }

    if(adjList[node].size() == 2){
        if(parent != -1){
            if(adjList[node][0] == unsigned(parent)){
                result = measureBranches(adjList, adjList[node][1], node);
            } else {
                result = measureBranches(adjList, adjList[node][0], node);
            }

            result[0]++;
            return result;
        }

        result = measureBranches(adjList, adjList[node][1], node);
        temp = measureBranches(adjList, adjList[node][0], node);

        result[0] += temp[0] + 1;
        temp.erase(temp.begin());
        result.insert(result.end(), temp.begin(), temp.end());
        return result;

    }

    for(int neighbourNode: adjList[node]){
        if(neighbourNode != parent){
            temp = measureBranches(adjList, neighbourNode, node);
            temp[0]++;
            result.insert(result.end(), temp.begin(), temp.end());
        }
    }

    if(parent != -1) result.insert(result.begin(), 1);

    return result;
}
