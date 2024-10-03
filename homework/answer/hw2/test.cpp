#include <iostream>

void triangles(int a, int b, int c);
void triangles(double a, double b, double c);

int main(int argc, char *argv[])
{
    int iteration = 1, size = 3;
    bool isDouble = false;
    int numberStartIndex = 0; // Added variable to determine where numbers start in argv[]

    // Handle command-line arguments
    if (argc == 1)
    {
        isDouble = false;
        numberStartIndex = 0;
    }
    else if (argc == 2)
    {
        if (argv[1][0] == '-' && argv[1][2] == '\0')
        {
            if (argv[1][1] == 'd')
            {
                isDouble = true;
            }
            else if (argv[1][1] == 'i')
            {
                isDouble = false;
            }
            else
            {
                std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
                return 1;
            }
        }
        else
        {
            std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
            return 1;
        }
        numberStartIndex = 0;
    }
    else if (argc == 4)
    {
        if (argv[1][0] == '-' && argv[1][2] == '\0') // Check if first argument is a flag
        {
            if (argv[1][1] == 'd')
            {
                isDouble = true;
            }
            else if (argv[1][1] == 'i')
            {
                isDouble = false;
            }
            else
            {
                std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
                return 1;
            }
            numberStartIndex = 2; // Numbers start from argv[2]
        }
        else
        {
            // No flag provided; assume numbers start from argv[1]
            isDouble = false;
            numberStartIndex = 1;
        }
    }
    else if (argc == 5)
    {
        if (argv[1][0] == '-' && argv[1][2] == '\0')
        {
            if (argv[1][1] == 'd')
            {
                isDouble = true;
            }
            else if (argv[1][1] == 'i')
            {
                isDouble = false;
            }
            else
            {
                std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
                return 1;
            }
            numberStartIndex = 2; // Numbers start from argv[2]
        }
        else
        {
            std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
            return 1;
        }
    }
    else
    {
        std::cerr << "Invalid number of arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
        return 1;
    }

    for (int j = 0; j < iteration; j++)
    {
        if ((argc == 1) || (argc == 2))
        {
            if (isDouble)
            {
                double numbers[size] = {0};
                std::cin >> numbers[0] >> numbers[1] >> numbers[2];

                // Validate input
                if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0)
                {  
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // Sort input
                double placeholder;
                for (int i = 2; i > 0; i--)
                {
                    if (numbers[i] < numbers[i - 1])
                    {
                        placeholder = numbers[i - 1];
                        numbers[i - 1] = numbers[i];
                        numbers[i] = placeholder;
                    }
                }

                triangles(numbers[0], numbers[1], numbers[2]);
            }
            else
            {
                int numbers[size] = {0};
                std::cin >> numbers[0] >> numbers[1] >> numbers[2];

                // Validate input
                if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0)
                {  
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // Sort input
                int placeholder;
                for (int i = 2; i > 0; i--)
                {
                    if (numbers[i] < numbers[i - 1])
                    {
                        placeholder = numbers[i - 1];
                        numbers[i - 1] = numbers[i];
                        numbers[i] = placeholder;
                    }
                }

                triangles(numbers[0], numbers[1], numbers[2]);
            }
        }
        else if ((argc == 4) || (argc == 5))
        {
            if (isDouble)
            {
                double numbers[size] = {0};
                for (int argIndex = numberStartIndex; argIndex < numberStartIndex + 3; argIndex++)
                {
                    bool detectedDecimal = false;
                    double integerPart = 0;
                    double decimalPart = 0;
                    double fractionalDivider = 10;

                    for (int i = 0; argv[argIndex][i] != '\0'; i++)
                    {
                        if (argv[argIndex][i] == '.')
                        {
                            if (detectedDecimal)
                            {
                                std::cerr << "Can only be one decimal!" << std::endl;
                                return 1;
                            }
                            detectedDecimal = true;
                            continue;
                        }

                        if (argv[argIndex][i] >= '0' && argv[argIndex][i] <= '9')
                        {
                            if (!detectedDecimal)
                            {
                                integerPart = integerPart * 10 + (argv[argIndex][i] - '0');
                            }
                            else
                            {
                                decimalPart += (argv[argIndex][i] - '0') / fractionalDivider;
                                fractionalDivider *= 10;
                            }
                        }
                        else
                        {
                            std::cerr << "Please enter ONLY positive numbers." << std::endl;
                            return 1;
                        }
                    }
                    numbers[argIndex - numberStartIndex] = integerPart + decimalPart;
                }

                // Validate input
                if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0)
                {  
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // Sort input
                double placeholder;
                for (int i = 2; i > 0; i--)
                {
                    if (numbers[i] < numbers[i - 1])
                    {
                        placeholder = numbers[i - 1];
                        numbers[i - 1] = numbers[i];
                        numbers[i] = placeholder;
                    }
                }

                triangles(numbers[0], numbers[1], numbers[2]);
            }
            else
            {
                int numbers[size] = {0};
                for (int argIndex = numberStartIndex; argIndex < numberStartIndex + 3; argIndex++)
                {
                    int integerPart = 0;
                    for (int i = 0; argv[argIndex][i] != '\0'; i++)
                    {
                        if (argv[argIndex][i] >= '0' && argv[argIndex][i] <= '9')
                        {
                            integerPart = integerPart * 10 + (argv[argIndex][i] - '0');
                        }
                        else
                        {
                            std::cerr << "Please enter ONLY positive integers." << std::endl;
                            return 1;
                        }
                    }
                    numbers[argIndex - numberStartIndex] = integerPart;
                }

                // Validate input
                if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0)
                {  
                    std::cerr << "Please enter ONLY positive integers." << std::endl;
                    return 1;
                }

                // Sort input
                int placeholder;
                for (int i = 2; i > 0; i--)
                {
                    if (numbers[i] < numbers[i - 1])
                    {
                        placeholder = numbers[i - 1];
                        numbers[i - 1] = numbers[i];
                        numbers[i] = placeholder;
                    }
                }

                triangles(numbers[0], numbers[1], numbers[2]);
            }
        }
        else
        {
            std::cerr << "Please enter ONLY in the following format -d/-i # # # or -d/-i." << std::endl;
            return 1;
        }
    }
}

