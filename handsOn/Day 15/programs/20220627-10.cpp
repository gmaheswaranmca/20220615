/*
Exercise: inner object 

contained object: rectangle  
container object: box which contains rectangle 
box has rectangle -> composition 
    - relationship 
        whole-part relationship 
            car is whole 
            engine is part 
            car has engine 
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
using namespace std;
class Box;
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
	friend Box;
};
RectangleEntity::RectangleEntity() {
	//cout << "We are in the constructor(default)." << endl;
	this->length = 0;
	this->width = 0;
}

RectangleEntity::~RectangleEntity() {
	//cout << "We are in the destructor." << endl;
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


class Box {
	private: 
		RectangleEntity rectangle;
		int height;
	public:
		Box();
		~Box();

		void readBox();
		void printBox();
		int findArea();
		
};
Box::Box() :rectangle(){
	//
}
Box::~Box() {
	//
}

void Box::readBox() {
	this->rectangle.readRect();
	cout << "Enter height:"; cin >> this->height;
}
void Box::printBox(){
	cout << "Box[length=" << this->rectangle.length
		<< ",width=" << this->rectangle.width
		<< ",height=" << this->height
		<< "]" << endl;
}
int Box::findArea() {
	return this->rectangle.findArea() * this->height;
}
int main() {
	Box box{};

	box.readBox();	//encapsulated member function
	box.printBox();	//encapsulated member function
	int area = 0;
	area = box.findArea(); //encapsulated member function
	
	cout << "The area of box is " << area << endl;
	
	return EXIT_SUCCESS;
}

/*
Test: 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Enter length:5
Enter width:3
Enter height:3
Box[length=5,width=3,height=3]
The area of box is 45
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
*/