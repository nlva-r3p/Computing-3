#include <iostream>

bool readInputs(int numbers[], int size);
bool readInputs(double numbers[], int size);
bool validateInputs(int numbers[], int size);
bool validateInputs(double numbers[], int size);
void sortInputs(int numbers[], int size);
void sortInputs(double numbers[], int size);
bool convertStringToInt(const char *arg, int &number);
bool convertStringToDouble(const char *arg, double &number);
void printInputsWithPrecision(double numbers[], int precision);

const char* triangles(int a, int b, int c); // ensure that we return it as a constant char pointer since it is read-only. Otherwise, there will be problems if the string is attempted to access
const char* triangles(double a, double b, double c);

int main(int argc, char *argv[])
{
    int iteration = 1; // for debugging sake, iteration is changed to higher values.
    const int size = 3;
    bool isDouble = false;
    int startIndex;

    if (argc == 1)
        isDouble = false;
    else if (argc == 2)
    {
        if (argv[1][0] == '-' && argv[1][1] == 'd' && argv[1][2] == '\0')
            isDouble = true;
        else if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[1][2] == '\0')
            isDouble = false;
        else
        {
            std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
            return 1;
        }
    }
    else if (argc == 4)
    {
        isDouble = false;
        startIndex = 1;
    }
    else if (argc == 5)
    {
        if (argv[1][0] == '-' && argv[1][2] == '\0')
        {
            if (argv[1][1] == 'd')
                isDouble = true;
            else if (argv[1][1] == 'i')
                isDouble = false;
            else
            {
                std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
                return 1;
            }
            startIndex = 2;
        }
    }
    else
    {
        std::cerr << "Invalid arguments. Please use the format -d/-i # # # or -d/-i or none." << std::endl;
        return 1;
    }

    for (int j = 0; j < iteration; j++)
    {
        if ((argc == 1) || (argc == 2))
        {
            if (isDouble)
            {
                double numbers[size] = {0};
                if (!readInputs(numbers, size))
                {
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // validate input
                if (!validateInputs(numbers, size))
                {
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // sort input
                sortInputs(numbers, size);
                printInputsWithPrecision(numbers, 5);
                std::cout << triangles(numbers[0], numbers[1], numbers[2]) << std::endl;
            }
            else
            {
                int numbers[size] = {0};
                if (!readInputs(numbers, size))
                {
                    std::cerr << "Please enter ONLY positive integers." << std::endl;
                    return 1;
                }

                // validate input
                if (!validateInputs(numbers, size))
                {
                    std::cerr << "Please enter ONLY positive integers." << std::endl;
                    return 1;
                }

                // sort input
                sortInputs(numbers, size);
                std::cout << triangles(numbers[0], numbers[1], numbers[2]) << std::endl;
            }
        }
        else if ((argc == 4) || (argc == 5))
        {
            if (isDouble)
            {
                double numbers[size] = {0};
                for (int i = 0; i < size; ++i)
                {
                    if (!convertStringToDouble(argv[startIndex + i], numbers[i])) // we are passing by reference for numbers. Also, argv[startIndex + i] is a character pointer to a string, so we just pass it as a pointer
                    {
                        std::cerr << "Please enter ONLY positive numbers." << std::endl;
                        return 1;
                    }
                }

                // validate input
                if (!validateInputs(numbers, size))
                {
                    std::cerr << "Please enter ONLY positive numbers." << std::endl;
                    return 1;
                }

                // sort input
                sortInputs(numbers, size);
                printInputsWithPrecision(numbers, 5);
                std::cout << triangles(numbers[0], numbers[1], numbers[2]) << std::endl;
            }
            else
            {
                int numbers[size] = {0};
                for (int i = 0; i < size; ++i)
                {
                    if (!convertStringToInt(argv[startIndex + i], numbers[i])) // we are passing by reference for numbers. Also, argv[startIndex + i] is a character pointer to a string, so we just pass it as a pointer
                    {
                        std::cerr << "Please enter ONLY positive integers." << std::endl;
                        return 1;
                    }
                }

                // validate input
                if (!validateInputs(numbers, size))
                {
                    std::cerr << "Please enter ONLY positive integers." << std::endl;
                    return 1;
                }

                // sort input
                sortInputs(numbers, size);
                std::cout << triangles(numbers[0], numbers[1], numbers[2]) << std::endl;
            }
        }
        else
        {
            std::cerr << "Please enter ONLY in the following format -d/-i # # # or -d/-i or none." << std::endl;
            return 1;
        }
    }
}

const char* triangles(int a, int b, int c)
{
    std::cout << a << " " << b << " " << c << " ";

    if (a + b <= c)
        return "Not a Triangle";

    bool isRight = (a * a + b * b == c * c);

    if (a == b && b == c)
        return "Equilateral Triangle";
    else if (a == b || b == c)
    {
        if (isRight)
            return "Right Isosceles Triangle";
        else
            return "Isosceles Triangle";
    }
    else
    {
        if (isRight)
            return "Right Scalene Triangle";
        else
            return "Scalene Triangle";
    }
}

const char* triangles(double a, double b, double c)
{
    const double EPSILON = 0.001;

    if (a + b <= c)
        return "Not a Triangle";

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
        return "Equilateral Triangle";
    else if (isEqualAB || isEqualBC)
    {
        if (isRight)
            return "Right Isosceles Triangle";
        else
            return "Isosceles Triangle";
    }
    else
    {
        if (isRight)
            return "Right Scalene Triangle";
        else
            return "Scalene Triangle";
    }
}

bool readInputs(int numbers[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cin >> numbers[i];
        if (std::cin.fail())
            return false;
    }
    return true;
}

bool readInputs(double numbers[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cin >> numbers[i];
        if (std::cin.fail())
            return false;
    }
    return true;
}

bool validateInputs(int numbers[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (numbers[i] <= 0)
            return false;
    }
    return true;
}

bool validateInputs(double numbers[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (numbers[i] <= 0)
            return false;
    }
    return true;
}

void sortInputs(int numbers[], int size)
{
    int temp;
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (numbers[j] > numbers[j + 1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

void sortInputs(double numbers[], int size)
{
    int temp;
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (numbers[j] > numbers[j + 1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

bool convertStringToDouble(const char *arg, double &number)
{
    bool detectedDecimal = false;
    double integerPart = 0;
    double decimalPart = 0;
    double fractionalDivider = 10;

    for (int i = 0; arg[i] != '\0'; ++i)
    {
        if (arg[i] == '.')
        {
            if (detectedDecimal) // if we want to automatically convert typos of multiple decimals then we remove this.
                return false;
            detectedDecimal = true;
            continue;
        }

        if (arg[i] >= '0' && arg[i] <= '9')
        {
            if (!detectedDecimal) // executes if haven't detected a decimal
                integerPart = integerPart * 10 + (arg[i] - '0');
            else
            {
                decimalPart += (arg[i] - '0') / fractionalDivider;
                fractionalDivider *= 10; // tenths -> hundredths -> etc.
            }
        }

        else
            return false; // if characters NOT between '0' and '9' are detected
    }
    number = integerPart + decimalPart; // we are passing by reference
    return true;
}

bool convertStringToInt(const char *arg, int &number)
{
    int integerPart = 0;

    for (int i = 0; arg[i] != '\0'; ++i)
    {
        if (arg[i] >= '0' && arg[i] <= '9')
            integerPart = integerPart * 10 + (arg[i] - '0');
        else
            return false; // if characters NOT between '0' and '9' are detected
    }
    number = integerPart; // we are passing by reference
    return true;
}

void printInputsWithPrecision(double numbers[], int precision)
{
    int fractionalMultiplier = 1;
    for (int i = 0; i < precision; ++i)
        fractionalMultiplier *= 10;

    for (int i = 0; i < 3; i++)
    {
        // prints the whole number part of the decimal
        double num = numbers[i];
        int integerPart = (int)num;
        double decimalPart = num - integerPart;
        int fraction = (int)(decimalPart * fractionalMultiplier + 0.5); // adds 0.5 for rounding. Ex: if 0.123456 * 100000, then we have 12345.6 + 0.5 = 12346.1, which rounds down to 12346 when casted to an int

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
}