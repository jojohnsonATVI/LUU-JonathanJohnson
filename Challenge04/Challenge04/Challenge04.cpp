

#include <iostream>



int main()
{
    
    std::cout << "Enter a positive number\n";
    int input;
    std::cin >> input;
    while (true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(99, '\n');
            std::cout << "A number wasn't entered. Please enter a positive number\n";
            std::cin >> input;
        }
        else if (input < 1) {
            std::cout << "A non positive number was entered. Please enter a positive number\n";
            std::cin >> input;
        }
        else break;
        
       

    }
    std::cout << input << " Has the following products: ";
    /* Since there is no possible factor between half of inputand input, we can skip the last half of checks. 
    *  This could be sped up even more if we were to run the loop from 1 to sqrt of input and add the corresponding factor 
    *  greater than the sqrt(n) to a stack and pop them out after finishing the loop. Of course we'd have to add a check for
    *  if the sqrt(input) is one of the factors before popping the stack so we don't end up missing or duplicatibg the sqrt result.
    *  I'm choosing not to implement this since it's unclear what the program's goals are for memory/speed O(n).
    */

        for (int i = 1; i <= input / 2; i++) {
        if (input % i == 0) {
            std::cout << i << " ";
        }
    }
    //necessary addition since we're doing the half the input trick up above^^
    std::cout << input;
}