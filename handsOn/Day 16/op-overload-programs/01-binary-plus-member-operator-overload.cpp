#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;

int gcf(int a, int b) {
	a = abs(a);
	b = abs(b);
	while (a != b) {
		if (a > b)  
			a -= b;
		else
			b -= a;
	}
	return a;
}

class Fraction {/*		x/y		*/
private: 
	int numerator;
	int denominator;
public: 
	Fraction();
	Fraction(int n, int d);
	Fraction operator+(const Fraction& second);

	void print();
};
Fraction::Fraction():numerator(0),denominator(0) {

}
Fraction::Fraction(int n, int d) : numerator(n), denominator(d) {

}
Fraction Fraction::operator+(const Fraction& second) {
	const Fraction& first = (*this);
	Fraction sum;
	sum.numerator = (first.numerator * second.denominator) + (second.numerator * first.denominator);
	sum.denominator = first.denominator * second.denominator;

	int factor = gcf(sum.numerator, sum.denominator);
	if(factor > 1){
		sum.numerator /= factor;
		sum.denominator /= factor;
	}
	return sum;
}

void Fraction::print() {
	cout << "[" << this->numerator << "/" << this->denominator << "]";
}


int main() {
	//Fraction f1(1, 2), f2(1, 4), sum;
	Fraction f1(3, 8), f2(2, 4), sum;//(3 x 4 + 2 x 8) /( 8 x 4) = 28 / 32 = 7 / 8
	sum = f1 + f2;
	cout << "sum of "; 
	f1.print(); 
	cout << " and "; 
	f2.print(); 
	cout << " is ";
	sum.print();
	cout << endl;

	return EXIT_SUCCESS;
}