
/**
 * This program is a typing speed calculator. It allows the user to provide their own text file to
 * use for the text, or they can select one of the given choices. It prints the entire text
 * to the screen, and allows the user to type it in line-by-line. The program keeps track of
 * how long it takes them to finish and calculates their typing speed in words-per-minute (wpm)
 * 
 * @author Jordan Moss
 * @version September 18 2020
 */

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
using namespace std;
string get_text();
bool file_exists(const string fileName);
int main(int argc, char *argv[]){
	// if there is a command-line argument passed, it is taken to be the name of a file.
	// if the file does not exist in the current working directory, the user is asked to
	// choose from one of the four existing text files.
	string filename = "";
    if(argc > 1){
		filename = argv[1];
		if(!file_exists(filename)){
			filename = get_text();
		}
    }else{
		filename = get_text();
    }

    cout << "\nType the words that appear on the screen.\n\n";
    string typed;
    string total_typed = "";
    string total_text = "";


    fstream file;
    try{
		file.open(filename, ios::in);
    }catch(string* excep){
		cout << excep;
		return 0;
    }

	// print the text to the screen so that the user can see it all at once
	int lines = 1;
	if(file.is_open()){
		string line;
		while(getline(file, line)){
			cout << line << endl;
			total_text += line;
			lines++;
		}
		file.close();
	}

	cout << "\n\n";

	// take in the lines that the user types
	time_t start = time(NULL);
	for(int i = 0; i < lines; i++){
		getline(cin, typed);
		total_typed += typed;
	}
	time_t end = time(NULL);

    //determine typing speed (wpm)
    double seconds = (double)(end - start);
	cout << "Typing Speed: " << (total_typed.size()/5)/(seconds/60) << " wpm" << endl;

    //determine accuracy
	//this if-else statement is to account for the lengths of the text and what the
	//user typed being different, to prevent going out of bounds of the array
	int size;
	if(total_text.size() < total_typed.size()){
		size = total_text.size();
	}else{
		size = total_typed.size();
	}

	int errors = 0;
	for(int i = 0; i < size; i++){
		//if the character at any particular position in the text is not
		//the same as what was typed, it is counted as an error.
		if(total_text[i] != total_typed[i]){
			errors++;
		}
	}
	// if the lengths of the strings are different, each extra character is counted as an error
	errors += abs((int)(total_typed.size() - total_text.size()));
	
	float accuracy = (float)((total_text.size() - errors)) / total_text.size() * 100;
	cout << "Accuracy: " << accuracy << "%" << endl;

	return 0;
}

// A function to get input from the user
string get_text(){
    cout << "Choose a text to use during the typing speed test:\n" <<
	"\t1. Alice's Adventures In Wonderland by Lewis Carroll\n" <<
	"\t2. Romeo and Juliet by William Shakespeare\n" << 
	"\t3. The Great Gatsby by F. Scott Fitzgerald\n" <<
	"\t4. The Raven by Edgar Allen Poe\n" << endl;
    int choice = 0;
    do{
		cin >> choice;
    }while(choice < 1 || choice > 4);

    string filename = "";
    switch(choice){
	case 1:
		filename = "alice-in-wonderland.txt";
	    break;
	case 2:
	    filename = "romeo-and-juliet.txt";
	    break;
	case 3:
	    filename = "the-great-gatsby.txt";
	    break;
	case 4:
	    filename = "the-raven.txt";
    }
    return filename;
}

// a function to check if a file exists in the CWD
bool file_exists(const string fileName){
    ifstream infile(fileName);
    return infile.good();
}
