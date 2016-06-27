/*This is a reddit daily programmer challenge:
Given the following constraints of the ISBN number, you should write a function that can return True 
if a number is a valid ISBN and False otherwise. An ISBN is a ten digit code which identifies a book. 
The first nine digits represent the book and the last digit is used to make sure the ISBN is correct.
To verify an ISBN you obtain the sum of 10 times the first digit, 9 times the second digit, 8 times the third digit... 
all the way till you add 1 times the last digit. 
If the sum leaves no remainder when divided by 11 the code is a valid ISBN.

Rather than just verify ISBN's, I put a twist on the challenge and made a program to generate ISBN numbers.
*/

#include <iostream>
#include <random>
#include <time.h>

struct ISBN { //This really wasn't needed, however for my own practice I decided make the ISBN itself a class.
private:
	int number[10];
	bool valid = false;
public:
	void calculate(ISBN& isbn);
	void setValid() { valid = true; }
	void addNumber(int n, int pos) { number[pos] = n; }
	void updateFinal(int n) { number[9] += n; }
	void assembleISBN(ISBN& isbn);
	void print(ISBN& isbn);
};

void ISBN::calculate(ISBN& isbn) { //based on the challenge criteria, this method determines if the isbn is valid.
								   //the last digit is updated based on what the remainder is so it becomes a valid isbn.
	int pos = 10;
	int total = 0;
	int remainder = 0;

	for (auto i : isbn.number) {
		total += (pos * i);
		pos--;
	}
	if (total % 11 == 0) {
		isbn.setValid();
	}
	else {
		remainder = total % 11;
		isbn.updateFinal(remainder);
		isbn.setValid();
	}
}

void ISBN::print(ISBN& isbn) {
	int count = 0;
	for (auto i : isbn.number) { /*simple method to print the isbn number formatted correctly. If the last digit is
								 10, append a 'X' per the instructions.*/
		if (i >= 10) {
			std::cout << 'X';
		}
		else {
			std::cout << i;
		}
		if (count == 0 || count == 4 || count == 8) {
			std::cout << '-';
		}
		count++;
	}
	std::cout << std::endl;
}

void ISBN::assembleISBN(ISBN& isbn) { //obtains the needed digits randomly and than calculates whether it is valid.
	srand(time(NULL));
	int num;
	int pos = 0;

	while (pos < 10) {
		num = rand() % 10;
		isbn.addNumber(num, pos);
		pos++;
	}

	while (!isbn.valid) {
		isbn.calculate(isbn);
	}

	isbn.print(isbn);
}

int main() {

	ISBN newISBN;
	newISBN.assembleISBN(newISBN);

	return 0;
}