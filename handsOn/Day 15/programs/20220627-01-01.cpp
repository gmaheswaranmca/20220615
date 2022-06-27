/*
Exercise:
	Define RectangleEntity class of attributes width and length (public access).
	Define service functions outside the class to operate on attributes of class RectangleEntity.
		1… readRect
		2… printRect
		3… findArea
		4… findCircumference


		Write driver code to invoke those functions
		
		Call functions with Arguments by value, the object of RectangleEntity 
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

void readRect(RectangleEntity& rectangle) {
	cout << "Enter length:"; cin >> rectangle.length;
	cout << "Enter width:"; cin >> rectangle.width;
}
void printRect(RectangleEntity rectangle) {
	cout << "Rectangle[length=" << rectangle.length
		<< ",width=" << rectangle.width
		<< "]" << endl;
}
int findArea(RectangleEntity rectangle) {
	return rectangle.length * rectangle.width;
}
int findCircumference(RectangleEntity rectangle) {
	return 2 * (rectangle.length + rectangle.width);
}

int main() {
	RectangleEntity rectangle{};
	readRect(rectangle);	//call by reference
	printRect(rectangle);	//call by value
	int area = 0;
	int circumference = 0;
	area = findArea(rectangle); //call by value
	circumference = findCircumference(rectangle); //call by value
	cout << "The area of rectangle is " << area << endl;
	cout << "The circumference of rectangle is " << circumference << endl;
	return EXIT_SUCCESS;
}

/*
    We have completed the exercise as per specification.
    DEVIATION: 
        readRect is defined as function with argument call by reference
        
        In readRect, the attributes values are changed.
        To reflect the attributes to original object we pass to the function 
        we cannot have it as the value in function argument 
        
        If readRect has object argument as value, 
        The argument object and passed object both two are different.
        
    FIXED:   
        If readRect has object argument as reference, 
        The argument object and passed object both two are same.
Test:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Enter length:5
Enter width:3
Rectangle[length=5,width=3]
The area of rectangle is 15
The circumference of rectangle is 16    
^^^^^^^^^^^^^^^^^^^^^^^^^^^^        
*/