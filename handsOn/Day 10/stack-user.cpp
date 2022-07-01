/*
---------------------------------------------------------------------
1.6 Implement Stack Class / Structure [User Defined] 	
	to define five salaries (double) 
    Use menu-driven based Add and Delete
    With Exception Handling
---------------------------------------------------------------------
*/
#define STACK_SIZE 5
#include<iostream>
#include<cstdlib>

using namespace std;

class GGStack {
	private:
		double salaries[STACK_SIZE];
		int topIndex;
		int count;
	public:
		GGStack();
		void push(double val);
		int size();
		bool empty();
		void pop();
		double top();
};

GGStack::GGStack() {
	this->topIndex = -1;
	this->count = 0;
}

int GGStack::size() {
	return this->count;
}
bool GGStack::empty() {
	return (this->count == 0);
}

double GGStack::top() {
	return salaries[this->topIndex];
}

void GGStack::push(double val) {
	if (this->count >= STACK_SIZE) {
		throw "Stack is full";
	}

	this->topIndex++;
	this->count++;

	salaries[this->topIndex] = val;
}

void GGStack::pop() {
	if (this->count <= 0) {
		throw "Stack is empty";
	}
	this->topIndex--;
	this->count--;
}

int main() {
	GGStack salaries;

	int menu;
	do {
		cout << "Choice(1-Add, 2-Delete, 3-Exit):";
		cin >> menu;

		if (1 == menu) {
			double sal;
			cout << "Enter the salary:";
			cin >> sal;
            try{
				salaries.push(sal);
			}
			catch (const char* ex) {
				cout << "(handler of object 'const char*')Stack is Full"<< endl;
                cout << "\t the exception is '" << ex << "'" << endl;
			}
			catch (...) {
				cout << "(default exception handler)Stack is Full"<< endl;
			}
			
		}
		else if (2 == menu) {
			try{
				cout << "Pay salary of worth Rs." << salaries.top() << endl; // PROCESS
				salaries.pop();
			}
			catch (const char* ex) {
				cout << "(handler of object 'const char*')Stack is Empty"<< endl;
                cout << "\t the exception is '" << ex << "'" << endl;
			}
			catch (...) {
				cout << "(default exception handler)Stack is Empty"<< endl;
			}
		}
		else {
			cout << "Shutting Down App!!!" << endl;
		}
	}while(1==menu || 2==menu);

	return EXIT_SUCCESS;
}