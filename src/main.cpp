#include <iostream>
#include "FinalTree.hpp"

#define N 10

int main() {
	FinalTree tree(N);
	tree.calculate();
	tree.printArrangements();

	return 0;
}
