#include <iostream>

void triangles(int a, int b, int c);
void triangles(double a, double b, double c);

int main(int argc, char *argv[])
{
    int iteration = 44, size = 3;
    bool isDouble = false;
    int startIndex;

    if (argc == 1)
        isDouble = false;
    else if (argc == 2)
    {
        if (argv[1][0] == '-' && argv[1][1] == 'd' && argv[1][2] == '\0')
            isDouble = true;
        else if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[1][2] == '\0')
        {
            isDouble = false;
        }
        else
        {
            std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
            return 1;
        }
    }
    else if (argc == 4)
    {
        if ((argv[1][0] == '-' && (argv[1][1] == 'd' || argv[1][1] == 'i') && argv[1][2] == '\0'))
        {
            std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
            return 1;
        }
        startIndex = 1;
        isDouble = false;
    }
    else if (argc == 5)
    {
        if (argv[1][0] == '-' && argv[1][1] == 'd' && argv[1][2] == '\0')
        {
            isDouble = true;
            startIndex = 2;
        }
        else if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[1][2] == '\0')
        {
            isDouble = false;
            startIndex = 2;
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

                // validate input
                if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0)
                {
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // sort input
                double placeholder;
                for (int i = 2; i > 0; i--)
                {
                    if (numbers[i] < numbers[i - 1])
                    {
                        placeholder = numbers[i - 1];
                        numbers[i - 1] = numbers[i];
                        numbers[i] = placeholder;
                    }
                    if (numbers[2] < numbers[1])
                    {
                        placeholder = numbers[1];
                        numbers[1] = numbers[2];
                        numbers[2] = placeholder;
                    }
                }

                triangles(numbers[0], numbers[1], numbers[2]);
            }
            else
            {
                double numbers[size] = {0};
                std::cin >> numbers[0] >> numbers[1] >> numbers[2];

                // validate input
                if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0)
                {
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // sort input
                double placeholder;
                for (int i = 2; i > 0; i--)
                {
                    if (numbers[i] < numbers[i - 1])
                    {
                        placeholder = numbers[i - 1];
                        numbers[i - 1] = numbers[i];
                        numbers[i] = placeholder;
                    }
                    if (numbers[2] < numbers[1])
                    {
                        placeholder = numbers[1];
                        numbers[1] = numbers[2];
                        numbers[2] = placeholder;
                    }
                }

                triangles((int)numbers[0], (int)numbers[1], (int)numbers[2]);
            }
        }
        else if ((argc == 4) || (argc == 5))
        {
            if (isDouble)
            {
                double numbers[size] = {0};
                for (int argIndex = startIndex; argIndex < 3 + startIndex; argIndex++)
                {
                    bool detectedDecimal = false;
                    double integerPart = 0;
                    double decimalPart = 0;
                    double fractionalDivider = 10;

                    for (int i = 0; argv[argIndex][i] != '\0'; i++)
                    {
                        if (argv[argIndex][i] == '.')
                        {
                            if (detectedDecimal) // if we want it to automatically filter out extra decimals, then we just remove this error function
                            {
                                std::cerr << "Can only be one decimal!" << std::endl;
                                return 1;
                            }
                            detectedDecimal = true;
                            continue;
                        }

                        if (argv[argIndex][i] >= '0' && argv[argIndex][i] <= '9')
                        {
                            if (!detectedDecimal) // before decimal is found, since detectedDecimal is false by default
                            {
                                integerPart = integerPart * 10 + (argv[argIndex][i] - '0');
                            }
                            else
                            {
                                decimalPart += (argv[argIndex][i] - '0') / fractionalDivider;
                                fractionalDivider *= 10; // increasing it so that we cover smaller decimals
                            }
                        }
                        else
                        {
                            std::cerr << "Please enter ONLY positive numbers." << std::endl;
                            return 1;
                        }
                    }
                    numbers[argIndex - startIndex] = integerPart + decimalPart;
                }

                // validate input
                if (numbers[0] <= 0 || numbers[1] <= 0 || numbers[2] <= 0)
                {
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // sort input
                double placeholder;
                for (int i = 2; i > 0; i--)
                {
                    if (numbers[i] < numbers[i - 1])
                    {
                        placeholder = numbers[i - 1];
                        numbers[i - 1] = numbers[i];
                        numbers[i] = placeholder;
                    }
                    if (numbers[2] < numbers[1])
                    {
                        placeholder = numbers[1];
                        numbers[1] = numbers[2];
                        numbers[2] = placeholder;
                    }
                }

                triangles(numbers[0], numbers[1], numbers[2]);
            }
            else
            {
                int numbers[size] = {0};
                for (int argIndex = startIndex; argIndex < 3 + startIndex; argIndex++)
                {
                    bool detectedDecimal = false;
                    int integerPart = 0;
                    double decimalPart = 0;
                    double fractionalDivider = 10;

                    for (int i = 0; argv[argIndex][i] != '\0'; i++)
                    {
                        if (argv[argIndex][i] == '.')
                        {
                            if (detectedDecimal) // if we want it to automatically filter out extra decimals, then we just remove this error function
                            {
                                std::cerr << "Can only be one decimal!" << std::endl;
                                return 1;
                            }
                            detectedDecimal = true;
                            continue;
                        }

                        if (argv[argIndex][i] >= '0' && argv[argIndex][i] <= '9')
                        {
                            if (!detectedDecimal) // before decimal is found, since detectedDecimal is false by default
                            {
                                integerPart = integerPart * 10 + (argv[argIndex][i] - '0');
                            }
                            else
                            {
                                decimalPart += (argv[argIndex][i] - '0') / fractionalDivider;
                                fractionalDivider *= 10; // increasing it so that we cover smaller decimals
                            }
                        }
                        else
                        {
                            std::cerr << "Please enter ONLY positive numbers." << std::endl;
                            return 1;
                        }
                    }
                    numbers[argIndex - startIndex] = integerPart;
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

    for (int i = 0; i < 3; i++)
    {
        // prints the whole number part of the decimal
        double num = (i == 0) ? a : (i == 1) ? b
                                             : c; // if i==0, num = a, if i==1, num  = b, if i==2, num = c
        int integerPart = (int)num;
        double decimalPart = num - integerPart;
        int fraction = (int)(decimalPart * 100000 + 0.5); // adds 0.5 for rounding. Ex: if 0.123456 * 100000, then we have 12345.6 + 0.5 = 12346.1, which rounds down to 12346 when casted to an int

        std::cout << integerPart << ".";

        int fractionalDivider = 10000;
        while (fractionalDivider > 0)
        {
            int digit = fraction / fractionalDivider; // ex: 12345 / 10000 -> 1
            std::cout << digit;                       // prints a digit at a time
            fraction %= fractionalDivider;            // ex: 12345 % 10000 -> 2345
            fractionalDivider /= 10;
        }
        std::cout << " ";
    }

    if (a + b <= c)
    {
        std::cout << "Not a triangle" << std::endl;
        return;
    }

    double difference = a * a + b * b - c * c;
    if (difference < 0)
        difference = -difference;
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