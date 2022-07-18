

#include <iostream>

int main()
{
    std::cout << "Enter a positive number\n";
    int input;
    std::cin >> input;
    if (input <= 0) {
        std::cout << "A non positive number was entered";
        return 0;
    }
    else {
        std::cout << input << " Has the following products: ";
        //since there is no possible factor between half of the input and the input itself. Really, we could make this more efficient for very large numbers if we set it to input/n and set n to 2, and change it to 3 if we get past 2 in our count, and set n to 4 if we pass 3 in our loop without 
        for (int i = 1; i <= input / 2; i++) {
            if (input % i == 0) {
                std::cout << i << " ";
           }
        }
            //necessary addition since we're doing the half the input trick up above^^
            std::cout << input;
    }
}
