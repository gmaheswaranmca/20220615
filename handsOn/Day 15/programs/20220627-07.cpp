/*
Exercise 
Define RectangleEntity class of attributes width and length (private access).
Define service functions using encapsulated functions
1… readRect
2… printRect
3… findArea
4… findCircumference

Write driver code to invoke those functions

Learning outcomes
o encapsulated functions 
o data hiding

o dynamic object for the class in the driver code 
	via new and delete 
	
	delete | heap deallocator to avoid memory leak 

*/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdlib>
using namespace std;
class RectangleEntity {
private:
	int length;
	int width;
public:
	RectangleEntity();
	~RectangleEntity();

	void readRect();
	void printRect();
	int findArea();
	int findCircumference();
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
int RectangleEntity::findArea() {
	return this->length * this->width;
}
int RectangleEntity::findCircumference() {
	return 2 * (this->length + this->width);
}

int main() {

	RectangleEntity* rectangleAddr = nullptr;
	rectangleAddr = new RectangleEntity();

	rectangleAddr->readRect();	//encapsulated member function
	rectangleAddr->printRect();	//encapsulated member function
	int area = 0;
	int circumference = 0;
	area = rectangleAddr->findArea(); //encapsulated member function
	circumference = rectangleAddr->findCircumference(); //encapsulated member function
	cout << "The area of rectangle is " << area << endl;
	cout << "The circumference of rectangle is " << circumference << endl;

	delete rectangleAddr;
	rectangleAddr = nullptr;

	return EXIT_SUCCESS;
}