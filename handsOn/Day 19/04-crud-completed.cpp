//CRUD operations
//   Delete operation - DONE 
//   read all objects 
//   displayed all objects using tabular format 
//   look and feel of the tabular format data we achieved via iomanip flags 
//          such as setw, setprecision, setfill, left, right, fixed etc 
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;
class Employee {
public:
	char name[257];
	double sal;
public:
	friend istream& operator>>(istream& in, Employee& emp);
};
istream& operator>>(istream& in, Employee& emp) {
	//cout << "Enter name:"; in >> emp.name;
	string name;
	cout << "Enter name:";
	in.ignore();getline(in, name);
	strcpy(emp.name, name.c_str());//name.c_str() gives c-string
	cout << "Enter salary:"; in >> emp.sal;
	return in;
}

char emp_db_file_name[256] = "employee.dat";
char emp_db_tempfile_name[256] = "employee_temp.dat";

void emp_db_create(Employee& emp) {
	ofstream output;
	output.open(emp_db_file_name, ios::out | ios::app | ios::binary);
	if (output.is_open()) {
		output.write((char*)&emp, sizeof(Employee));
	}
	output.close();
}

void emp_db_search(Employee& emp, char searchText[256], bool& is_found) {
	is_found = false;
	ifstream input;
	input.open(emp_db_file_name, ios::in | ios::binary);
	if (input.is_open()) {
		Employee temp;
		while (input.read((char*)&temp, sizeof(Employee))) {
			if (strstr(temp.name, searchText) != nullptr) {
				emp = temp;
				is_found = true;
				break;
			}
		}
	}
	input.close();
}
void emp_db_update(Employee& emp) {
	fstream inout;
	inout.open(emp_db_file_name, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		Employee temp;
		int I = 0;
		while (inout.read((char*)&temp, sizeof(Employee))) {
			I++;
			if (strcmp(temp.name, emp.name) == 0) {
				int offset = (I - 1) * sizeof(Employee); // the position of the beginning of the object
				inout.seekg(offset, ios::beg);
				inout.write((char*)&emp, sizeof(Employee));
				break;
			}
		}
	}
	inout.close();
}

void emp_db_delete(Employee& emp) { //obj2
	ifstream in;
	ofstream out;
	in.open(emp_db_file_name, ios::in | ios::binary);//obj1ojb2obj3...obj10
	out.open(emp_db_tempfile_name, ios::out | ios::trunc | ios::binary);//obj1obj3...obj10
	if (in.is_open() && out.is_open()) {
		Employee temp;
		int I = 0;
		while (in.read((char*)&temp, sizeof(Employee))) {
			I++;
			if (strcmp(temp.name, emp.name) != 0) {//obj2.name == emp.name  
				out.write((char*)&temp, sizeof(Employee));
			}
		}
	}
	else if (!in.is_open()) {
		cout << "We cannot open the file " << emp_db_file_name << endl;
	}
	else if (!out.is_open()) {
		cout << "We cannot open the file " << emp_db_tempfile_name << endl;
	}
	out.close();
	in.close();
	remove(emp_db_file_name); // employee.dat deleted 
	rename(emp_db_tempfile_name, emp_db_file_name); //"employee_temp.dat" renamed as "employee.dat"
}
int emp_db_count() {
	int count=0;
	ifstream input;
	input.open(emp_db_file_name, ios::in | ios::binary);
	if (input.is_open()) {
		input.seekg(0, ios::end);
		count = input.tellg() / sizeof(Employee);
	}
	input.close();
	return count;
}
void emp_db_read_all(Employee* employees) {
	int I = 0;
	ifstream input;
	input.open(emp_db_file_name, ios::in | ios::binary);
	if (input.is_open()) {
		Employee temp;
		while (input.read((char*)&temp, sizeof(Employee))) {
			employees[I] = temp;
			I++;//1 2 3 4 5 6
		}
	}
	
	input.close();
}

