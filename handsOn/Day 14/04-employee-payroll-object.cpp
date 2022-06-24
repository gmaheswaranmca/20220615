#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;

class Employee {
	private:
		int empId;
		string empName;
		double basicSalary;
		double hra;
		double da;
		double pf;
		double netSalary;
	public:
		Employee();
		Employee(string empName, double basicSalary);
		~Employee();
		void doPayrollCalculation();
		double getNetSalary();
};

Employee::Employee() {
	//empty
}
Employee::Employee(string empName, double basicSalary) {
	cout << "We are in constructor." << endl;
	this->empName = empName;
	this->basicSalary = basicSalary;
}
Employee::~Employee() {
	cout << "We are in destructor." << endl;
}
void Employee::doPayrollCalculation() {
	this->hra = (this->basicSalary / 100.0) * 15.0;
	this->da = (this->basicSalary / 100.0) * 20.0;
	this->pf = (this->basicSalary / 100.0) * 15.0;
	this->netSalary = this->basicSalary + this->hra + this->da + this->pf;
}
double Employee::getNetSalary() {
	return this->netSalary;
}


int main() {
	Employee emp("Maheswaran",10000);
	//1500,2000,1500 -> 15000

	emp.doPayrollCalculation();
	cout << "Net salary is " << emp.getNetSalary() << endl;

	return EXIT_SUCCESS;
}