/* hashing.h

hashing declarations

by: Chris Staudigel
*/

#ifndef HASHING_H
#define HASHING_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "hashtab.h"

using namespace std;

class Hashing {
	private:
		// filenames
		string file1Name;
		string file2Name;
		// maps for each file
		map < int, hashval_t > hash1;
		map < int, hashval_t > hash2;
	public:
		Hashing(string f1, string f2);
		void run();
		void hashFile(ifstream& f, string name, int fileNum);
		hashval_t hash(string s);
		void compareFiles(map < int, hashval_t >& h1, map < int, hashval_t >& h2);

};

#endif
