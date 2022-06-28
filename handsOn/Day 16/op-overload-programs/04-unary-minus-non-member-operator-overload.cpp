//non-member unary operator - overloaded for a Fraction object
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
	void print();
public:
	friend Fraction operator-(const Fraction& first);
};
Fraction::Fraction() :numerator(0), denominator(0) {

}
Fraction::Fraction(int n, int d) : numerator(n), denominator(d) {

}


void Fraction::print() {
	cout << "[" << this->numerator << "/" << this->denominator << "]";
}

Fraction operator-(const Fraction& first) { /* - (x/y) => ((-x)/y) */
	Fraction result;
	result.numerator = -first.numerator;
	result.denominator = first.denominator;

	int factor = gcf(result.numerator, result.denominator);
	if (factor > 1) {
		result.numerator /= factor;
		result.denominator /= factor;
	}
	return result;
}

int main() {
	//Fraction f1(1, 2), f2;
	Fraction f1(3, 8), f2;

	f2 = -f1; //f2 = operator-(f1);

	cout << "negate of ";
	f1.print();
	cout << " is ";
	f2.print();
	cout << endl;

	return EXIT_SUCCESS;
}

