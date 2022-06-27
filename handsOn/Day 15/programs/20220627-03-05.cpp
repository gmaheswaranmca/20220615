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
o constructors of all types 
o constructor overloadable 
o destructor 
o encapsulated functions defined inside the class 

*/

#define _CRT_SECURE_NO_WARNINGS
#define CONSTRUCTOR_TYPE 3 //1-Default Constructor, 2-Parameterized Constructor, 3-Copy Constructor
#include<iostream>
#include<cstdlib>
using namespace std;

class RectangleEntity {
public:
	int length;
	int width;
public:
	RectangleEntity() {
		cout << "We are in the constructor(default)." << endl;
		this->length = 0;
		this->width = 0;
	}
	RectangleEntity(int L, int W) : length(L), width(W) {
		cout << "We are in the constructor(parameterized)." << endl;
	}

	RectangleEntity(const RectangleEntity& rectangle) : length(rectangle.length), width(rectangle.width) {
		cout << "We are in the constructor(copy)." << endl;
	}
	~RectangleEntity() {
		cout << "We are in the destructor." << endl;
	}

	void readRect() {
		cout << "Enter length:"; cin >> this->length;
		cout << "Enter width:"; cin >> this->width;
	}
	void printRect() {
		cout << "Rectangle[length=" << this->length
			<< ",width=" << this->width
			<< "]" << endl;
	}
	int findArea() {
		return this->length * this->width;
	}
	int findCircumference() {
		return 2 * (this->length + this->width);
	}
};


int main() {
#if CONSTRUCTOR_TYPE==1
	RectangleEntity rectangle{};
#elif CONSTRUCTOR_TYPE==2
	RectangleEntity rectangle(0,0);
#elif CONSTRUCTOR_TYPE==3
	RectangleEntity rectangle_default(0, 0);
	RectangleEntity rectangle(rectangle_default);
#endif
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
        to experiment each type of the constructor only once 
    FIXED:  
        CONSTRUCTOR_TYPE macro will switch to type of the constructor 
    
Test:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Enter length:5
Enter width:3
Rectangle[length=5,width=3]
The area of rectangle is 15
The circumference of rectangle is 16    
^^^^^^^^^^^^^^^^^^^^^^^^^^^^    
*/