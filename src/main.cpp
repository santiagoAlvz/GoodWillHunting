#include <iostream>
#include "FinalTreeMaker.hpp"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    if(argc < 2){
        cout<<"N value wasn't provided"<<endl;
        return 1;
    }

    unsigned n = atoi(argv[1]);

    ArrangementsTable arrangements(n);
	FinalTreeMaker tree(&arrangements);
	tree.createArrangements(n);
	arrangements.printStats();
	arrangements.printToFile("output",n);

	return 0;
}
