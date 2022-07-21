

#include <iostream>
#include <stack>
#include <time.h>

int getGoodInt() {
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
        else return input;
    }
}
void PrintFactors(int input) {
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
    std::cout << '\n';
}
void PrintFactorsHalf(int input) {
    std::cout << input << " Has the following factors: ";
    int half = input / 2;
    for (int i = 1; i <= half; i++) {
        if (input % i == 0) {
            std::cout << i << ' ';
        }
    }
    std::cout << input << '\n';
}
void PrintFactorsFull(int input) {
    std::cout << input << " Has the following factors: ";
    for (int i = 1; i <= input; i++) {
        if (input % i == 0) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';
}




int main()
{
   /*
    *clock_t tStart = clock();
    *for (int i = 1999999900; i < 2000000000; i++) {
    *    PrintFactors(i);
    *}
    *
    *clock_t tStart2 = clock();
    *for (int i = 1999999900; i < 2000000000; i++) {
    *    PrintFactorsHalf(i);
    *}
    *
    *clock_t tStart3 = clock();
    *for (int i = 1999999900; i < 2000000000; i++) {
    *    PrintFactorsFull(i);
    *}
    *printf("Time taken for Sqrt route: %.2fs\n", (double)(tStart2 - tStart) / CLOCKS_PER_SEC);
    *printf("Time taken for half route: %.2fs\n", (double)(tStart3 - tStart2) / CLOCKS_PER_SEC);
    *printf("Time taken for full route: %.2fs\n", (double)(clock() - tStart3) / CLOCKS_PER_SEC);
    *
    *return 0;
    * 
    * 
    * Results:
    * 
    * Time taken for Sqrt route: 1.56s
    * Time taken for half route: 134.25s
    * Time taken for full route: 275.81s
    */

    PrintFactors(getGoodInt());

   

}