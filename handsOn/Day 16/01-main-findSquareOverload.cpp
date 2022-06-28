#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
using namespace std;

int findSquare(int num) {//I	
	return num * num;
}
double findSquare(double num) {//II	
	return num * num;
}
int main() {
	int age;
	cout << "Enter age:"; cin >> age;
	double salary;
	cout << "Enter salary:"; cin >> salary;
	
	int ageSquare = findSquare(age);//I
	double salarySquare = findSquare(salary);//II

	cout << "The square of " << age << " is " << ageSquare << endl;
	cout << "The square of "  << salary << " is " << salarySquare << endl;

	return EXIT_SUCCESS;
}