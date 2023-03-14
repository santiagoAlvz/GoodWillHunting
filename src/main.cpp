#include <iostream>
#include "FinalTree.hpp"

using std::cout;
using std::endl;

#define N 10

int main() {
    ArrangementsTable arrangements(N);
	FinalTree tree(&arrangements);
	tree.createArrangements(N);
	arrangements.printStats();
	//cout<<arrangements<<endl;
	arrangements.printToFile("output",N);

	return 0;
}
