#define STR_SIZE 2000
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<forward_list>
using namespace std;

bool isDebug = false;

struct DLNode {
public:
	DLNode* prev;
	double data;
	DLNode* next;
public:
	DLNode();
	DLNode(double val);
	~DLNode();
};

DLNode::DLNode() {
	this->prev = nullptr;
	this->data = 0.0;
	this->next = nullptr;
}
DLNode::DLNode(double val) {
	this->prev = nullptr;
	this->data = val;
	this->next = nullptr;
}
DLNode::~DLNode() {

}


struct DoublyLinkedList {
public:
	DLNode* head;
	DLNode* tail;
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void push_front(double val);
	void pop_front();
	double front();

	void push_back(double val);
	void pop_back();
	double back();
};
DoublyLinkedList::DoublyLinkedList() {
	this->head = nullptr;
	this->tail = nullptr;
}
DoublyLinkedList::~DoublyLinkedList() {
	if (isDebug) { cout << endl; }
	while (this->head != nullptr) {
		if (isDebug) { cout << this->front() << " deleted." << endl; }
		this->pop_front();
	}
	if (isDebug) { cout << "We further managed memory well!!!" << endl; }
	this->head = nullptr;
	this->tail = nullptr;
}
void DoublyLinkedList::push_front(double val) {
	DLNode* node = new DLNode(val);
	//CODE HERE ;attach the node in the DLL ; adjust both head and tail
	if(this->head == nullptr){
		this->head = node;
		this->tail = node;
	}
	else {
		node->next = this->head;
		node->next->prev = node;
		this->head = node;
	}
}

void DoublyLinkedList::pop_front() {
	if (this->head == nullptr) {
		return;
	}
	DLNode* node = this->head;//deleteble node

	//CODE HERE ; detach the node ; adjust both head and tail
	if(node->next != nullptr){
		//list of two or more nodes
		node->next->prev = nullptr;
		this->head = node->next;
	}
	else {
		//list of one node
		this->head = nullptr;
		this->tail = nullptr;
	}

	//deallocation of node
	node->next = nullptr;
	node->prev = nullptr;
	delete node;
	node = nullptr;
}
double DoublyLinkedList::front() {
	if (this->head == nullptr) {
		throw "List is empty.";
	}
	return this->head->data;
}
void DoublyLinkedList::push_back(double val) {
	DLNode* node = new DLNode(val);
	//CODE HERE ;attach the node in the DLL ; adjust both head and tail
	if (this->tail == nullptr) {
		this->head = node;
		this->tail = node;
	}
	else {
		node->prev = this->tail;
		node->prev->next = node;
		this->tail = node;
	}
}
void DoublyLinkedList::pop_back() {
	if (this->tail == nullptr) {
		return;
	}
	DLNode* node = this->tail;

	//CODE HERE ; detach the node ; adjust both head and tail
	if (node->prev != nullptr) {
		//list of two or more nodes
		node->prev->next = nullptr;
		this->tail = node->prev;
	}
	else {
		//list of one node
		this->head = nullptr;
		this->tail = nullptr;
	}

	//deallocation of node
	node->next = nullptr;
	node->prev = nullptr;
	delete node;
	node = nullptr;
}
double DoublyLinkedList::back() {
	if (this->tail == nullptr) {
		throw "List is empty.";
	}
	return this->tail->data;
}
void printData(DLNode* node) {
	if (isDebug) {
		cout << "[(" << node << "),prev=" << node->prev << ",data=" << node->data << ",next=" << node->next << "]" << " -> ";
		return;
	}

	cout << node->data << " -> ";
}
void traversalForward(DoublyLinkedList& list) {
	DLNode* node = list.head;
	cout << "The salaries are:" << endl;
	while (node != nullptr) {
		printData(node);//cout << node->data << " -> ";
		node = node->next;
	}
	cout << endl;
}
void traversalBackward(DoublyLinkedList& list) {
	DLNode* node = list.tail;
	cout << "The reverse of salaries are:" << endl;
	while (node != nullptr) {
		printData(node);//cout << node->data << " -> ";
		node = node->prev;
	}
	cout << endl;
}
void traversalUsingNextRecursionForward(DLNode* node) {
	if (node == nullptr) {
		return;
	}
	printData(node);//cout << node->data << " -> ";
	traversalUsingNextRecursionForward(node->next);
}

