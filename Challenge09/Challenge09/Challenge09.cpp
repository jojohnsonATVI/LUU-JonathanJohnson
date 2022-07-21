

#include <iostream>

void SwapInts(int *ptrA, int *ptrB) {
	int temp = *ptrA;
	*ptrA = *ptrB;
	*ptrB = temp;

}

int main()
{
	int a;
	int b;
	std::cout << "Enter a number\n";
	std::cin >> a;
	//Should make this into a funtion, maybe I will later?
	while (true) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(99, '\n');
			std::cout << "Not a valid response, please eneter a numer.\n";
			std::cin >> a;

		}
		else break;
	}
	std::cout << "Enter a number\n";
	std::cin >> b;
	//Copy of code above
	while (true) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(99, '\n');
			std::cout << "Not a valid response, please eneter a numer.\n";
			std::cin >> b;

		}
		else break;
	}
	for (int i = 0; i < 1000000; i++) {
		SwapInts(&a, &b);
		std::cout << a << ' ' << b << std::endl;
	}
	SwapInts(&a, &b);
	std::cout << a << ' ' << b << std::endl;
	

}
