/*
Exercise 20220607-02
Define RectangleEntity class of attributes width and length (public access).
Define RectangleService class to define service functions to operate on attributes of class RectangleEntity.
1… readRect
2… printRect
3… findArea
4… findCircumference

Write driver code to invoke those functions

Learning outcome: 
o static functions
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
using namespace std;

class RectangleEntity {
public:
	int length;
	int width;
};

class RectangleService {
public:
	static void readRect(RectangleEntity& rectangle);
	static void printRect(const RectangleEntity& rectangle);
	static int findArea(const RectangleEntity& rectangle);
	static int findCircumference(const RectangleEntity& rectangle);
};

void RectangleService::readRect(RectangleEntity& rectangle) {
	cout << "Enter length:"; cin >> rectangle.length;
	cout << "Enter width:"; cin >> rectangle.width;
}
void RectangleService::printRect(const RectangleEntity& rectangle) {
	cout << "Rectangle[length=" << rectangle.length
		<< ",width=" << rectangle.width
		<< "]" << endl;
}
int RectangleService::findArea(const RectangleEntity& rectangle) {
	return rectangle.length * rectangle.width;
}
int RectangleService::findCircumference(const RectangleEntity& rectangle) {
	return 2 * (rectangle.length + rectangle.width);
}

int main() {
	RectangleEntity rectangle{};
	RectangleService::readRect(rectangle);	//call by reference
	RectangleService::printRect(rectangle);	//call by reference
	int area = 0;
	int circumference = 0;
	area = RectangleService::findArea(rectangle); //call by reference
	circumference = RectangleService::findCircumference(rectangle); //call by reference
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
*