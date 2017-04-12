#define TARGETFILES "targets.txt"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

class Receipt {
	public :
		Receipt () {
			awardOrReceipt = -1;
			match = -1;
			prize = -1;
			receiptNumber = "";
		}

		Receipt (string first, int type) {
			awardOrReceipt = type;
			match = -1;
			prize = -1;
			receiptNumber = first;
		}

		~Receipt () {

		}

		void show () {
			cout << receiptNumber << endl;
		}

		string returnReceiptNumber () {
			return receiptNumber;
		}

		void winning (int match, int prize) {
			this->match = match;
			this->prize = prize;
		}

	private :
		int awardOrReceipt;	/** 
								* 0 for award numbers
								* q for my receipts
							*/
		int match;	// index of the matching serial number in the table
		int prize;	/**
						* the award you won
						* initialized as -1
					*/
		string receiptNumber;
};

void plot ();


fstream *targets;
string table[2][5];
vector < vector <Receipt>> receiptTable;	/**
												* first row be the awards
												* others be my receipt
											*/

int main ()
{
	vector <Receipt> attributes;
	Receipt* tmpt = new Receipt ("", 0);
	attributes.push_back (*tmpt);
	tmpt = new Receipt ("Extraordinary Award", 0);
	attributes.push_back (*tmpt);
	tmpt = new Receipt ("Special Award", 0);
	attributes.push_back (*tmpt);
	tmpt = new Receipt ("Top Award", 0);
	attributes.push_back (*tmpt);
	tmpt = new Receipt ("Top Award", 0);
	attributes.push_back (*tmpt);
	tmpt = new Receipt ("Top Award", 0);
	attributes.push_back (*tmpt);
	receiptTable.push_back (attributes);

	//for (int i=0; i<Awards.size(); i++)
	//	Awards[i].show();

	table[0][0] = "Extraordinary Award";
	table[0][1] = "Special Award";
	table[0][2] = "Top Award";
	table[0][3] = "Top Award";
	table[0][4] = "Top Award";

	for (int j=0; j<5; j++)
		table[1][j] = "/0";

	string inputString;
	targets = new fstream ();
	targets->open (TARGETFILES, ios::in);

	vector <Receipt> Awards;
	Awards.push_back (Receipt ("", 0));
	while (getline (*targets, inputString)) 
		Awards.push_back (Receipt (inputString, 0));
		
	receiptTable.push_back (Awards);
	for (int i=0; i<receiptTable.size(); i++) {
		for (int j=0; j<receiptTable[i].size(); j++)
			receiptTable[i][j].show();
	}

	cout << "Please enter your receipt number : ";
	
	while (cin >> inputString) {
		if (inputString == "exit") 
			break;
		
		Receipt *current = new Receipt (inputString, 1);

		//check extraordinary award
		if (inputString == receiptTable[1][1].returnReceiptNumber()) {
			current->winning (1, 1);
			cout << "You just won the extraordinary award : " << inputString << endl;
			continue;
		}
		//check special award
		if (inputString == receiptTable[1][2].returnReceiptNumber()) {
			current->winning (1, 1);
			cout << "You just won the special award : " << inputString << endl;
			continue;
		}
		//check three top awards
		for (int i=0; i<3; i++) {
			if (inputString == receiptTable[1][3+i].returnReceiptNumber()) {
				current->winning (3+1, 3+1);
				cout << "You just won the top award : " << inputString << endl;
			}
			continue;
		}

		/*

UNSOLVED


		*/
		//check other awards
		for (int num=3; num<3; num++) {
			for (int award=1; award<8; award++) {
				bool won = true;
				for (int i=award; i<8; i++) {
					string tmpt = receiptTable[1][num].returnReceiptNumber();
					cout << tmpt << endl;
					if (inputString[i] != tmpt[i]) {
						won = false;
						break;
					}
				}
				if (won) {
					current->winning (num, award+1);
					cout << "You just won the #" << award+1 << " award : " << inputString << endl;
					continue;
					break;
				}
			}
		}

	}
	cout << "You won nothing TAT" << endl;

	return 0;
}

void plot () 
{	
	for (int r=0; r<2; r++) {
		for (int i=0; i<5; i++) {
			cout << ' ';
			for  (int j=0; j<20; j++) {
				cout << '-';
			}
		}
		cout << endl;
		for (int i=0; i<5; i++) {
			cout << '|';
			int length = table[r][i].size();

			for  (int j=0; j<(20-length); j++) {
				cout << ' ';
			}
			cout << table[r][i];
		}
		cout << '|';
		cout << endl;
	}	
	for (int i=0; i<5; i++) {
		cout << ' ';
		for  (int j=0; j<20; j++) {
			cout << '-';
		}
	}
	cout << endl;
}