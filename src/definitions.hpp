/* Type definitions to be used in the rest of the program
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <utility>
#include <vector>

//an edge. It contains the two nodes a given edge connects
typedef std::pair<unsigned, unsigned> edge;

//a list of edges
typedef std::vector<edge> edgeList;

//a seed is the list of all non-leaf edge counts for a given tree
typedef std::vector<unsigned> seed;

//a leaf node cluster is a group of leaf nodes that are connected to the same
// branch node. This pair contains how many nodes are between the leaf nodes and
// the 0th node, and the amount of nodes of the cluster
typedef std::pair<unsigned, unsigned> leafNodeCluster;

#endif