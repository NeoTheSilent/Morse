#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Letters {
private:
	char character;
	string morse;
	int size;
public:
	char getCharacter() {
		return character;
	}

	string getMorse() {
		return morse;
	}

	int getSize() {
		return size;
	}

	void setCharacter(char character2) {
		character = character2;
	}

	void setMorse(string morse2) {
		morse = morse2;
	}

	void setSize(int size2) {
		size = size2;
	}
};