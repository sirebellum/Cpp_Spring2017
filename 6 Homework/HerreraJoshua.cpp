/* Joshua Herrera
   Homework 6 */

#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;

class complex
{
	
private:

	double real;
	double img;
 
public:

	complex(double _real, double _img);
	double get_real();
	double get_img();
	double calc_phase();
	friend void print(complex c);
	complex operator+ (const complex& num);
	complex operator* (const complex& num);
 
};


int main() {
	
	complex c1(4, -5);
	complex c2(2,  9);
	
	cout << "c1: ";
	print(c1);
	cout << "c2: ";
	print(c2);
	
	cout << "phase c1: " << c1.calc_phase() << endl;
	cout << "phase c2: " << c2.calc_phase() << endl;

	cout << "c1 + c2: ";
	print(c1 + c2);
	
	cout << "c1 * c2: ";
	print(c1 * c2);
	
	return 0;
}


//Function Definitions
complex::complex(double _real, double _img) {
	real = _real;
	img  = _img;
}
double  complex::get_real() {return real; }
double  complex::get_img() {return img; }
double  complex::calc_phase() {return atan(img/real); }
complex complex::operator+ (const complex& num) {
	complex result(0, 0);
	result.real = this->real + num.real;
	result.img  = this->img  + num.img;
	return result;
}
complex complex::operator* (const complex& num) {
	complex result(0, 0);
	result.real = this->real*num.real + -1*(this->img*num.img);
	result.img  = this->real*num.img  + this->img*num.real;
	return result;
}
void print(complex c) {
	if (c.img > 0)
		cout << c.real << "+" << c.img << "i" << endl;
	else
		cout << c.real << c.img << "i" << endl;
}

