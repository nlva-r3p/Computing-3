#include <iostream>

void triangles (int a, int b, int c);

int main (int argc, char *argv[]) {
    int placeholder, iteration = 5, size = 3;

for (int j = 0; j < iteration; j++) {
    int numbers[size] = {0};
    if (argc == 1) {
        std::cin >> numbers[0] >> numbers[1] >> numbers[2];
        //Validate input
        if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0) {
            std::cerr << "Please enter ONLY positive integers." << std::endl;
            return 1;
        }
    }
    else if (argc == 4) {
        for (int i = 0; argv[1][i] != '\0'; i++) {
            numbers[0] = numbers[0] * 10 + (argv[1][i] - '0');
        }
        for (int i = 0; argv[2][i] != '\0'; i++) {
            numbers[1] = numbers[1] * 10 + (argv[2][i] - '0');
        }
        for (int i = 0; argv[2][i] != '\0'; i++) {
            numbers[2] = numbers[2] * 10 + (argv[2][i] - '0');
        }
        
        //Validate input
        if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0) {
            std::cerr << "Please enter ONLY positive integers." << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "Please enter ONLY positive integers." << std::endl;
        return 1;
    }

    //Sort input
    for (int i = 3; i > 0; i--) {
        if (numbers[i] < numbers[i - 1]) {
            placeholder = numbers[i - 1];
            numbers [i - 1] = numbers[i];
            numbers[i] = placeholder;
        }
    }

    triangles(numbers[0], numbers[1], numbers[2]);
}
}

void triangles (int a, int b, int c) {
    std::cout << a << " " << b << " " << c << " ";

    if (a + b <= c) {
        std::cout << "Not a triangle" << std::endl;
        return;
    }
    
    bool isRight = (a * a + b * b == c * c);

    if (a == b && b == c) {
        std::cout << "Equilateral Triangle" << std::endl;
    }
    else if (a == b || b == c) {
        std::cout << (isRight ? "Right " : "") << "Isosceles Triangle" << std::endl;
    }
    else {
        std::cout << (isRight ? "Right " : "") << "Scalene Triangle" << std::endl;
    }
}