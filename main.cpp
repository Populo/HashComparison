/* main.cpp

File that is run when the program is run and sets file names for the run method

by: Chris Staudigel
*/

#include <iostream>
#include <string>

#include "hashing.h"

using namespace std;

int main(int argc, char *argv[]) {
	// checks arguments and reads them in
	if (argc > 2) {
		string file1 = argv[1];
		string file2 = argv[2];

		Hashing *h = new Hashing(file1, file2);
		h->run();
	} else {
		// user cant do anything right
		cout << "please include filenames as arguments." << endl;
		cout << "./name <file1Name> <file2Name>"
	}
}
