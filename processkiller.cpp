#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/**
* Simplified process killer by vorixo
* A simple console app that lets you search for 
* a process and kill it by looking at its id
**/

/**
* Main menu UI
* @Param currentMenu
**/
void showMenu(const int& currentMenu) {
	system("clear");
	switch(currentMenu){
		case 0:
			cout << "1.- Search process" << endl;
			cout << "2.- Exit" << endl;
			cout << "Option: ";
		break;
		case 1:
			cout << "Look for (can use substrings): ";
		break;
	}
}

/**
* Prints the process list matching with the string query 
* @Param op: input string query
**/
bool indexFiles(const string& op){
	system("ps -ef | sort > .proclist_processkiller");
	ifstream infile(".proclist_processkiller");
	string line;
	bool oneAtLeast = false;
	while(getline(infile, line)){
		if(line.find(op) != -1){
			cout << line << endl;
			oneAtLeast = true;
		}
	}
	return oneAtLeast;
}

/**
* Processes the input depending in the menu we are on
* Observation: Simplified function based on functionality, not design
* @Param currentMenu
**/
void inputMutator(int& currentMenu){
	string op;
	if(currentMenu == 0) {
		getline(cin, op);
		if(op == "1"){
                        currentMenu = 1;
                }
                else if(op == "2"){
                        // Safe, erase the file generated for the indexing
			system("rm -f .proclist_processkiller");
			system("clear");
			exit(0);
                }
	} else if (currentMenu == 1) {
		getline(cin, op);
		if(indexFiles(op)){
			cout << "\n---------------------------------" << endl;
			cout << "Process id to kill (quit to exit): ";
			string pid = "";
			getline(cin, pid);
			if(pid == "quit"){
				currentMenu = 0;
			}
			else{
				system("clear");
				system(("sudo kill " + pid).c_str());
				cout << "Press ENTER to continue" << endl;
				getchar();
			}
		} else {
			cout << "\n---------------------------------" << endl;			
			cout << "\033[1;31mNo results were found under: \033[0m" << op << endl;
			cout << "Press ENTER to continue or write quit: ";
			string finalop;
			getline(cin, finalop);
			if(finalop == "quit"){
				currentMenu = 0;
			}
		}
	}
}

int main(){
	int currentMenu = 0;
	while(true){
		showMenu(currentMenu);
		inputMutator(currentMenu);
	}
}
