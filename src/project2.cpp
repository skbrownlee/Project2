#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
	for (int i=0; i < n; i++) {
		A[i] = '\0';
	}
}


// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
	for (int i=0; i < n; i++) {
		B[i] = A[i];
	}
	B[n] = '\0';
}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

class myString;

class myString {
	friend ostream& operator << (ostream& s, myString& A);
protected:
	char* strArray;
	int size;
	void strCpy (char* A, char* B, int n);
public:
	myString ();
	myString(char* inpStr);
	myString (myString& B);
	int Size();
	char* getWord();
    bool operator == (myString& B);
    bool operator > (myString& B);
    bool operator < (myString& B);
    myString& operator = (myString& B);
    myString& operator = (char* B);
    ~myString ();
};


// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}
// deconstructor - deletes the strArray and size is set to zero
myString::~myString (){
	delete [] strArray;
	size = 0;
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0') {
		i++;}
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1);
	for (int j=0; j < size; j++)
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy (B.strArray, size, strArray);
}

char* myString::getWord()
{
	return strArray;
}

// getter for size of myString
int myString::Size () {
	return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {
	// clear the array
	if(strArray != NULL) {
			delete [] strArray;
		}
		strArray = new char[stringLength(B)];
		// set variables equal to the other
		size = stringLength(B);
		stringCopy(B, size, strArray);

		return *this;
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
	//clear the array
	if(strArray != NULL) {
		delete [] strArray;
	}
	strArray = new char[stringLength(B.strArray)];
	// set variables equal to the new ones
	size = stringLength(B.strArray);
	stringCopy(B.strArray, size, strArray);

	return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {
	// TODO
	// if the lengths aren't the same the words aren't the same
		if (stringLength(this->getWord()) != stringLength(B.getWord())) {
			return false;
		}
		// check letter by letter, if not the same return false otherwise true
		for (int i=0; i < stringLength(this->getWord()); i++) {
			if (int(this->strArray[i]) != int(B.strArray[i])) {
				return false;
			}
		}
		return true;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {
// want to find smaller so we can loop through it and not get out of bounds
	int sizeOfA = size;
	int sizeOfB = B.size;
	int smallerSize;
	if(sizeOfA < sizeOfB) {
		smallerSize = sizeOfA;
	}
	else {
		smallerSize = sizeOfB;
	}
// loop through the smaller array if char is less return true, otherwise false
	for(int i=0; i < smallerSize; i++) {
		char first = strArray[i];
		char second = B.strArray[i];
		if (int(first) > int(second)) {
			return false;
		}
		else if (int(first) < int(second)) {
			return true;
		}
	}
	if (sizeOfA != sizeOfB) {
		if(sizeOfA < sizeOfB) {
			return true;
		}
		return false;
	}
	return false;
}


// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {
	// same as < but opposite
	int sizeOfA = size;
	int sizeOfB = B.size;
	int smallerSize;
	if(sizeOfA < sizeOfB) {
		smallerSize = sizeOfA;
	}
	else {
		smallerSize = sizeOfB;
	}

	for(int i=0; i < smallerSize; i++) {
		char first = strArray[i];
		char second = B.strArray[i];
		if (int(first) > int(second)) {
			return true;
		}
		else if (int(first) < int(second)) {
			return false;
		}
	}
	if (sizeOfA != sizeOfB) {
		if(sizeOfA < sizeOfB) {
			return false;
		}
		return true;
	}
	return false;
}

// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
	char* str = new char[20]; //assumes a max token size of 20
	emptyString (str, 20);

	char c;
	int i = 0;
	while (!cin.eof()) {
		cin.get(c);
		if (!cin.eof ()) {
			if ((c != '\n') && (c != ' ')) {
				if ( ((c >= 'a') && (c <= 'z')) ||
					 ((c >= 'A') && (c <= 'Z')) ||
					 ((c >= '0') && (c <= '9')) )
					str[i++] = c;
			}
			else if ((c == '\n') && (i > 0))
				return str;
			else if ((c == ' ') && (i > 0))
				return str;
		}
	}
	if (i > 0) return str;
	else return NULL;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bagOfWords;
class bagOfWords {
private:
	int binarySearch (myString& W);
	bool binarySearch(myString* stopWords, myString& wordToFind, int numStopWords); // ended up not using
protected:
	myString* _words;
	int* _frequencies;
	int _size;

public:
	bagOfWords ();
	bagOfWords (int numOfWords);

	myString* get_Words();
	int* get_Freq();
	int get_size();

	void addAtIndex(int index, myString& newWord);

	void setSize(int i);
	void swapElements(int i,int j);

	void addWord (myString& W);//insert word w into the array _words - keep it sorted alphabetically
	void sortFreq(); //sort words array based on frequency
	void sortWords(); //sort words array alphabetically
	void display(); //print word followed by a colon followed by a single space and frequencuy
	bagOfWords& operator = (bagOfWords& B);
	bagOfWords* removeStopWords(myString* stopWords, int numStopWords); //stopWords from _words array
	~bagOfWords();
};

// default constructor - initializes with no words
bagOfWords::bagOfWords()
{
	_size = 0;
	_words = new myString[0];
	_frequencies = new int[0];
}

// non default constructor - initializes with a known number of words
bagOfWords::bagOfWords (int numOfWords)
{
	_size = numOfWords;
	_words = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}
// overloaded = operator for a bagOfwords, isn't used in main but could be useful
bagOfWords& bagOfWords::operator = (bagOfWords& B) {
		int size = B._size;
		for (int i=0; i<size; i++) {
			this->_words[i] = B._words[i];
			this->_frequencies[i] = B._frequencies[i];
		}
		this->_size = size;
		return *this;
}

// destructor for bag of words, deletes the arrays and sets variables to null
bagOfWords::~bagOfWords() {
	delete [] this->_words;
	delete [] this->_frequencies;
	_words = NULL;
	_frequencies = NULL;
	this->_size = 0;
}


myString* bagOfWords::get_Words()
{
	return _words;
}

int* bagOfWords::get_Freq()
{
	return _frequencies;
}

int bagOfWords::get_size()
{
	return _size;
}

void bagOfWords::setSize(int i)
{
	_size = i;
}

// print the bag of words in dictionary format
void bagOfWords::display() {
	cout << "Bag of Words: " << this->get_size() << endl;
	for (int i=0; i < this->get_size(); i++) {
		cout << this->_words[i] << ": " << this->_frequencies[i] << endl;
	}
}

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq()
{
	//uses bubble sort to sort by frequency
	for (int i=0; i<this->get_size() - 1; i++) {
				for (int j=0; j<(this->get_size()-i-1); j++) {
					if (this->_frequencies[j] > this->_frequencies[j+1]) {
						swapElements(j,j+1);
					}
				}
		}
}
// Function for swapping elements of the pointer arrays only works
// if j > i but my sorting methods only find instances where j > i
// if needed to use another sorting method I could add functionality for other cases
void bagOfWords::swapElements(int i,int j) {
	// make new bag
	bagOfWords* bag = new bagOfWords(this->_size);
	// move values to new bag before swap index
	for (int k=0; k < i; k++) {
		bag->_words[k] = this->_words[k];
		bag->_frequencies[k] = this->_frequencies[k];
	}
	// move values of swap index
	bag->_words[i] = this->_words[j];
	bag->_frequencies[i] = this->_frequencies[j];
	// move values between swap index
	for (int k=i+1; k<j; k++) {
		bag->_words[k] = this->_words[k];
		bag->_frequencies[k] = this->_frequencies[k];
	}
	//move other swap index values
	bag->_words[j] = this->_words[i];
	bag->_frequencies[j] = this->_frequencies[i];
	// move values after second swap index
	for (int k=j+1; k<this->_size; k++) {
		bag->_words[k] = this->_words[k];
		bag->_frequencies[k] = this->_frequencies[k];
	}
	// set the array to the new arrays which are pointers
	_words = bag->_words;
	_frequencies = bag->_frequencies;

}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords()
{
	// sorts the words alphabetically using bubble sort
	for (int i=0; i<this->get_size() - 1; i++) {
			for (int j=0; j<(this->get_size()-i-1); j++) {
				if (this->_words[j] > this->_words[j+1]) {
					swapElements(j,j+1);
				}
			}
	}
	/* Selection sort is unused
	int minIdx;
	for (int i=0; i < this->_size - 1; i++) {
		minIdx = i;
		for (int j=i+1; j<this->_size; j++) {
			if (this->_words[j] < this->_words[minIdx]) {
				minIdx = j;
			}
			swapElements(i, minIdx);
		}
	}
	*/
}
// This method takes a bag of words, sorts through a character array linearly
// because I couldn't get binary search to work for it, so it is kindof slow
// if it finds a stop word it doesn't add it to the new bag
bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords)
{
	// makes a new bag to insert elements into
	bool flag = true;
	bagOfWords* returner = new bagOfWords();
	//iterates through the current bag and the stop words, only allowing words that are not stop words to copy
	for (int i=0; i<this->_size;i++) {
		for (int j=0; j<numStopWords; j++) {
			if (this->_words[i] == stopWords[j]) {
				flag = false;
			}
		}
		// copies the values to the new bag
		if (flag) {
			returner->addAtIndex(returner->_size, this->_words[i]);
			returner->_frequencies[returner->_size - 1] = this->_frequencies[i];
		}
		flag = true;
	}
	return returner;

}
// this was the binary search method for the removestopwords method but it wouldn't work so it sits unused
bool bagOfWords::binarySearch(myString* stopWords, myString& wordToFind, int numStopWords) {
	int mid=0;
	int L=0;
	int R= numStopWords - 1;
	while (L <= R) {
		mid = L + R / 2;
		if (wordToFind == stopWords[mid]) {
			return true;
		}
		if (wordToFind > stopWords[mid]) {
			L = mid + 1;
		}
		else R = mid - 1;
	}
	return false;
}

// to search for a given word in _words, if not found it returns where it should be
int bagOfWords::binarySearch(myString& wordToFind)
{
	// defines useful variables and if size is zero go ahead and put the word in the zero spot
	if (this->_size == 0) {
		return 0;
	}
	int mid;
	int L = 0;
	int R = this->get_size() - 1;
	mid = 0;
	// iterates untill something returns
	while(true) {
		// sets the middle
		mid = (R + L) / 2;
		// if the middle is the word need to inc frequency of the word and return
		if (this->_words[mid]==wordToFind) {
			this->_frequencies[mid]++;
			return -1;
		}
		// if the middle is less than the word it is in the upper half
		else if(this->_words[mid] < wordToFind) {
			L = mid + 1;
			// if we've found where the word should be return where it should be inserted
			if (L > R) {
				return mid + 1;
			}
		}
		// otherwise word is in lower half
		else {
			R = mid - 1;
			// return where word should be inserted if we've found it
			if (L > R) {
				return mid;
			}
		}
	}
}
// this method will at the newWord at the given index to the bagOfwords, and inc frequency if it's the same
void bagOfWords::addAtIndex(int index, myString& newWord) {
	// if the word was found in binary search don't do anything
	if (index == -1) {
		return;
	}
	// make a temp string of increased size
	myString* temp = new myString[this->get_size() + 1];
	int* tempInt = new int[this->get_size() + 1];
	// copy the values up to the index into temp
	for (int i=0; i<index; i++) {
		temp[i] = this->_words[i];
		tempInt[i] = this->_frequencies[i];
	}
	// copy in the word and freq at the temp
	temp[index] = newWord;
	tempInt[index] = 1;
	// copy in all the words after the index
	for (int i=index+1; i<this->get_size() + 1; i++) {
		temp[i] = this->_words[i-1];
		tempInt[i] = this->_frequencies[i-1];
	}
	// increment size and delete the old arrays to clean up for the new ones
	_size++;
	delete [] _frequencies;
	delete [] _words;
	_frequencies = tempInt;
	_words = temp;
}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString & newWord)
{
	addAtIndex(binarySearch(newWord), newWord);

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {



	int numStopWords;
	char* token;
	myString* tokenString;

    //read the first number from the file that contains the number of stop words
	cin >> numStopWords;
	cout << "Number of Stop words: " << numStopWords << endl;
	myString* stopWordsList = new myString[numStopWords];

	//read the stop words
	for (int i=0; i < numStopWords; i++)
	{
		token = getNextToken ();
		stopWordsList[i] = token; //calls the overloaded = operator on myString class
	}

	//Now read a text and put them in the bagOfWords instance.
	bagOfWords* myBag = new bagOfWords ();

	token = getNextToken (); // v2: this was the error.

	while (token != NULL)
	{
		tokenString = new myString (token); //create a myString object with the token
		(*myBag).addWord(*tokenString); //add token to myBag
		token = getNextToken ();
	}


	// this should display the token and frequency;
	// note that becuase you are using binary search and insert the tokens will
	// be sorted alphabetically
	cout << endl;
	cout << "Input display:" << endl;
	(*myBag).display ();

	(*myBag).sortFreq ();
	cout << endl;
	cout << "myBag - Sorted based on frequency:" << endl;
	(*myBag).display ();

	(*myBag).sortWords();
	cout << endl;
	cout << "myBag - Sorted alphabetically:" << endl;
	(*myBag).display ();
	bagOfWords* newBag = new bagOfWords();
	newBag = (*myBag).removeStopWords(stopWordsList, numStopWords); // new parameter added here
	cout << endl;
	cout << "newBag - Sorted alphabetically:" << endl;
	(*newBag).display();

	(*newBag).sortFreq ();
	cout << endl;
	cout << "newBag - Sorted based on frequency:" << endl;
	(*newBag).display ();
	// TODO : destructors
	delete [] stopWordsList;
	delete myBag;
	delete newBag;

}
