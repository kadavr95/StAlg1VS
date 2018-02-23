//used libraries
#include <fstream.h>//file stream
#include <iostream.h>//input, output stream
#include <conio.h>//getch
#include <iomanip>//string comparison
#include <windows.h>//localization
#include <stdlib.h>//random
#include <time.h>//time
#include <string>//strings

class Data{//class of list nodes' data
	int key;

public:
	char value;

	Data(int key){//constructor
		this->key = key;
		value = (char)(key + '0');//just another magic value generator
	}

	int getKey(){//key getter
		return key;
	}
};

class Node{//class of list node

public:
    Data *data;
	Node *next;
	Node *previous;

	Node(Data *data){//constructor
        this->data = data;
		this->next = NULL;
		this->previous = NULL;
	}

	~Node(){//destructor
		delete data;
	}
};

class CircularDoublyLinkedList{//class of circular doubly linked list
	Node *head;

public:
	CircularDoublyLinkedList(){//constructor
		head = NULL;//setting head to default NULL value
	}

	Node* getHead(){//head address getter
		return head;
	}

	void print(Node* current){//list printout
		if (!CircularDoublyLinkedList::isEmpty()) {//if list is not empty
			cout << current->data->value << "\n";//printing value
			if (!(current->next == head)) {//moving to next element
				print(current->next);
			}
		}
		else//if list is empty
			cout << "\n";
	}

	void push(Data *newData, char nextData){//addition to list
		Data *data = newData;
		if (CircularDoublyLinkedList::isEmpty()) {//if list is empty
			Node *newNode = new Node(data);//node creation
			head = newNode;//head and neighbours links setting
			newNode->next = head;
			newNode->previous = head;
		}
		else{//if list is not empty
			Node *current = CircularDoublyLinkedList::searchByKey(nextData);//search presence of element to insert before it
			if (current!=NULL) {//if addition before element
				Node *newNode = new Node(data);//new node creation
				current->previous->next = newNode;//new node and neighbours nodes links rerouting
				newNode->next = current;
				newNode->previous=current->previous;
				current->previous = newNode;
				if (current == head) {//if insert to the first place
					head=newNode;//head adjustment
				}
			}
			else{//if addition to the tail
				Node *newNode = new Node(data);//new node creation
				head->previous->next = newNode;//new node and neighbours nodes links rerouting
				newNode->next = head;
				newNode->previous=head->previous;
				head->previous = newNode;
			}
		}
	}

	Node* pop(int index){//deletion from list
		if (head!=NULL) {//if list is not empty
			Node* current = head;
			if (index<=0) {//deny indeces lesser than one
				return NULL;
			}
			while (index>1) {//jumping to element we want to delete
				index--;
				current=current->next;
				if (current==head) {//deny indeces greater than quantity of list elements
					return NULL;
				}
			}
			current->previous->next=current->next;//rerouting neighbours nodes
			current->next->previous=current->previous;
			if (head==current) {//if element to delete is head
				head=current->next;//head adjustment
			}
			if (current==current->next) {//if element is the only one
				head=NULL;//head reset
			}
			Node *currentTemporary= current->data;//new temporary node to return
			Node *nullPointer = NULL;//new pointer to erase old data
			delete current;//element and pointer destruction
			current = nullPointer;
			return currentTemporary;
		}
		return NULL;//if list is empty
	}

	bool isEmpty(){//check if list is empty
		if (head == NULL)//if empty
			return true;
		else//if not empty
			return false;
	}

	Node* searchByKey(char key){//search element by value
		Node *current = head;//set head as current
		if (head != NULL) {//if list is not empty
			while (true)//unlimited recursion
			{
				if (current->data->value ==  key)//if element is found
					return current;
				if (current->next == head) {//if all list was checked
					return NULL;
				}
				current=current->next;//jump to next element
			}
		}
		return NULL;//if list is empty;
	}

	~CircularDoublyLinkedList(){//destructor
		if (!CircularDoublyLinkedList::isEmpty()) {//if list is not empty
			Node *last = head->previous;//set last and penultimate element
			Node *nextLast = NULL;
			while (last!=head) {//while element has more than one element
				nextLast=last->previous;//save link to penultimate element
				delete last;//delete last element
				last=nextLast;//set new last element
			}
			delete last;//deletion of last element in list
			head=NULL;//head reset
		}
	}
};

//functions prototypes
void outputMainMenu();//menu and info
void aboutProgramme();//about programme
bool unitTesting(int testNumber);//unit testing

const int TESTS_NUMBER=33;//number of units tests

