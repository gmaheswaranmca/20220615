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
o encapsulated functions defined outside the class 


1. constructor : special function without return type with arguments/no args | purpose: initialization 
    | initialize member data / attributes | open pritner, open socket, open file | heap allocator for attributes
    1.1 default constructor             ! no-argument !if constructor is defined explicitly, this is default 
    1.2 parameterized constructor       ! arguments/parameters we will pass to constructor to initialize attributes 
    1.3 copy constructor                ! argument is same class object (const reference) to initialize attributes 
    constructors overloadable ? 
        constructor can take many forms 
2. destructor : special function without return type without arguments | purpose : cleaning up 
    | heap deallocator for attributes | close printer, close socket, close file 
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
	RectangleEntity();
	RectangleEntity(int L, int W);
	RectangleEntity(const RectangleEntity& rectangle);
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
RectangleEntity::RectangleEntity(int L, int W) : length(L),width(W){
	cout << "We are in the constructor(parameterized)." << endl;
}
/*
RectangleEntity::RectangleEntity(int L, int W) {
	cout << "We are in the constructor(parameterized)." << endl;
	this->length = L;
	this->width = W;
}
*/
RectangleEntity::RectangleEntity(const RectangleEntity& rectangle) : length(rectangle.length), width(rectangle.width) {
	cout << "We are in the constructor(copy)." << endl;
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