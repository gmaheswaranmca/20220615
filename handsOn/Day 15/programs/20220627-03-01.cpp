/*
Exercise 20220607-03-01
Define RectangleEntity class of attributes width and length (public access).
Define service functions using encapsulated functions
1… readRect
2… printRect
3… findArea
4… findCircumference

Write driver code to invoke those functions

Learning outcome:
o encapsulated functions

*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
using namespace std;

class RectangleEntity {
public:
	int length;
	int width;
public:
	void readRect();
	void printRect();
	int findArea();
	int findCircumference();
};


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
	RectangleEntity rectangle{};
	rectangle.readRect();	//encapsulated member function
	rectangle.printRect();	//encapsulated member function
	int area = 0;
	int circumference = 0;
	area = rectangle.findArea(); //encapsulated member function
	circumference = rectangle.findCircumference(); //encapsulated member function
	cout << "The area of rectangle is " << area << endl;
	cout << "The circumference of rectangle is " << circumference << endl;
	return EXIT_SUCCESS;
}

/*
    We have completed the exercise as per specification.
    DEVIATION: 
    FIXED:  
    
Test:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Enter length:5
Enter width:3
Rectangle[length=5,width=3]
The area of rectangle is 15
The circumference of rectangle is 16    
^^^^^^^^^^^^^^^^^^^^^^^^^^^^    
*/

