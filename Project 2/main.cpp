#include "Struct.h"
// Raymond Rennock | 11/25/2018 | Project 2B

//Declaration for Input
int input(int num, int lower, int upper);

int main() {
	//Input File
	ifstream morsecode ("morse.txt");
	
	//Temporary containers
	string line;
	string morseline = "";

	//What we will initially store our letters in before we put it in the BST
	Letters alphabet[26];
	
	//Our base root, as we need our root to be completely blank
	Letters base_root;
	base_root.setSize(0);
	base_root.setCharacter(' ');
	base_root.setMorse("");

	//Assuming we can open up our file
	if (morsecode.is_open()) {
		for (int i = 0; i < 26; i++) {
			//Get the line from the file
			getline(morsecode, line);
			
			//Set the letter that has the character
			alphabet[i].setCharacter(line[0]);
			
			//Set the size of the morse code line
			alphabet[i].setSize(line.size() - 1);

			//Get the contents, ignoring the first letter
			for (int j = 1; j < line.size(); j++) {
				morseline += line[j];
			}
			alphabet[i].setMorse(morseline);
			//Reseting the dummy line
			morseline = "";
		}
		//We close it when it's done
		morsecode.close();
	}

	//Otherwise if it breaks, we say it can't be opened
	else {
		cout << "Unable to Open File";
	}
	
	// We make our base root from what we know
	struct node *root = NULL;
	root = insert(root, base_root, 0);

	//And now, we put into the BST all the letters that are only one dot or one dash
	for (int i = 0; i < 26; i++) {
		if (alphabet[i].getSize() == 1) {
			insert(root, alphabet[i], 0);
		}
	}
	//Next, we put in all of our letters that are exactly 2 long, such as _. or ..
	for (int i = 0; i < 26; i++) {
		if (alphabet[i].getSize() == 2) {
			insert(root, alphabet[i], 0);
		}
	}
	//After that, we can put in all of our letters that are exactly 3 long, such as ___ or ._.
	for (int i = 0; i < 26; i++) {
		if (alphabet[i].getSize() == 3) {
			insert(root, alphabet[i], 0);
		}
	}
	//Finally, we put in all the rest of the letter
	for (int i = 0; i < 26; i++) {
		if (alphabet[i].getSize() == 4) {
			insert(root, alphabet[i], 0);
		}
	}
	//By doing it this way, it will automatically sort our tree correctly without a chance of losing a letter somewhere
	//If we put in all our letters at once, it would lose a few letters and get confused, so if we make sure
	//each level is completed before we move on to the next one, there aren't any problems

	//Our choice element
	int choice = 0;
	//While the user doesn't want to quit, we continue this loop forever, allowing them to test and look at what they want
	while (choice != 4) {
		cout << "Welcome to the Morse Code Translator. Please select what you want to do" << endl;
		cout << "\n1: View the In Order BST\n";
		cout << "2: Decipher a Text\n";
		cout << "3: Encrypt a Message\n";
		cout << "4: Quit\n\n";
		//If they make an invalid input, we ignore it and ask them to try again
		retry:
		// We now ask for their input, and we will only accept 1, 2, 3, 4
		choice = input(choice, 1, 4);

		//If they chose one, we'll clear the screen and show the tree inorder, while also giving each letters information
		if (choice == 1) {
			system("CLS");
			inorder(root);
			// After that,we'll pause to let them actually see it instead of letting it get wiped by the next CLS
			system("pause");
			system("CLS");
		}
		
		//If they want to decipher something, they select 2
		if (choice == 2) {
			// We create a temporary string
			string decipher = "";
			// We clear the screen from anything before
			system("CLS");
			// Then, we ask them what they want to do. 
			cout << "What would you like to decipher? (Please use . and _ only with a single space to seperate): ";
			// We take all the information given to us
			getline(cin,decipher);
			
			// Temporary string file
			string word;
			cout << endl << endl;

			//As long as there are characters in the decipher string, we'll continue working
			for (int i = 0; i < decipher.size(); i++) {
				// If we're looking at something that is . or _, we add it
				if ((decipher[i] == '/') or (decipher[i] == '_')) {
					word += decipher[i];
				}
				else if (decipher[i] == ' '){
					// Otherwise, if we find a space, that means that the "word" is complete and we try to
					// translate it. Afterwords, we reset the word
					morse_to_letter(root, word);
					word = "";
				}
				else {
					// If they enter in an invalid character, we ignore it
					cout << "\n\nYou entered in an invalid character, " << decipher[i] << ", it will be ignored\n";
				}
			}
			// Once everything is finished, it's likely that there will still be one last word to decipher
			// So we decipher it here.
			if (word != "") {
				morse_to_letter(root, word);
				word = "";
			}
			cout << endl << endl;
			// We give them a moment to look, and allow them to move on
			system("pause");
			system("CLS");
		}
		
		// If they want to encrypt something, they select 3
		if (choice == 3) {
			// We create a encryption string
			string encrypt = "";	
			// We clear the screen
			system("CLS");
			// We ask for them to encrypt something. Note, if you add a space, it will run it multiple times
			cout << "What would you like to encrypt? (Please use a-z in lower case only, no spaces)";
			cout << "NOTE: Invalid characters will not be encrypted. Only use a-z: ";
			// We take in user input to see what they want to encrypt.
			// NOTE: If you decide to have fun and put in something that isn't a-z, 
			// that character will be ignored during the encryption process
			cin >> encrypt;
			cout << endl << endl;

			// We will encrypt everything that is valid
			for (int i = 0; i < encrypt.size(); i++) {
				letter_to_morse(root, encrypt[i]);
				// And let out a space to seperate each morse letter, so you don't confuse . . as ..
				cout << " ";
			}

			cout << endl << endl << endl;
			system("pause");
			system("CLS");
		}
		

	}


	system("pause");
	return 0;
}

int input(int num, int lower, int upper) {
	while (true) { // We'll be running this loop until something is returned
		if (!(cin >> num)) { // If the input doesn't fail
			{ // If cin fails, that means they tried to do something like entering in
			// a string into an integer, so we clear the input and ask them to enter in a number
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Please enter a number from " << lower << " to " << upper << " that has no nonnumeric digits in it: ";
			}
		}

		else {
			if (num >= lower && num <= upper) { // We check the numbers to see if it's what we want
				// Assumption: If we get a valid input, we're going to ignore any further input from that line
				cin.clear();
				cin.ignore(100, '\n');
				return num; // If it is, we return it
			}
			else { // Otherwise, we declare to the user what acceptable numbers there are
				//And we'll ignore any further point in the line as it's already invalid
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Please enter a number from " << lower << " to " << upper << ": ";
			}
		}
	}
}