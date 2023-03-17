#include <iostream>
#include "FinalTreeMaker.hpp"
#include "CLI.hpp"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    try {
        readArguments(argc, argv);
    } catch (string message){
        cout<<message<<endl;
        return 1;
    }

    ArrangementsTable arrangements(runtimeArgs.n);
	FinalTreeMaker tree(&arrangements);
	tree.createArrangements(runtimeArgs.n);

	if(runtimeArgs.verbose) cout<<arrangements<<endl;

	arrangements.printStats();
	arrangements.printToFile(runtimeArgs.output, runtimeArgs.n);

	return 0;
}