void triangles(int a, int b, int c)
{
    std::cout << a << " " << b << " " << c << " ";

    if (a + b <= c)
    {
        std::cout << "Not a triangle" << std::endl;
        return;
    }

    bool isRight = (a * a + b * b == c * c);

    if (a == b && b == c)
    {
        std::cout << "Equilateral Triangle" << std::endl;
    }
    else if (a == b || b == c)
    {
        std::cout << (isRight ? "Right " : "") << "Isosceles Triangle" << std::endl;
    }
    else
    {
        std::cout << (isRight ? "Right " : "") << "Scalene Triangle" << std::endl;
    }
}

void triangles(double a, double b, double c)
{
    const double EPSILON = 0.001;

    std::cout << a << " " << b << " " << c << " ";

    if (a + b <= c)
    {
        std::cout << "Not a triangle" << std::endl;
        return;
    }

    double difference = a * a + b * b - c * c;
    if (difference < 0) difference = -difference;
    bool isRight = (difference < EPSILON);

    double AB = a - b;
    double BC = b - c;
    double AC = a - c;
    if (AB < 0)
        AB = -AB;
    if (BC < 0)
        BC = -BC;
    if (AC < 0)
        AC = -AC;
    bool isEqualAB = (AB < EPSILON);
    bool isEqualBC = (BC < EPSILON);
    bool isEqualAC = (AC < EPSILON);

    if (isEqualAB && isEqualBC && isEqualAC)
    {
        std::cout << "Equilateral Triangle" << std::endl;
    }
    else if (isEqualAB || isEqualBC)
    {
        std::cout << (isRight ? "Right " : "") << "Isosceles Triangle" << std::endl;
    }
    else
    {
        std::cout << (isRight ? "Right " : "") << "Scalene Triangle" << std::endl;
    }
}
