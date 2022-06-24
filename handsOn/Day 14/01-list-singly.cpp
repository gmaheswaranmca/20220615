#define STR_SIZE 2000
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<forward_list>
using namespace std;

bool isDebug = false;

struct SLNode {
public:
	double data;
	SLNode* next;
public:
	SLNode();
	SLNode(double val);
	~SLNode();
};

SLNode::SLNode() {
	this->data = 0.0;
	this->next = nullptr;
}
SLNode::SLNode(double val) {
	this->data = val;
	this->next = nullptr;
}
SLNode::~SLNode() {

}


struct SinglyLinkedList {
public:
	SLNode* head;
public:
	SinglyLinkedList();
	~SinglyLinkedList();
	void push_front(double val);
	void pop_front();
	double front();
};
SinglyLinkedList::SinglyLinkedList() {
	this->head = nullptr;
}
SinglyLinkedList::~SinglyLinkedList() {
	if (isDebug) { cout << endl; }
	while (this->head != nullptr) {
		if (isDebug) { cout << this->front() << " deleted." << endl; }
		this->pop_front();
	}
	if (isDebug) { cout << "We further managed memory well!!!" << endl; }
}
void SinglyLinkedList::push_front(double val) {	
	SLNode* node = new SLNode(val);//dynamic node={val,NULL}
	if (this->head == nullptr) {
		this->head = node;
	}
	else {
		node->next = head; 
		this->head = node; 
	}
}

void SinglyLinkedList::pop_front() {
	if (this->head == nullptr) {
		return;
	}
	SLNode* node = this->head;
	//ADJ
	this->head = this->head->next;
	//deallocator for dynamic node
	node->next = nullptr;
	delete node;
	node = nullptr;
}
double SinglyLinkedList::front() {
	return this->head->data;
}

void printData(SLNode* node) {
	if (isDebug) {
		cout << "[(" << node << "),data=" << node->data << ",next=" << node->next << "]" << " -> ";
		return;
	}
	
	cout << node->data << " -> ";
}

void traversal(SinglyLinkedList& list) {
	SLNode* node = list.head;
	cout << "The salaries are:" << endl;
	while (node != nullptr) {
		printData(node);//cout << node->data << " -> ";
		node = node->next;
	}
	cout << endl;
}
void traversalUsingNextRecursionForward(SLNode* node) {
	if (node == nullptr) {
		return;
	}
	printData(node); //cout << node->data << " -> ";
	traversalUsingNextRecursionForward(node->next);
}

void traversalUsingNextRecursionBackward(SLNode* node) {
	if (node == nullptr) {
		return;
	}
	traversalUsingNextRecursionBackward(node->next);
	printData(node); //cout << node->data << " -> ";

}
int main() {

	SinglyLinkedList salaries;

	int menu;
	do {
		cout << endl << endl << "Pick Choice" << endl;
		cout << "\t1 - Add Front, 2 - Delete Front" << endl;
		cout << "\t3 - Traversal" << endl;
		cout << "\tRecursion(next)4 - Forward Traversal, 5 - Backward Traversal" << endl;
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
			cout << "The salary at front is " << salaries.front() << endl;
			salaries.pop_front();
		}
		else if (3 == menu) {
			traversal(salaries);
		}
		else if (4 == menu) {
			cout << "The salaries are:" << endl;
			traversalUsingNextRecursionForward(salaries.head);
			cout << endl;
		}
		else if (5 == menu) {
			cout << "The reverse of the salaries are:" << endl;
			traversalUsingNextRecursionBackward(salaries.head);
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
	} while (((1 <= menu) && (menu <= 5)) || ((88 <= menu) && (menu <= 89)));

	return EXIT_SUCCESS;
}