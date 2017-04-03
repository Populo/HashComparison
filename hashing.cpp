/* hashing.cpp

main file of program.  Contains run method that calls hashing method and
comparing method

by: Chris Staudigel
*/

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sys/stat.h>

#include "hashtab.h"
#include "hashing.h"

using namespace std;

// sets filenames
Hashing::Hashing(string f1, string f2) {
	file1Name = f1;
	file2Name = f2;
}

// main method of program
void Hashing::run() {

	ifstream in1;
	ifstream in2;

	/*
taken from http://stackoverflow.com/a/6296808 to tell if file exists
using for speed optimization (which is important considering comparing is currently
n^2) rather than opening, checking, then closing
if I don't do this and the user inputs a name for a file that doesnt exist
you will end up with a massive file of text, I made the mistake and got a 40gb file.
oops.
	*/
	struct stat buf;
	if (stat(file1Name.c_str(), &buf) != -1 &&
			stat(file2Name.c_str(), &buf) != -1) {
		in1.open(file1Name.c_str());
		in2.open(file2Name.c_str());
	} else {
		cout << "One or more of the provided file names do not exist, that was almost very bad. " << endl;
		return;
	}

	// passes files individually
	hashFile(in1, file1Name, 1);
	hashFile(in2, file2Name, 2);

	// compares files by comparing the maps
	compareFiles(hash1, hash2);
}


// hashes file and puts it into corresponding map
void Hashing::hashFile(ifstream& file, string name, int fileNum) {

	// output file
	ofstream out;
	string outName = name + ".hash";
	out.open(outName.c_str());

	// tracks current line and strings
	int currentLine = 1;
	string line1;
	string line2;
	string line3;

	// temporary map of hashes
	map<int, hashval_t> hashing;

	// grabs first two lines
	getline(file, line1);
	getline(file, line2);

	// hashes 3 lines, grabs the next line and increments currentLine
	// adds hash and line number to map
	while(!file.eof()) {
		getline(file, line3);
		hashval_t h = hash(line1+line2+line3);
		hashing[currentLine] = h;
		out << currentLine << ": " << h << endl;
		line1=line2;
		line2=line3;
		currentLine++;
	}

	// determines which map the file belongs to.
	// had to use int because using filename doesnt work in the case of
	// the same files being used
	if(fileNum == 1) hash1 = hashing;
	else if (fileNum == 2) hash2 = hashing;

	// prints output
	cout << "output file is called: " << outName << endl;

	// closes files
	file.close();
	out.close();
}


// given string, hash the string
hashval_t Hashing::hash(string s) {
	hashval_t h;
	for (int i = 0; i < s.size(); i++) {
		// ignore spaces
		if (s[i] != ' ') h = h ^ magicbits[s[i]][i%512];
	}
	return h;
}

// compares the files and outputs matching lines
void Hashing::compareFiles(map < int, hashval_t >& h1, map < int, hashval_t >& h2) {
	if (h1.size() != 0 && h2.size() != 0) {
		// if the maps are the same, the files are the same
		if (h1 == h2) {
			cout << "The files are the same." << endl;
			return;
		}
		// if the maps arent the same, loop through and find similarities
		// does not account for sequential lines
		for (int i = 1; i <= h1.size(); i++) {
			for (int j = 1; j <= h2.size(); j++) {
				if(h1[i] == h2[j]) {
					cout << "line " << i << " and line " << j << endl;
				}
			}
		}
	}
}
