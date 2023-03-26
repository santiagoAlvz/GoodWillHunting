#include "TreeMaker.hpp"
#include "CLI.hpp"

int main(int argc, char* argv[]) {

    //process the command line arguments
    try {
        readArguments(argc, argv);
    } catch (string message){

        //if there was a mistake, inform the user and exit
        cout<<message<<endl<<endl;
        printHelp();
        return 1;
    }

    //if help was specified
    if(runtimeArgs.help){
        printHelp();
        return 0;
    }

    //execute the tree construction process
    ArrangementsTable arrangements(runtimeArgs.n);
	TreeMaker tree(&arrangements, runtimeArgs.n, true);

    //if specified, print the arrangements table
	if(runtimeArgs.verbose) cout<<arrangements<<endl;

    //output
	arrangements.printStats();
	arrangements.printToFile(runtimeArgs.output, runtimeArgs.n, runtimeArgs.darkmode);

	return 0;
}
