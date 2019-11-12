///////////////////////////////////////////////////////////////////////////////////////////
//  This program will create a Tree with data in it.  The data will be between 0 and 99
//  inclusive all other data will be discarded or ignored.  The final data will be written
//  to file called tree.txt with the corresponding level that it is in the tree.
//
//  Christy Mims
// 
//  07/18/2019
///////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

struct Node
{
	int Data;
	int DepthCounter;
	Node *Left;
	Node *Right;
};

string getFileName(string);
void readFile(string);
struct Node *Insert(Node *&, int &, int);
int writeFile(Node *);
void inOrder(ofstream &, Node *);

int main()
{
	// variable to hold file name 
	string fileName;

	// call and catch fileName from function 
	fileName = getFileName(fileName);

	// call readFile function
	readFile(fileName);

	//system("PAUSE");
	return(0);
}

string getFileName(string fileName)
{
	// prompt user and read in file name 
	cout << "Please enter file name with the extension (.txt)." << endl;
	cin >> fileName;

	// returns the file name
	return(fileName);
}

void readFile(string fileName)
{
	// variable to catch data
	int Data = -1;

	// create stream reader
	ifstream readData;

	// point to the stream reader and open the file provided by the user
	readData.open(fileName);

	// check to see if file was found
	while (!readData)
	{
		cout << "File could not be opened for reading." << endl << endl;

		// calls the function getFileName
		fileName = getFileName(fileName);
		// try to open file 
		readData.open(fileName);
	}

	// initializes root and level
	struct Node *Root = NULL;
	int level = 0;

	// look for end of file to see if all data has been read in 
	while (readData)
	{
		

		// read in data from file
		readData >> Data;

		// check to see if end of file has been reached
		if (readData.eof()) break;

		// check for invalid data and clear if is invalid
		if (readData.fail() || Data < 0 || Data > 99)
		{


			readData.clear();
			readData.ignore();

			Data = -1;

			cout << endl;
		}

		// executes if data is in valid range
		if (Data >= 0 && Data <= 99)
		{
			// calls function to put data into tree
			Insert(Root, Data, level);
		}

	}

	// call function to write data to file in order with
	// corresponding level
	writeFile(Root);
}

struct Node *Insert(struct Node *&Root, int &Data, int level)
{
	// creates new node and sets pointers to NULL
	if (Root == NULL)
	{
		// check to see if memory was allocated for the new Node
		if ((Root = new(Node)) == NULL)
		{
			cout << "Out of Space!!" << endl;
		}

		Root->Data = Data;
		Root->Left = NULL;
		Root->Right = NULL;
		Root->DepthCounter = level;

		// Debugging purposes
		//cout << Data << "\t" << level << endl;
		
	}
	// evaluates data to determine which side of the tree the data will go
	else
	{
		// less than the parent goes left
		if (Data < Root->Data)
		{
			// debugging purposes
			//cout << Data << "\t" << level << endl;

			Insert(Root->Left, Data, level + 1);
		}

		// greater than the parent go right
		else if (Data > Root->Data)
		{
			// debugging purposes
			//cout << Data << "\t" << level << endl;
				
			Insert(Root->Right, Data, level + 1);
		}

		// if equal to parent node go right
		else if (Data == Root->Data)
		{
			// debugging purposes
			//cout << Data << "\t" << level << endl;
			
			Insert(Root->Left, Data, level + 1);
		}

	}

	return Root;
}

int writeFile(Node *Root)
{
	// create out stream writer
	ofstream writeData;

	// tell out stream writer to create or open file tree.txt
	writeData.open("tree.txt");

	// check to see if file was created or opened
	if (!writeData)
	{
		cout << "Could not create or open file for writing." << endl << endl;
		return(1);
	}

	// output column headers for console and file
	cout << "Data:" << "\t" << "Level:" << endl;
	writeData << "Data:" << "\t" << "Level:" << endl;


	// call functionto print data in order with corresponding levels
	inOrder(writeData, Root);


	// close the file
	writeData.close();

}

// prints the tree in order from lowest to highest
void inOrder(ofstream &writeData, Node *Root)
{
	if (Root)
	{
		inOrder(writeData, Root->Left);
		// output the data and level
		cout << Root->Data << "\t" << Root->DepthCounter << endl;
		writeData << Root->Data << "\t" << Root->DepthCounter << endl;
		inOrder(writeData, Root->Right);

	}
}