void main()//main function
{
	short operationCode=0, passedTests=0;
	CircularDoublyLinkedList *myCircularDoublyLinkedList = new CircularDoublyLinkedList();
	int index;
	char value, valueNext;
	Node *current;
	srand (time(NULL));//initialization of random seed
	SetConsoleOutputCP(1251);//console localization
	SetConsoleCP(1251);
	outputMainMenu();//show menu of available commands
	while(operationCode!=48)//repeat until exit
	{
		operationCode=getch();//get command
		system("cls");//clear console screen
		switch (operationCode)//command choice
		{
			case 49://push to list
				cout<<"ADD TO LIST\n";
				cout<<"Enter value to push:\n";//value input
				cin>>value;
				cout<<"Enter value of element before which will be pushed new element:\n";//next element value input
				cin>>valueNext;
				myCircularDoublyLinkedList->push(new Data(value), valueNext);//node addition
				cout<<"Done!\n";
				break;
			case 50://pop from list
				cout<<"REMOVE FROM LIST\n";
				cout<<"Enter index to remove:\n";//index input
				cin>>index;
				current=myCircularDoublyLinkedList->pop(index);//node deletion
				if (current!=NULL) {//check if deletion was successful
					cout<<"Element \""<<current->data->value<<"\" was successfully removed\n";
				}
				else
					cout<<"List does not contain element with index "<<index<<endl;
				cout<<"Done!\n";
				break;
			case 51://search data
				cout<<"SEARCH IN LIST\n";
				cout<<"Enter value to search:\n";//value input
				cin>>value;
				if (myCircularDoublyLinkedList->searchByKey(value)!=NULL)
					cout<<"Element \""<<myCircularDoublyLinkedList->searchByKey(value)<<"\" found\n";
				else
					cout<<"Element \""<<myCircularDoublyLinkedList->searchByKey(value)<<"\" not found\n";
				cout<<"Done!\n";
				break;
			case 52://list output
				cout<<"LIST PRINTOUT\n";
				myCircularDoublyLinkedList->print(myCircularDoublyLinkedList->getHead());
				cout<<"Done!\n";
				break;
			case 53://list destruction
				cout<<"LIST DESTRUÑTION!\n";
				delete myCircularDoublyLinkedList;
				myCircularDoublyLinkedList = new CircularDoublyLinkedList();
				cout<<"Done!\n";
				break;
			case 54://unit testing
				cout<<"UNIT TESTING\n";
				for (int i = 0; i < TESTS_NUMBER; ) {//go through all tests
					i++;//go to next test
					cout<<"Test "<<setw(2)<<i<<": ";//print test number
					if (unitTesting(i)) {//if current test passed
						cout<<"Passed\n";
						passedTests++;//increase quantity of passed tests
					}
					else{//if current test failed
						cout<<"Failed\n";
					}
				}
				cout<<"\nPassed tests: "<<passedTests<<"/"<<TESTS_NUMBER<<"\n";//print summary
				passedTests=0;//reset passed tests quantity
				cout<<"Done!\n";
				break;
			case 57://show info about programme
				aboutProgramme();
				break;
			case 48://programme shut down
				delete myCircularDoublyLinkedList;//delete list
				exit;
				break;
			default://case of pressing button not assigned to commands
				outputMainMenu();//show menu of available commands
		}
	}
}

