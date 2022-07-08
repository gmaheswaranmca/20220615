/*
    Singleton : 
        Creational Design Pattern that ensures only one object creation for the class 
    
    C++ Implementation Points/Steps:
    General:
        1. make the constructor "private"
        2. define private static object pointer or reference 
        3. define static member function to return the object pointer or reference 
              (a) it has to create only one time the object for the class 
    Special
        4. delete copy constructor 
        5. delete assignment operator 
       
    
*/


#include<iostream>
#include<cstdlib>
using namespace std;
/**
 * The Singleton class defines the `getInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class LibraryPreference{
	public:
		int faculty_number_of_books_allowed;
		int student_number_of_books_allowed;
		double fine_amount_for_student_late_return;
	public:
	    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

		static LibraryPreference* getInstance(){//factory method 
		    /**
		     * !!!! Mutlithreading
             * This is a safer way to create an instance. instance = new "Singleton class" is
             * dangeruous in case two instance "threads" wants to access at the same time
             */
			if(_instance == nullptr){
				_instance = new LibraryPreference();
			}
			
			return _instance;
		}
        /**
         * Singletons should not be cloneable.
         */
        LibraryPreference(LibraryPreference &other) = delete; //copy constructor 
        /**
        * Singletons should not be assignable.
        */        
        void operator=(const LibraryPreference &) = delete; //assignment operator
	private:
		static LibraryPreference* _instance;
		
		    /**
             * The Singleton's constructor should always be private to prevent direct
             * construction calls with the `new` operator.
             */
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