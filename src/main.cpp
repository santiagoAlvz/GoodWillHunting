#include <iostream>
#include "FinalTree.hpp"

#define N 10

int main() {
    ArrangementsTable arrangements(N);
	FinalTree tree(&arrangements);
	tree.createArrangements(N);
	//tree.printArrangements();
	arrangements.print();

	return 0;
}
