

#include <iostream>
#include <stack>


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
    std::cout << input << " Has the following factors: ";
    std::stack<int> stack;
    int sqrt = std::sqrt(input);
    for (int i = 1; i < sqrt; i++) {
        if (input % i == 0) {
            stack.push(input / i);
            std::cout << i << ' ';
        }
    }
    if (sqrt * sqrt == input) {
        std::cout << sqrt << ' ';
    }
    while (!stack.empty()) {
        std::cout << stack.top() << ' ';
        stack.pop();
    }

}