#include <iostream>
#include "FinalTreeMaker.hpp"

using std::cout;
using std::endl;

#define N 10

int main() {
    ArrangementsTable arrangements(N);
	FinalTreeMaker tree(&arrangements);
	tree.createArrangements(N);
	arrangements.printStats();
	arrangements.printToFile("output",N);

	return 0;
}
