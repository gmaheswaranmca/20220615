#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
using namespace std;

class Employee {
public: 
	char name[257];
	double sal;
public: 
	friend istream& operator>>(istream& in, Employee& emp);
};
istream& operator>>(istream& in, Employee& emp) {
	cout << "Enter name:"; in >> emp.name;
	cout << "Enter salary:"; in >> emp.sal;
	return in;
}


int main() {
	//I Read from keyboard
	int numberOfEmployees;
	cout << "Enter number of employees:"; cin >> numberOfEmployees;
	Employee* employees = new Employee[numberOfEmployees];//head alloc: dealloc is pending???
	for (int I = 0; I < numberOfEmployees; I++) {
		cout << "Enter employee details at index " << I << endl;
		cin >> employees[I];
	}
	//II Write into file 
	//traversal the employees -> add each emp to file "emp.txt"
	ofstream output;
	output.open("emp.txt", ios::out | ios::trunc);//ios::out | ios::app //ios::in
	for (int I = 0; I < numberOfEmployees; I++) {
		output << employees[I].name << " " << employees[I].sal << endl;
	}
	output.close();

	//III Read from file 
	ifstream input;
	input.open("emp.txt", ios::in);
	string empLine;
	getline(input, empLine);
	int J = 0;
	while (empLine != "") {
		//cout << "Reading at " << J << endl << empLine << endl;
		stringstream inputSS(empLine);
		inputSS >> employees[J].name >> employees[J].sal;
		//cout << employees[J].name << " " << employees[J].sal << endl;
		getline(input, empLine);
		J++;
	}	
	input.close();

	//IV Write into console
	cout << endl << endl << "The employees from file are " << endl;
	for (int I = 0; I < numberOfEmployees; I++) {
		cout << employees[I].name << " " << employees[I].sal << endl;
	}
	delete[] employees;
	employees = nullptr;
	return EXIT_SUCCESS;
}


/*

Enter number of employees:3
Enter employee details at index 0
Enter name:Ram
Enter salary:5000
Enter employee details at index 1
Enter name:Rahul
Enter salary:6000
Enter employee details at index 2
Enter name:Dhoni
Enter salary:7000


The employees from file are
Ram 5000
Rahul 6000
Dhoni 7000

Check the file emp.txt 

*/