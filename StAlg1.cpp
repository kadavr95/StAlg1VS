//used libraries
#include <fstream.h>//file stream
#include <iostream.h>//input, output stream
#include <conio.h>//getch
#include <iomanip>//string comparison
#include <windows.h>//localization

class Data{
	int key;

public:
	char value;

	Data(int key){
		this->key = key;
		// вариативно
		//value = (char)(key + 'a');
		value = (char)key;
	}

	int getKey(){
		return key;
	}
};

class Item{

public:
    Data *data;
	Item *next;
	Item *previous;

    Item(Data *data){
        this->data = data;
		this->next = NULL;
		this->previous = NULL;
	}

    ~Item(){
		delete data;
	}
};

class List{
	Item *head;

public:
    List(){
        head = NULL;
	}

	Item* getHead(){
		return head;
	}

	void print(Item* current){
		if (!List::isEmpty()) {
			cout << current->data->value << "\n";
			if (!(current->next == head)) {
				print(current->next);
			}
		//переход к следующему элементу
		}
		else
			cout << "\n";
		//std::cout << "Только здесь может быть вывод в консоль";
	}

	void push(Data *newData, char nextData){
		Data *data = newData;
		if (List::isEmpty()) {
			Item *newItem = new Item(data);
			head = newItem;
			newItem->next = head;
			newItem->previous = head;
		}
		else{
			if (!(List::searchByKey(nextData)==NULL)) {
				Item *current = List::searchByKey(nextData);
                Item *newItem = new Item(data);
				current->previous->next = newItem;
				newItem->next = current;
				newItem->previous=current->previous;
				current->previous = newItem;
				if (current == head) {
					head=newItem;
				}
			}
			else{
				Item *newItem = new Item(data);
				head->previous->next = newItem;
				newItem->next = head;
				newItem->previous=head->previous;
				head->previous = newItem;
			}

		}
	}

	Item* pop(int index){
		if (head!=NULL) {
			Item* current = head;
			if (index==0) {
                return NULL;
			}
			while (index>1){
				index--;
				current=current->next;
				if (current==head) {
					return NULL;
				}
			}
			current->previous->next=current->next;
			current->next->previous=current->previous;
			if (head==current) {
				head=current->next;
			}
			if (current==current->next) {
				head=NULL ;
			}
			Item* current2=current;
			Item *p_var = NULL;
			delete current;
			current = p_var;
			return current2;
		 }
		 return NULL;
	}

	bool isEmpty(){
		if (head == NULL)
			return true;
		else
			return false;
	}

	Item* searchByKey(char key){
		Item *current = head;
		if (!(head == NULL)) {
			while (true)
			{
				if (current->data->value ==  key)
					return current;
				if (current->next == head) {
					return NULL;
				}
				current=current->next;
			}
		}
		return NULL;
	}

	~List(){
		if (!List::isEmpty()) {
			Item *last = head->previous;
			Item *nextLast = NULL;
			while (last!=head) {
				nextLast=last->previous;
				delete last;
				last=nextLast;
			}
			delete last;
			head=NULL;
		}
	}
};

//functions prototypes
void OutputMainMenu();//menu and info
void AboutProgramme();

void userTest(){
	List myList;
    int command = 1;
    while (command != 0)
    {
        std::cout << "input 1, if you want print.....";
        std::cin >> command;
        switch(command){
            case 1:{
				//myList.print(myList.getHead());
				break;
			}
        }
    }
}

bool unitTesting(List *myList, int testNumber){
	switch (testNumber) {
		case 1://push to empty

			return true;
			break;
		case 2://remove from empty

			return true;
			break;
		case 3:
			return true;
			break;
		case 4:
			return true;
			break;
		case 5:
			return true;
			break;
		case 6:
			return true;
			break;
		case 7:
			return true;
			break;
		case 8:
			return true;
			break;
		case 9:
			return true;
			break;
		case 10:
			return true;
			break;
		case 99:
			for (int i = 0; i < 26000; i++) {
				myList->push(new Data(i), 0);
			}
			for (int i = 0; i < 26000; i++) {
				myList->pop(1);
			}
			return true;
			break;
		case 100:
			for (int i = 0; i < 26000; i++) {
				myList->push(new Data(i), 0);
			}
			delete myList;
			myList = new List();
			return true;
			break;
		default:
			return false;
	}
}

void main()//main function
{
	short OperationCode=0;
	List *myList = new List();
	int index;
	char value, valueNext;
	Data *data = new Data(2);
	Data *data2 = new Data(4);
	Item *it1 = new Item(data);
	Item *it2 = new Item(data2);
	it1->next = it2;
	Item *current = it1;
	SetConsoleOutputCP(1251);//console localization
	SetConsoleCP(1251);
	OutputMainMenu();//show menu of available commands
	while(OperationCode!=48)//repeat until exit
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		switch (OperationCode)//command choice
		{
			case 49://push to list
				cout<<"ADD TO LIST\n";
				if (myList->isEmpty()) {
				   myList = new List(); 
				}
				cout<<"Enter value to push:\n";//value input
				cin>>value;
				cout<<"Enter value of element before which will be pushed new element:\n";//value input
				cin>>valueNext;
				data = new Data(value);
				myList->push(data, valueNext);
				cout<<"Done!\n";
				break;
			case 50://pop from list
				cout<<"REMOVE FROM LIST\n";
				cout<<"Enter index to remove:\n";//index input
				cin>>index;
				current=myList->pop(index);
				if (current!=NULL) {
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
				if (myList->searchByKey(value)!=NULL)
					cout<<"Element found\n";
				else
					cout<<"Element not found\n";
				cout<<"Done!\n";
				break;
			case 52://list output
				cout<<"LIST PRINTOUT\n";
				myList->print(myList->getHead());
				cout<<"Done!\n";
				break;
			case 53://list destruction
				cout<<"LIST DESTRUСTION!\n";
				delete myList;
				myList = new List();
				cout<<"Done!\n";
				break;
			case 54://unit testing
				cout<<"UNIT TESTING\n";
				for (int i = 1; i < 100; i++) {
					cout<<"Test "<<i<<": ";
					if (unitTesting(myList, i)) {
						cout<<"Passed\n";
					}
					else{
						cout<<"Failed\n";
					}
				}
				cout<<"Done!\n";
				break;
			case 57://show info about programme
				AboutProgramme();
				break;
			case 48://programme shut down
				delete myList;
				exit;
				break;
			default://case of pressing button not assigned to commands
				OutputMainMenu();//show menu of available commands
		}
	}
}

void OutputMainMenu()//show menu of available commands in main menu
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

void AboutProgramme()//show info about the programme
{
	cout<<"ABOUT PROGRAMME\n\n";
	cout<<"Algorithms and data structures\n";
	cout<<"Practical assignment #1\n";
	cout<<"Variant GGA\n\n";
	cout<<"Version 0.0.13.0 build 20180216003000\n\n";
	cout<<"Development and testing: Yaskovich Dmitry (ISBO-05-15)\n\n";
	cout<<"Dimini Inc, 2018";
}
