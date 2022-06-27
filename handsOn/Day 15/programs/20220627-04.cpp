/*

Exercise 
Define RectangleEntity class of attributes width and length (private access).
Define service functions outside the class to operate on attributes of class RectangleEntity.
1… readRect
2… printRect
3… findArea
4… findCircumference

Write driver code to invoke those functions

Learning outcome:

friend functions 
    | friend qualifier for the outside function to be given inside the class for that function 
    | to operate on private attributes, outside functions should be "friend" to the class 
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
	friend void readRect(RectangleEntity& rectangle);
	friend void printRect(const RectangleEntity& rectangle);
	friend int findArea(const RectangleEntity& rectangle);
	friend int findCircumference(const RectangleEntity& rectangle);
};

void readRect(RectangleEntity& rectangle) {
	cout << "Enter length:"; cin >> rectangle.length;
	cout << "Enter width:"; cin >> rectangle.width;
}
void printRect(const RectangleEntity& rectangle) {
	cout << "Rectangle[length=" << rectangle.length
		<< ",width=" << rectangle.width
		<< "]" << endl;
}
int findArea(const RectangleEntity& rectangle) {
	return rectangle.length * rectangle.width;
}
int findCircumference(const RectangleEntity& rectangle) {
	return 2 * (rectangle.length + rectangle.width);
}

int main() {
	RectangleEntity rectangle{};
	readRect(rectangle);	//call by reference
	printRect(rectangle);	//call by reference
	int area = 0;
	int circumference = 0;
	area = findArea(rectangle); //call by reference
	circumference = findCircumference(rectangle); //call by reference
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