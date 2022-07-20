#include<iostream>

int BiggestInArray(int intArray[], int length) {
    int biggest = intArray[0];
    for (int i = 1; i < length; i++) {
        if (intArray[i] > biggest) {
            biggest = intArray[i];
        }
    }
    return biggest;
}

int main()
{
    int myArray[] = { -64, 40, 12658, 12657, 12659, -13000, 4, 84 };
    std::cout << BiggestInArray(myArray, 8);
}

