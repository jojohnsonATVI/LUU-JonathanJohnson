#include<iostream>

using namespace std;

int main() {
	double num1;
	double num2;
	double num3;
	cout << "Give the first number\n";
	cin >> num1;
	cout << "Give the second number\n";
	cin >> num2;
	cout << "Give the third number\n";
	cin >> num3;
	cout << "The sum of " << num1 << ", " << num2 << ", and " << num3 << " is " << num1 + num2 + num3 <<"\n";
	cout << "The Average of " << num1 << ", " << num2 << ", and " << num3 << " is " << (num1 + num2 + num3) / 3;
	return 0;
}