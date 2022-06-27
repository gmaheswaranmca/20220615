/*
Exercise 
Define RectangleEntity class of attributes width and length (public access).
Define service functions using encapsulated functions
1… readRect
2… printRect
3… findArea
4… findCircumference

Write driver code to invoke those functions

Learning outcome:
o encapsulated functions
o const member functions 		| purpose: to operate on 'const object'
o non-const member functions  	| purpose: to operate on 'read/write object'

*/
#define _CRT_SECURE_NO_WARNINGS
#define CONST_FUNCTION 2 //1-non-const member function 2-const member function 
#include<iostream>
#include<cstdlib>
using namespace std;

class RectangleEntity {
public:
	int length;
	int width;
public:
	RectangleEntity();
	~RectangleEntity();

	void readRect();
	void printRect() const;
	void printRect();
	int findArea() ;
	int findArea() const;
	int findCircumference() const;
	int findCircumference() ;
};
RectangleEntity::RectangleEntity() {
	cout << "We are in the constructor(default)." << endl;
	this->length = 0;
	this->width = 0;
}

RectangleEntity::~RectangleEntity() {
	cout << "We are in the destructor." << endl;
}

void RectangleEntity::readRect() {
	cout << "Enter length:"; cin >> this->length;
	cout << "Enter width:"; cin >> this->width;
}
void RectangleEntity::printRect() {
	cout << "Rectangle[length=" << this->length
		<< ",width=" << this->width
		<< "]" << endl;
}
void RectangleEntity::printRect() const {
	cout << "Rectangle[length=" << this->length
		<< ",width=" << this->width
		<< "]" << endl;
}
int RectangleEntity::findArea() const {
	return this->length * this->width;
}
int RectangleEntity::findArea()  {
	return this->length * this->width;
}
int RectangleEntity::findCircumference() const {
	return 2 * (this->length + this->width);
}
int RectangleEntity::findCircumference()  {
	return 2 * (this->length + this->width);
}



int main() {
#if 1 == CONST_FUNCTION
	RectangleEntity rectangle{};
	rectangle.readRect();	//encapsulated member function
#else
	const RectangleEntity rectangle{};
#endif
	
	rectangle.printRect();	//encapsulated member function
	int area = 0;
	int circumference = 0;
	area = rectangle.findArea(); //encapsulated member function
	circumference = rectangle.findCircumference(); //encapsulated member function
	cout << "The area of rectangle is " << area << endl;
	cout << "The circumference of rectangle is " << circumference << endl;
	return EXIT_SUCCESS;
}