#include <iostream>

int main()
{
    int year;
    std::cout << "What is the current year?\n";
    std::cin >> year;
    if (year % 4 == 0)
        if (year % 400 == 0) {
            std::cout << year << " is a leap year.\n";
        }
        else 
            if (year % 100 == 0) {
                std::cout << year << " is not a leap year.\n";
            }
            else std::cout << year << " is a leap year.\n";
    else std::cout << year << " is not a leap year.\n";
    return 0;
}

