//============================================================================
// Name        : complex-number-calculator.cpp
// Author      : R. G. Nagel
// Version     :
// Copyright   : Your copyright notice
// Description : Complex Number Calculator in C++
//============================================================================

#include <iostream>
#include <list>
#include <math.h>
using namespace std;

class ComplexNumber {
private:
	float re;
	float im;
	float module;
	float angle;

	void setModule()
	{
		this->module = sqrt(pow(this->re, 2) + pow(this->im, 2));
	}
	void setAngle()
	{
		this->angle = atan(this->im / this->re);
	}
	void setRe()
	{
		this->re = this->module * cos(this->angle);
	}
	void setIm()
	{
		this->im = this->module * sin(this->angle);
	}
public:
	ComplexNumber operator+(const ComplexNumber &n)
	{
		ComplexNumber result;

		result.re = this->re + n.re;
		result.im = this->im + n.im;
		result.setModule();
		result.setAngle();

		return result;
	}

	ComplexNumber operator-(const ComplexNumber &n)
	{
		ComplexNumber result;

		result.re = this->re - n.re;
		result.im = this->im - n.im;
		result.setModule();
		result.setAngle();

		return result;
	}

	ComplexNumber operator*(const ComplexNumber &n)
	{
		ComplexNumber result;

		result.module = this->module * n.module;
		result.angle = this->angle + n.angle;
		result.setRe();
		result.setIm();

		return result;
	}

	ComplexNumber operator/(const ComplexNumber &n)
	{
		ComplexNumber result;

		result.module = this->module / n.module;
		result.angle = this->angle - n.angle;
		result.setRe();
		result.setIm();

		return result;
	}
	friend ostream & operator<<(ostream &output, const ComplexNumber &n)
	{
		output << n.module << "/_" << n.angle << " <-> " << n.re << "+" << n.im << "j";
		return output;
	}

	bool set(string input)
	{
		int args = 0;
		float arg1, arg2;

		args = std::sscanf(input.c_str(), "%f/_%f", &arg1, &arg2);
		if (args == 2) {
			this->module = arg1;
			this->angle = arg2;
			this->setRe();
			this->setIm();
			return true;
		}

		args = std::sscanf(input.c_str(), "%f %f", &arg1, &arg2);
		if (args == 2) {
			this->re = arg1;
			this->im = arg2;
			this->setModule();
			this->setAngle();
			return true;
		}

		return false;
	}
};

int main() {
	string input;
	cout << "Welcome to the Complex Number Calculator.\n"
			"You can write numbers in these formats:\n"
			"<mod>/_<ang>\n"
			"<red> <im>\n"
			"Type \"q\" to leave.\n\n\n";

	do {
		static list<ComplexNumber> numbers; // don't use stack because we have to print all elements (i.e. iterate over it)
		uint i;
		ComplexNumber num = ComplexNumber();

		/*
		 * getline() function is used when you have to take input
		 * strings which have spaces in between them.
		*/

		std::getline(std::cin, input);

		i = input.find_first_of("+-*/");

		if (num.set(input)) {
			numbers.push_back(num);
		}
		else if (i != std::string::npos && numbers.size() >= 2) {
			std::list<ComplexNumber>::iterator n1, n2;

			n2 = std::prev(numbers.end());
			n1 = std::prev(n2);

			switch (input[i]) {
			case '+':
				num = *n1 + *n2;
				break;
			case '-':
				num = *n1 - *n2;
				break;
			case '/':
				num = *n1 / *n2;
				break;
			case '*':
				num = *n1 * *n2;
				break;
			}

			numbers.pop_back();
			numbers.pop_back();
			numbers.push_back(num); // @suppress("Invalid arguments")
		}

		cout << "\n\n====== STACK ======\n";
		/* print stack */
		for (std::list<ComplexNumber>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
			cout << *it << "\n";
		}
		cout << "\n\n";

	} while (input != "q");

	return 0;
}
