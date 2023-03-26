#include "TreeMaker.hpp"
#include "CLI.hpp"

int main(int argc, char* argv[]) {

    try {
        readArguments(argc, argv);
    } catch (string message){
        cout<<message<<endl<<endl;
        printHelp();
        return 1;
    }

    if(runtimeArgs.help){
        printHelp();
        return 0;
    }

    ArrangementsTable arrangements(runtimeArgs.n);
	TreeMaker tree(&arrangements, runtimeArgs.n, true);

	if(runtimeArgs.verbose) cout<<arrangements<<endl;

	arrangements.printStats();
	arrangements.printToFile(runtimeArgs.output, runtimeArgs.n);

	return 0;
}
