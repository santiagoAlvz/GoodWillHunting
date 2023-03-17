#ifndef CLI_H
#define CLI_H

#define VALUE_REQUIRED_STRING 0
#define NO_VALUE_BOOL 1

#include <queue>

struct arguments{
	int n;
	string output = "output";
	bool verbose = false;
	bool help = false;
};

arguments runtimeArgs;

struct option{
	char c;
	string name;
	int type;
	void* argument;
	string help;
	string fieldName;
};

static struct option const options[] = {
	{'o',"output",VALUE_REQUIRED_STRING, &runtimeArgs.output,"provide a custom filename for the output, if unspecified, 'output' will be used", " FILENAME"},
	{'v',"verbose",NO_VALUE_BOOL, &runtimeArgs.verbose, "display the complete arrangements table",""},
	{'h',"help",NO_VALUE_BOOL, &runtimeArgs.help, "display program help",""}
};

void printHelp(){
	cout<<"usage: goodwillhunting [options] N"<<endl;
	cout<<"options:"<<endl;
	for(unsigned long j = 0; j < sizeof(options) / sizeof(option); j++){
		cout<<"  -"<<options[j].c<<options[j].fieldName<<", --"<<options[j].name<<options[j].fieldName<<endl;
		cout<<"      "<<options[j].help<<endl;
	}
}

void readArguments(int argc, char* argv[]){
	std::queue<string> clarguments;
	string element;
	bool found;
	bool isNPresent = false;

	for(int i = 1; i < argc; i++){
		if(argv[i][0] == '-' && argv[i][1] != '-'){
			element = argv[i];
			for(unsigned long j = 1; j < element.size(); j++){
				clarguments.push(string() + '-' + element[j]);
			}
		} else clarguments.push(string(argv[i]));
	}

	while (!clarguments.empty()){
		element = clarguments.front();
		clarguments.pop();

		if(element[0] == '-'){
			found = false;
			for(unsigned long j = 0; !found && j < sizeof(options) / sizeof(option); j++){
				if((element.size() > 1 && element[1] == options[j].c) ||
				(element.substr(2, element.size() - 2) == options[j].name)){
					switch(options[j].type){
						case VALUE_REQUIRED_STRING:

							//If there aren't more arguments or if next argument is an option
							if(clarguments.empty() || clarguments.front()[0] == '-') throw ("Missing value for argument "+element);

							*(string*)(options[j].argument) = clarguments.front();
							clarguments.pop();
							break;
						case NO_VALUE_BOOL:
							*(bool*)(options[j].argument) = true;
							break;
					}
					found = true;
				}
			}

			if(!found){
				throw ("Unknown option "+element);
			}

		} else {
			if(std::all_of(element.begin(), element.end(), ::isdigit)){
				runtimeArgs.n = std::stoi(element);
				isNPresent = true;
			} else throw ("Unexpected value '" + element + "'");
		}
	}

	if (!isNPresent && !runtimeArgs.help) throw (string("Missing N value"));
}

#endif