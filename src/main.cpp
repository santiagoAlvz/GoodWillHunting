#include <iostream>
#include "FinalTreeMaker.hpp"

using std::cout;
using std::endl;

struct PARAMETERS{
    int n;
    bool verbose = false;
    string output = "output";
};

void readArguments(int argc, char* argv[], PARAMETERS &rP){
    bool specifiedN = false;

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            switch(argv[i][1]){
                case 'o':
                    i++;
                    rP.output = argv[i];
                    break;
                case 'v':
                    rP.verbose = true;
                    break;
                case 'h':
                    throw("");
                default:
                    throw("Unknown argument -" + argv[i][1]);
            }
        } else {
            specifiedN = true;
            rP.n = atoi(argv[i]);
        }
    }

    if(!specifiedN) throw("Missing N value");
}

void printHelp(){
    cout<<"usage: goodwillhunting [options] N"<<endl;

    cout<<"options:"<<endl;
    cout<<"\t-o [filename]\tProvides a custom filename for the output, if not specified, 'output' is used"<<endl;
    cout<<"\t-v\t(from verbose) prints the arrangement matrix"<<endl;
}

int main(int argc, char* argv[]) {

    PARAMETERS runtimeParameters;

    try{
        readArguments(argc, argv, runtimeParameters);
    } catch(char const* message){
        cout<<message<<endl;
        printHelp();
        return 1;
    }

    ArrangementsTable arrangements(runtimeParameters.n);
	FinalTreeMaker tree(&arrangements);
	tree.createArrangements(runtimeParameters.n);

	if(runtimeParameters.verbose) cout<<arrangements<<endl;

	arrangements.printStats();
	arrangements.printToFile(runtimeParameters.output, runtimeParameters.n);

	return 0;
}
