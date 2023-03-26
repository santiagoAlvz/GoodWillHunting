/* Contains the definitions and functions for the Command Line Interface
 */

#ifndef CLI_H
#define CLI_H

#define VALUE_REQUIRED_STRING 0
#define NO_VALUE_BOOL 1

#include <queue>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

// Contains the flags that the program accepts as runtime options and their value
struct arguments{
	int n;
	string output = "output";
	bool verbose = false;
	bool help = false;
};

// Instance of arguments to be used in the program
arguments runtimeArgs;

//Structure of any runtime option available
struct option{
	char c; //short name
	string name; //long name
	int type; //how does this option affect runtime flags
	void* argument; //what runtime is expected to modify
	string help; //Text to be displayed in the help text about the option
	string fieldName; //Name of the field expected. Displayed in the help text
};

//Options that the program accepts, declared as option (previously declared struct)
static struct option const options[] = {
	{'o',"output",VALUE_REQUIRED_STRING, &runtimeArgs.output,"provide a custom filename for the output, if unspecified, 'output' will be used", " FILENAME"},
	{'v',"verbose",NO_VALUE_BOOL, &runtimeArgs.verbose, "display the complete arrangements table",""},
	{'h',"help",NO_VALUE_BOOL, &runtimeArgs.help, "display program help",""}
};

//prints the help on screen, using the declared options
void printHelp(){
	cout<<"usage: goodwillhunting [options] N"<<endl;
	cout<<"options:"<<endl;

	//print all options, with their help
	for(unsigned long j = 0; j < sizeof(options) / sizeof(option); j++){
		cout<<"  -"<<options[j].c<<options[j].fieldName<<", --"<<options[j].name<<options[j].fieldName<<endl;
		cout<<"      "<<options[j].help<<endl;
	}
}

//processes the runtime arguments supplied by the program on execution
void readArguments(int argc, char* argv[]){
	std::queue<string> clarguments; //queue to store arguments
	string element;
	bool found; //if the current option has been found
	bool isNPresent = false; //if the n value (a lonely number) has been found

	//Enters all arguments into a queue. It splits grouped short options
	for(int i = 1; i < argc; i++){
		if(argv[i][0] == '-' && argv[i][1] != '-'){
			element = argv[i];
			for(unsigned long j = 1; j < element.size(); j++){
				clarguments.push(string() + '-' + element[j]);
			}
		} else clarguments.push(string(argv[i]));
	}

	//For every element in the queue of arguments
	while (!clarguments.empty()){

		//get front argument
		element = clarguments.front();
		clarguments.pop();

		//if its an option
		if(element[0] == '-'){
			found = false;

			//traverse all known options to find a match
			for(unsigned long j = 0; !found && j < sizeof(options) / sizeof(option); j++){

				//If a match is found
				if((element.size() > 1 && element[1] == options[j].c) ||
				(element.substr(2, element.size() - 2) == options[j].name)){

					//According to the match type
					switch(options[j].type){
						case VALUE_REQUIRED_STRING: //the option requires a string as data

							//If there aren't more arguments or if next argument is an option
							if(clarguments.empty() || clarguments.front()[0] == '-') throw ("Missing value for argument "+element);

							*(string*)(options[j].argument) = clarguments.front();
							clarguments.pop();
							break;

						case NO_VALUE_BOOL: //the option sets a boolean on
							*(bool*)(options[j].argument) = true;
							break;
					}
					found = true; //mark option as found
				}
			}

			//If no match was found, display an error message
			if(!found){
				throw ("Unknown option "+element);
			}

		} else {
			//if it's not an option, try to process it as n

			//if element is a number and n hasn't been specified, use it as n, otherwise,
			//display an error message
			if(!isNPresent && std::all_of(element.begin(), element.end(), ::isdigit)){
				runtimeArgs.n = std::stoi(element);
				isNPresent = true;
			} else throw ("Unexpected value '" + element + "'");
		}
	}

	//If n wasn't specified, display an error message
	if (!isNPresent && !runtimeArgs.help) throw (string("Missing N value"));
}

#endif