#include<iostream>
#include<cstdlib>
using namespace std;
class LibraryPreference{
	public:
		int faculty_number_of_books_allowed;
		int student_number_of_books_allowed;
		double fine_amount_for_student_late_return;
	public:
		static LibraryPreference* getInstance(){//factory method 
			if(_instance == nullptr){
				_instance = new LibraryPreference();
			}
			
			return _instance;
		}
	private:
		static LibraryPreference* _instance;
		LibraryPreference():faculty_number_of_books_allowed(0),
			student_number_of_books_allowed(0),
			fine_amount_for_student_late_return(0.0){
			    
			    cout << "Constructed" << endl;
			
		}
};		
LibraryPreference* LibraryPreference::_instance = nullptr;
void printPref(LibraryPreference* pref_addr){
    cout << "faculty_number_of_books_allowed=" 
		<< pref_addr->faculty_number_of_books_allowed 
		<< endl;
	cout << "student_number_of_books_allowed=" 
		<< pref_addr->student_number_of_books_allowed 
		<< endl;
	cout << "fine_amount_for_student_late_return=" 
		<< pref_addr->fine_amount_for_student_late_return 
		<< endl;
}
int main(){
	LibraryPreference* pref_addr = LibraryPreference::getInstance();
	
	pref_addr->faculty_number_of_books_allowed = 3;
	pref_addr->student_number_of_books_allowed = 1;
	pref_addr->fine_amount_for_student_late_return = 0.0;
	
    printPref(pref_addr);
		
	LibraryPreference another_pref = (*pref_addr);    //No compile time error //constructor is not called // object is memory created
	printPref(&another_pref);                         //No singleton      
	
	//LibraryPreference* third_pref_addr = new LibraryPreference(); //compile time error
	//printPref(third_pref_addr);                                   //constr cannot be called explicitly
	
	//LibraryPreference* fourth_pref_addr = new LibraryPreference; //compile time error - trying to call default constructor
	//printPref(fourth_pref_addr);                                 //constr cannot be called explicitly  
	return EXIT_SUCCESS;
}