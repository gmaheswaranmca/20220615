//member binary operator + overloaded for two Fraction objects 
//non-member operator istream >> and ostream << operators overloaded for a fraction object
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
public:
	friend ostream& operator<<(ostream& out, const Fraction& first);
	friend istream& operator>>(istream& in, Fraction& first);
};
Fraction::Fraction() :numerator(0), denominator(0) {

}
Fraction::Fraction(int n, int d) : numerator(n), denominator(d) {

}
Fraction Fraction::operator+(const Fraction& second) {
	const Fraction& first = (*this);
	Fraction sum;
	sum.numerator = (first.numerator * second.denominator) + (second.numerator * first.denominator);
	sum.denominator = first.denominator * second.denominator;

	int factor = gcf(sum.numerator, sum.denominator);
	if (factor > 1) {
		sum.numerator /= factor;
		sum.denominator /= factor;
	}
	return sum;
}

ostream& operator<<(ostream& out, const Fraction& first) {
	out << "[" << first.numerator << "/" << first.denominator << "]";
	return out;//*****
}
istream& operator>>(istream& in, Fraction& first) {
	cout << "Enter numerator:"; in >> first.numerator;
	cout << "Enter denominator:"; in >> first.denominator;
	return in;//*****
}

void Fraction::print() {
	cout << "[" << this->numerator << "/" << this->denominator << "]";
}



int main() {
	//Fraction f1(1, 2), f2(1, 4), sum;
	Fraction f1(3, 8), f2(2, 4), sum;//(3 x 4 + 2 x 8) /( 8 x 4) = 28 / 32 = 7 / 8

	cout << "Enter first fraction number:" << endl;
	cin >> f1;
	cout << "Enter second fraction number:" << endl;
	cin >> f2;

	sum = f1 + f2; //sum = f1.operator+(f2);

	/*cout << "sum of ";
	f1.print();
	cout << " and ";
	f2.print();
	cout << " is ";
	sum.print();
	cout << endl;*/
	cout << "sum of " << f1 << " and " << f2 << " is " << sum << endl;

	return EXIT_SUCCESS;
}

