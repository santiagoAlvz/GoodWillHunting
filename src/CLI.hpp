#ifndef CLI_H
#define CLI_H

#define VALUE_REQUIRED_STRING 1
#define NO_VALUE_BOOL 0

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
	{'h',"help",NO_VALUE_BOOL, &runtimeArgs.help, "displays program help",""}
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
	string element;
	bool found;
	bool isNPresent = false;

	for(int i = 1; i < argc; i++){
		element = argv[i];


		if(element[0] == '-'){
			found = false;
			for(unsigned long j = 0; !found && j < sizeof(options) / sizeof(option); j++){
				if((element.size() > 1 && element[1] == options[j].c) ||
				(element.substr(2, element.size() - 2) == options[j].name)){
					switch(options[j].type){
						case VALUE_REQUIRED_STRING:
							i++;
							if(i == argc || argv[i][0] == '-') throw ("Missing value for argument "+element);

							*(string*)(options[j].argument) = argv[i];
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
				runtimeArgs.n = stoi(element);
				isNPresent = true;
			} else throw ("Unexpected value '" + element + "'");
		}
	}

	if (!isNPresent && !runtimeArgs.help) throw (string("Missing N value"));
}

#endif