void traversalUsingNextRecursionBackward(DLNode* node) {
	if (node == nullptr) {
		return;
	}
	traversalUsingNextRecursionBackward(node->next);
	printData(node);//cout << node->data << " -> ";
}
void traversalUsingPrevRecursionBackward(DLNode* node) {
	if (node == nullptr) {
		return;
	}
	printData(node);//cout << node->data << " -> ";
	traversalUsingPrevRecursionBackward(node->prev);
}

void traversalUsingPrevRecursionForward(DLNode* node) {
	if (node == nullptr) {
		return;
	}
	traversalUsingPrevRecursionForward(node->prev);
	printData(node);//cout << node->data << " -> ";
}
int main() {

	DoublyLinkedList salaries;

	int menu;
	do {
		cout << endl << endl;
		cout << "Pick Choice" << endl;
		cout << "\t1 - Add Front, 2 - Delete Front" << endl;
		cout << "\t3 - Add Back, 4 - Delete Back" << endl;
		cout << "\t5 - Traversal Forward, 6-Traversal Backward" << endl;
		cout << "\tRecursion(Next)7 -Traversal Forward, 8-Traversal Backward" << endl;
		cout << "\tRecursion(Prev)9 -Traversal Forward, 10-Traversal Backward" << endl;
		cout << "\t88-Switch On Debug, 89-Switch Off Debug" << endl;
		cout << "\t0 - Exit" << endl;
		cout << "Your Choice: "; cin >> menu;
		cout << endl;
		if (1 == menu) {
			double data;
			cout << "Enter data:"; cin >> data;
			salaries.push_front(data);
		}
		else if (2 == menu) {
			try {
				cout << "The salary at front is " << salaries.front() << endl;
				salaries.pop_front();
			}
			catch (const char* ex) {
				cout << "'" << ex << "' is handled" << endl;
			}
		}
		else if (3 == menu) {
			double data;
			cout << "Enter data:"; cin >> data;
			salaries.push_back(data);
		}
		else if (4 == menu) {
			try{
				cout << "The salary at front is " << salaries.back() << endl;
				salaries.pop_back();
			}
			catch (const char* ex) {
				cout << "'" << ex << "' is handled" << endl;
			}
		}
		else if (5 == menu) {
			traversalForward(salaries);
		}
		else if (6 == menu) {
			traversalBackward(salaries);
		}
		else if (7 == menu) {
			cout << "(Recursion-Next)The salaries are:" << endl;
			traversalUsingNextRecursionForward(salaries.head);
			cout << endl;
		}
		else if (8 == menu) {
			cout << "(Recursion-Next)The reverse of salaries are:" << endl;
			traversalUsingNextRecursionBackward(salaries.head);
			cout << endl;
		}
		else if (9 == menu) {
			cout << "(Recursion-Prev)The salaries are:" << endl;
			traversalUsingPrevRecursionForward(salaries.tail);
			cout << endl;
		}
		else if (10 == menu) {
			cout << "(Recursion-Next)The reverse of salaries are:" << endl;
			traversalUsingPrevRecursionBackward(salaries.tail);
			cout << endl;
		}
		else if (88 == menu) {
			isDebug = true;
		}
		else if (89 == menu) {
			isDebug = false;
		}
		else {
			cout << "App is shutting down...";
		}
	} while (((1 <= menu) && (menu <= 10)) || ((88 <= menu) && (menu <= 89)));

	return EXIT_SUCCESS;
}