

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
        //since there is no possible factor between half of the input and the input itself, we don't have to run the loop through about half of the numbers between 1 and n. Really, we could make this more efficient for very large numbers if we set it the loop contraint to i <= sqrt(input) and catch the pairs as they appear, but this would require a vector or a stack which would be less efficient for memory... Depends on how much you want to cut down on iterations
        for (int i = 1; i <= input / 2; i++) {
            if (input % i == 0) {
                std::cout << i << " ";
           }
        }
            //necessary addition since we're doing the half the input trick up above^^
            std::cout << input;
    }
}
