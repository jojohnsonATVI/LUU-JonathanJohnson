#include <iostream>

double CubeANumber(double number) {
    return pow(number, 3);

}

int main()
{
    double input;
    std::cout << "Enter a number to get cubed.\n";
    std::cin >> input;
    std::cout << "The cube of " << input << " is " << CubeANumber(input);
    return 0;
}