bool unitTesting(int testNumber){//auto testing if everything is working as intended
	int value, valueSecond;//initializing variables
	char valueNext;
	Node *current;
	string listString="";
	CircularDoublyLinkedList *myCircularDoublyLinkedList = new CircularDoublyLinkedList();
	switch (testNumber) {
		case 1://add to empty list
			value=rand() % 1000 + 1;//generate random values
			valueNext=rand() % 1000 + 1;
			myCircularDoublyLinkedList->push(new Data(value), valueNext);//node addition
			if (myCircularDoublyLinkedList->searchByKey(value)==NULL){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 2://remove from empty list
			if (myCircularDoublyLinkedList->pop(rand() % 1000 + 1)==NULL){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 3://search in empty list
			if (myCircularDoublyLinkedList->searchByKey(rand() % 1000 + 1)==NULL){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 4://print empty list
			std::cout.setstate(std::ios_base::failbit);//suppressing console list printout
			myCircularDoublyLinkedList->print(myCircularDoublyLinkedList->getHead());
			std::cout.clear();//removing suppression
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 5://destroy empty list
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 6://add to list with 1 element before this element
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), 'a');
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;//getting nodes values
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			if (listString=="ba"){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//it test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 7://add to list with 1 element to the end
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;//getting nodes values
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			if (listString=="ab"){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 8://remove from list with 1 element
			myCircularDoublyLinkedList->push(new Data('1'), '0');//node addition
			if (myCircularDoublyLinkedList->pop(1)->data->value=='a'){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 9://remove wrong element from list with 1 element
			myCircularDoublyLinkedList->push(new Data('1'), '0');//node addition
			if (myCircularDoublyLinkedList->pop(2)==NULL){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 10://print list with 1 element
			myCircularDoublyLinkedList->push(new Data('1'), '0');//node addition
			std::cout.setstate(std::ios_base::failbit);//suppressing console list printout
			myCircularDoublyLinkedList->print(myCircularDoublyLinkedList->getHead());
			std::cout.clear();//removing suppression
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 11://destroy list with 1 element
			myCircularDoublyLinkedList->push(new Data('1'), '0');//node addition
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 12://add to list with 2 elements before first element
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), 'a');
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;//nodes deletion
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			if (listString=="cab"){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 13://add to list with 2 elements before second element
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), 'b');
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;//nodes deletion
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			if (listString=="acb"){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 14://add to list with 2 elements to the end
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;//nodes deletion
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			if (listString=="abc"){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			return true;
			break;
		case 15://remove first element from list with 2 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			if (myCircularDoublyLinkedList->pop(1)->data->value=='a'){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 16://remove last element from list with 2 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			if (myCircularDoublyLinkedList->pop(2)->data->value=='b'){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 17://remove wrong element from list with 2 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			if (myCircularDoublyLinkedList->pop(3)==NULL){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 18://print list with 2 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			std::cout.setstate(std::ios_base::failbit);//suppressing console list printout
			myCircularDoublyLinkedList->print(myCircularDoublyLinkedList->getHead());
			std::cout.clear();//removing suppression
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 19://destroy list with 2 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 20://add to list with 5 elements before first element
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			myCircularDoublyLinkedList->push(new Data('6'), 'a');
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;//nodes deletion
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			if (listString=="fabcde"){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 21://add to list with 5 elements in the middle of list
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			myCircularDoublyLinkedList->push(new Data('6'), 'd');
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;//nodes deletion
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			if (listString=="abcfde"){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 22://add to list with 5 elements to the end
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			myCircularDoublyLinkedList->push(new Data('6'), '0');
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;//nodes deletion
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			listString+=myCircularDoublyLinkedList->pop(1)->data->value;
			if (listString=="abcdef"){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 23://remove first element from list with 5 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			if (myCircularDoublyLinkedList->pop(1)->data->value=='a'){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 24://remove element from the middle of the list with 5 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			if (myCircularDoublyLinkedList->pop(3)->data->value=='c'){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 25://remove last element from list with 5 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			if (myCircularDoublyLinkedList->pop(5)->data->value=='e'){//it test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 26://remove wrong element from list with 5 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			if (myCircularDoublyLinkedList->pop(6)==NULL){//if test passed
				delete myCircularDoublyLinkedList;
				return true;
			}
			else{//if test failed
				delete myCircularDoublyLinkedList;
				return false;
			}
			break;
		case 27://print list with 5 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			std::cout.setstate(std::ios_base::failbit);//suppressing console list printout
			myCircularDoublyLinkedList->print(myCircularDoublyLinkedList->getHead());
			std::cout.clear();//removing suppression
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 28://destroy list with 5 elements
			myCircularDoublyLinkedList->push(new Data('1'), '0');//nodes addition
			myCircularDoublyLinkedList->push(new Data('2'), '0');
			myCircularDoublyLinkedList->push(new Data('3'), '0');
			myCircularDoublyLinkedList->push(new Data('4'), '0');
			myCircularDoublyLinkedList->push(new Data('5'), '0');
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 29://add thousands of elements and delete them
			for (int i = 0; i < 26000; i++) {
				myCircularDoublyLinkedList->push(new Data(i), 0);
			}
			for (int i = 0; i < 26000; i++) {
				myCircularDoublyLinkedList->pop(1);
			}
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 30://add and delete thousands of elements
			for (int i = 0; i < 26000; i++) {
				myCircularDoublyLinkedList->push(new Data(i), 0);
				myCircularDoublyLinkedList->pop(1);
			}
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 31://add element to list and destroy it thousands of times
			for (int i = 0; i < 26000; i++) {
				myCircularDoublyLinkedList->push(new Data(i), 0);
				delete myCircularDoublyLinkedList;
				myCircularDoublyLinkedList = new CircularDoublyLinkedList();
			}
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 32://add thousands of elements and destroy list
			for (int i = 0; i < 26000; i++) {
				myCircularDoublyLinkedList->push(new Data(i), 0);
			}
			delete myCircularDoublyLinkedList;
			return true;
			break;
		case 33://randomly add thousands of elements and delete them
			for (int i = 0; i < 26000; i++) {
				myCircularDoublyLinkedList->push(new Data(rand() % 1000 + 1), rand() % 1000 + 1);
				myCircularDoublyLinkedList->pop(rand() % 1000 + 1);
			}
			delete myCircularDoublyLinkedList;
			return true;
			break;
		default://if unknown unit test number
			return false;
	}
}

void outputMainMenu()//show menu of available commands in main menu
{
	cout<<"MAIN MENU\n";
	cout<<"Choose operation:\n";
	cout<<"Press 1 to add data into list\n";
	cout<<"Press 2 to remove data from list\n";
	cout<<"Press 3 to search data in list\n";
	cout<<"Press 4 to print list\n";
	cout<<"Press 5 to clear list\n";
	cout<<"Press 6 to perform unit testing\n";
	cout<<"Press 9 to get info about the programme\n";
	cout<<"Press 0 to exit";
}

void aboutProgramme()//show info about the programme
{
	cout<<"ABOUT PROGRAMME\n\n";
	cout<<"Algorithms and data structures\n";
	cout<<"Practical assignment #1\n";
	cout<<"Variant GGA\n\n";
	cout<<"Version 0.1.2.0 build 20180224014500\n\n";
	cout<<"Development and testing: Yaskovich Dmitry (ISBO-05-15)\n\n";
	cout<<"Dimini Inc, 2018";
}
