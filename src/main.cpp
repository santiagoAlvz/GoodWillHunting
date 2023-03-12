#include <iostream>
#include "FinalTree.hpp"

#define N 10

int main() {
    ArrangementsTable arrangements(N);
	FinalTree tree(N, &arrangements);
	tree.calculate();
	//tree.printArrangements();
	arrangements.print();

	return 0;
}
