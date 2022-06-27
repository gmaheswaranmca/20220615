/*
Exercise:
	Define RectangleEntity class of attributes width and length (public access).
	Define service functions outside the class to operate on attributes of class RectangleEntity.
		1… readRect
		2… printRect
		3… findArea
		4… findCircumference


		Write driver code to invoke those functions
		
		Call functions with Arguments by pointer, the object of RectangleEntity 
    o pointer to const Ex 1.2
    o const pointer Ex 1 2
    o const pointer to const Ex 1.2        
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

void readRect(RectangleEntity* rectangleAddr) {
	cout << "Enter length:"; cin >> rectangleAddr->length;
	cout << "Enter width:"; cin >> rectangleAddr->width;
}
void printRect(RectangleEntity* rectangleAddr) {
	cout << "Rectangle[length=" << rectangleAddr->length
		<< ",width=" << rectangleAddr->width
		<< "]" << endl;
}
int findArea(RectangleEntity* rectangleAddr) {
	return rectangleAddr->length * rectangleAddr->width;
}
int findCircumference(RectangleEntity* rectangleAddr) {
	return 2 * (rectangleAddr->length + rectangleAddr->width);
}

int main() {
	RectangleEntity rectangle{};
	readRect(&rectangle);	//call by pointer
	printRect(&rectangle);	//call by pointer
	int area = 0;
	int circumference = 0;
	area = findArea(&rectangle); //call by pointer
	circumference = findCircumference(&rectangle); //call by pointer
	cout << "The area of rectangle is " << area << endl;
	cout << "The circumference of rectangle is " << circumference << endl;
	return EXIT_SUCCESS;
}

/*
    We have completed the exercise as per specification.
    DEVIATION: 
    FIXED:   
    
    
    o pointer to const Ex 1.2
    o const pointer Ex 1 2
    o const pointer to const Ex 1.2 

    int x = 10; // x is variable 
	const int y = 20; //y is "const int" or "int const" //int const y=20;
	const int* ptrx = &x; // ptrx is pointer to "int const" or "const int" //int const* ptrx = &x;
	//"1. pointer to const" will not change the value of memory it is pointing
	cout << (*ptrx) << endl;
	//(*ptrx) = 15;// compile-time ERROR
	const int* ptry = &y; // pointer to "const int/int const"
	cout << (*ptry) << endl;
	int* const ptrxv2 = &x;//const pointer
	//"2. const pointer" cannot change its address
	int z = 20;
	//ptrxv2 = &z; // compile-time ERROR
	const int* const ptrxv3 = &x;
	//"3. const pointer to 'const int/int const' cannot change its address and the value it is pointing"
	//ptrxv3 = &z;// compile-time ERROR
	//(*ptrxv3) = 300;// compile-time ERROR
    
    
Test:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Enter length:5
Enter width:3
Rectangle[length=5,width=3]
The area of rectangle is 15
The circumference of rectangle is 16    
^^^^^^^^^^^^^^^^^^^^^^^^^^^^    
*/




/*
1. pointer to const             printRect 
2. const pointer                findArea 
3. const pointer to const       findCircumference 


In string.h or cstring header file 

    char* strcpy(char* dest, char const* source);  
    // source is "pointer to const" 
    char* strcat(char* dest, char const* source);  
    // source is "pointer to const" 
    char* strcat(char* const str, char const* const substring);  
    // str is "const pointer" 
    // substring is "const pointer to const" 
    int strcmp(char const* str1, char const* str2);
    //str1 is "pointer to const" 
    //str2 is "pointer to const" 
    char* strchr(char* const str, char ch);
    //str is "const pointer"
    char* strtok(char* str, char const* delimeter);
    //str is "read/write pointer" 
    //delimeter is "pointer to constant"

*/


#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
using namespace std;

class RectangleEntity {
public:
	int length;
	int width;
};

void readRect(RectangleEntity* rectangleAddr) {
	cout << "Enter length:"; cin >> rectangleAddr->length;
	cout << "Enter width:"; cin >> rectangleAddr->width;
}
void printRect(const RectangleEntity* rectangleAddr) {//pointer to const
	cout << "Rectangle[length=" << rectangleAddr->length
		<< ",width=" << rectangleAddr->width
		<< "]" << endl;
}
int findArea(RectangleEntity* const rectangleAddr) {//const pointer
	//RectangleEntity anotherRect;
	//rectangleAddr = &anotherRect;//compile-time ERR
	return rectangleAddr->length * rectangleAddr->width;
}
int findCircumference(const RectangleEntity* const rectangleAddr) {//const pointer to const
	//RectangleEntity anotherRect;
	//rectangleAddr = &anotherRect;//compile-time ERR
	//rectangleAddr->length = 40; //compile-time ERR
	return 2 * (rectangleAddr->length + rectangleAddr->width);
}

int main() {
	RectangleEntity rectangle{};
	readRect(&rectangle);	//call by pointer
	printRect(&rectangle);	//call by pointer
	int area = 0;
	int circumference = 0;
	area = findArea(&rectangle); //call by pointer
	circumference = findCircumference(&rectangle); //call by pointer
	cout << "The area of rectangle is " << area << endl;
	cout << "The circumference of rectangle is " << circumference << endl;
	return EXIT_SUCCESS;
}