void ui_employee_display_all() {
	int count = emp_db_count();
	Employee* employees = new Employee[count]{};//heap alloc'd
	emp_db_read_all(employees);
	cout << endl;
	cout << setw(70) << setfill('~') << " " << setfill(' ') << endl;
	cout << left << setw(5) << "Sno";
	cout << left << setw(50) << "Employee";
	cout << right << setw(15) << "Salary(Rs)";
	cout << endl;
	cout << setw(70) << setfill('~') << " " << setfill(' ') << endl;
	for (int I = 0; I < count; I++) {
		cout << left << setw(5) << (I+1);
		cout << left << setw(50) << employees[I].name;
		cout << right << setw(15) << fixed << setprecision(2) << employees[I].sal;
		cout << endl;
	}
	cout << setw(70) << setfill('~') << " " << setfill(' ') << endl;
	cout << endl;

	int menu;	
	cout << "Your choice(3-Update Employee,4-Delete Employee,0-Dont Dot Nothing):"; cin >> menu;
	
	if (3 == menu || 4 == menu) {
		int sno=0;
		if(3 == menu){
			cout << "Enter serial Number to update:"; cin >> sno;
			Employee employee = employees[sno - 1];
			//here you do update
			cout << "New Salary:"; cin >> employee.sal;
			emp_db_update(employee);
			cout << "Employee is updated successfully" << endl;
		}else if (4 == menu) {
			cout << "Enter serial Number to delete:"; cin >> sno;
			Employee employee = employees[sno - 1];
			char ch;			
			//here you do delete
			cout << "Are you sure to delete the employee(y/n)?"; cin >> ch;
			if (('y' == ch) || ('Y' == ch)) {
				emp_db_delete(employee);
				cout << "Employee is deleted successfully" << endl;
			}
		}
	}


	delete[] employees; //heap free'd
}

int main() {
	int menu;
	do {
		cout << endl << endl << "Choices are" << endl;
		cout << "\t1-Create Employee 2-Search Employee" << endl;
		cout << "\t3-Update Employee" << endl;
		cout << "\t4-Delete Employee" << endl;
		cout << "\t5-Display All Employees" << endl;
		cout << "\t0-Exit" << endl;
		cout << "Your choice:"; cin >> menu; 
		cout << endl;

		if (1 == menu) {
			Employee employee;
			cout << "Enter employee details" << endl;
			cin >> employee;
			emp_db_create(employee);
			cout << "Employee is created successfully" << endl;
		}
		else if (2 == menu) {
			char name[256];
			bool is_found;

			cout << "Enter employee name to search:"; cin >> name;
			Employee employee;
			emp_db_search(employee, name, is_found);
			if (is_found) {
				cout << "The employee we found is " << endl;
				cout << employee.name << " " << employee.sal << endl;

			}
			else {
				cout << "The employee cannot be found." << endl;
			}
		}
		else if (3 == menu) {
			char name[256];
			bool is_found;

			cout << "Enter employee name to search:"; cin >> name;
			Employee employee;
			emp_db_search(employee, name, is_found);
			if (is_found) {
				cout << "The employee we found is " << endl;
				cout << employee.name << " " << employee.sal << endl;
				//here you do update
				cout << "New Salary:"; cin >> employee.sal;
				emp_db_update(employee);
				cout << "Employee is updated successfully" << endl;
			}
			else {
				cout << "The employee cannot be found." << endl;
			}
		}
		else if (4 == menu) {
			char name[256];
			bool is_found;

			cout << "Enter employee name to search:"; cin >> name;
			Employee employee;
			emp_db_search(employee, name, is_found);
			if (is_found) {
				char ch;
				cout << "The employee we found is " << endl;
				cout << employee.name << " " << employee.sal << endl;
				//here you do update
				cout << "Are you sure to delete the employee(y/n)?"; cin >> ch;
				if (('y' == ch) || ('Y' == ch)) {
					emp_db_delete(employee);
					cout << "Employee is deleted successfully" << endl;
				}
			}
			else {
				cout << "The employee cannot be found." << endl;
			}
		}
		else if (5 == menu) {
			ui_employee_display_all();
		}
	} while ((1 <= menu && menu <= 5));
	return EXIT_SUCCESS;
}

