#include <iostream>
#include <vector>
#include <limits> // need to to use max

template <typename T>
class MyComplex {
public:
    // Constructors
    MyComplex() : real(T(0)), imaginary(T(0)) {}
    MyComplex(T r) : real(r), imaginary(T(0)) {}
    MyComplex(T r, T i) : real(r), imaginary(i) {}

    // Mutators
    void setReal(T r);
    void setImaginary(T i);
    void setNumbers(T r, T i);
    void conjugateNumbers();

    // Accessors
    T getReal() const;
    T getImaginary() const;
    void outputNumbers() const;

    // Operator overloads
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const MyComplex<U>& number);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, MyComplex<U>& number);

    // Assignment 6
    template <typename U>
    friend MyComplex<U> operator+(const U& num, const MyComplex<U>& cnum);

    template <typename U>
    friend MyComplex<U> operator-(const U& num, const MyComplex<U>& cnum);

    template <typename U>
    friend MyComplex<U> operator*(const U& num, const MyComplex<U>& cnum);

    template <typename U>
    friend MyComplex<U> operator/(const U& num, const MyComplex<U>& cnum);

    MyComplex operator+(const T& other) const;
    MyComplex operator+(const MyComplex& other) const;
    MyComplex operator-(const T& other) const;
    MyComplex operator-(const MyComplex& other) const;
    MyComplex operator*(const T& other) const;
    MyComplex operator*(const MyComplex& other) const;
    MyComplex operator/(const T& other) const;
    MyComplex operator/(const MyComplex& other) const;
    MyComplex operator!() const;

private:
    T real;
    T imaginary;
};

// Mutator definitions
template<typename T>
void MyComplex<T>::setReal(T r) {
    real = r;
}

template<typename T>
void MyComplex<T>::setImaginary(T i) {
    imaginary = i;
}

template<typename T>
void MyComplex<T>::setNumbers(T r, T i) {
    real = r;
    imaginary = i;
}

template<typename T>
void MyComplex<T>::conjugateNumbers() {
    imaginary *= T(-1);
}

// Accessor definitions
template<typename T>
T MyComplex<T>::getReal() const {
    return real;
}

template<typename T>
T MyComplex<T>::getImaginary() const {
    return imaginary;
}

template<typename T>
void MyComplex<T>::outputNumbers() const {
    std::cout << "Re == " << real << ", Im == " << imaginary << std::endl;
}

// Operator overload definitions

// For operator<< we have to consider:
// a) both real and imaginary is 0
// b) either one, but not both is a zero (2 cases)
// c) both not zero
// d) if imaginary is negative, then + won't be printed
// c and d is implemented in hw4

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyComplex<T>& number) {
    if (number.real == T(0) && number.imaginary == T(0)) {
        os << number.real; // since both is zero, we can just output whichever
        // os << number.imaginary;
        // os << '0';
    } else if (number.real == T(0)) {
        os << number.imaginary << 'i';
    } else if (number.imaginary == T(0)) {
        os << number.real;
    } else {
        os << number.real;
        if (number.imaginary >= T(0))
            os << '+';
        os << number.imaginary << 'i';
    }
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, MyComplex<T>& number) {
    number.real = T(0);
    number.imaginary = T(0);

    T r;
    is >> r;

    // is nextChar whitespac or 'i'
    char nextChar = is.peek();
    while (nextChar == ' ') {
        is.get();
        nextChar = is.peek();
    }

    // is the only input the imaginary part
    if (nextChar == 'i') {
        number.imaginary = r;
        is.get(); // omit 'i'
        return is;
    } else {
        number.real = r; // proceed as normal
    }

    is >> nextChar;
    if (nextChar == '+' || nextChar == '-') {
        T i;
        is >> i;

        char i_placeholder = is.peek();
        while (i_placeholder == ' ') {
            is.get();
            i_placeholder = is.peek();
        }

        if (i_placeholder == 'i') {
            is.get(); // omit 'i'
            number.imaginary = (nextChar == '+') ? i : -i;
        } else {
            number.real += (nextChar == '+') ? i : -i;
        }
    } else {
        is.unget();
    }

    return is;
}

template<typename T>
MyComplex<T> MyComplex<T>::operator+(const T& other) const {
    return MyComplex<T>(real + other, imaginary);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator+(const MyComplex<T>& other) const {
    return MyComplex<T>(real + other.real, imaginary + other.imaginary);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator-(const T& other) const {
    return MyComplex<T>(real - other, imaginary);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator-(const MyComplex<T>& other) const {
    return MyComplex<T>(real - other.real, imaginary - other.imaginary);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator*(const T& other) const {
    return MyComplex<T>(real * other, imaginary * other);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator*(const MyComplex<T>& other) const {
    T newReal = real * other.real - imaginary * other.imaginary;
    T newImaginary = real * other.imaginary + imaginary * other.real;
    return MyComplex<T>(newReal, newImaginary);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator/(const T& other) const {
    if (other == T(0))
        std::cerr << "Error! Division by 0!" << std::endl;
    
    T newReal = real / other;
    T newImaginary = imaginary / other;
    return MyComplex<T>(newReal, newImaginary);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator/(const MyComplex<T>& other) const {
    T denominator = other.real * other.real + other.imaginary * other.imaginary;

    if (denominator == T(0))
        std::cerr << "Error! Division by 0!" << std::endl;

    T newReal = (real * other.real + imaginary * other.imaginary) / denominator;
    T newImaginary = (imaginary * other.real - real * other.imaginary) / denominator;
    return MyComplex<T>(newReal, newImaginary);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator!() const {
    return MyComplex<T>(real, -imaginary);
}

template<typename T>
MyComplex<T> operator+(const T& num, const MyComplex<T>& cnum) {
    return MyComplex<T>(num + cnum.real, cnum.imaginary);
}

template<typename T>
MyComplex<T> operator-(const T& num, const MyComplex<T>& cnum) {
    return MyComplex<T>(num - cnum.real, -cnum.imaginary);
}

template<typename T>
MyComplex<T> operator*(const T& num, const MyComplex<T>& cnum) {
    return MyComplex<T>(num * cnum.real, num * cnum.imaginary);
}

template<typename T>
MyComplex<T> operator/(const T& num, const MyComplex<T>& cnum) {
    T denominator = cnum.real * cnum.real + cnum.imaginary * cnum.imaginary;

    if (denominator == T(0))
        std::cerr << "Error! Division by 0!" << std::endl;

    T newReal = num * cnum.real / denominator;
    T newImaginary = -num * cnum.imaginary / denominator;

    return MyComplex<T>(newReal, newImaginary);
}

// main function
int main() {
    MyComplex<double> c1; // default constructor
    MyComplex<double> c2(9.1, 8.2); // 2-value constructor
    MyComplex<double> c3(7.3, 6.4); // 2-value constructor
    MyComplex<double> c4(5.5); // 1-value constructor

    std::cout << "Value of c1 (default constructor):" << std::endl;
    std::cout << "c1.getReal() == " << c1.getReal() << ", c1.getImaginary() == " << c1.getImaginary() << std::endl;

    std::cout << std::endl;
    std::cout << "Value of c2 (2-value constructor):" << std::endl;
    std::cout << "c2.getReal() == " << c2.getReal() << ", c2.getImaginary() == " << c2.getImaginary() << std::endl;

    std::cout << std::endl;
    std::cout << "Value of c3 (2-value constructor):" << std::endl;
    std::cout << "c3.getReal() == " << c3.getReal() << ", c3.getImaginary() == " << c3.getImaginary() << std::endl;

    std::cout << std::endl;
    std::cout << "Value of c4 (1-value constructor):" << std::endl;
    std::cout << "c4.getReal() == " << c4.getReal() << ", c4.getImaginary() == " << c4.getImaginary() << std::endl;

    std::cout << std::endl;
    // arithmetic operations
    std::cout << "c2 + c3 (" << c2 << " + " << c3 << ") == " << (c2 + c3) << std::endl;
    std::cout << "c2 - c3 (" << c2 << " - " << c3 << ") == " << (c2 - c3) << std::endl;
    std::cout << "c2 * c3 (" << c2 << " * " << c3 << ") == " << (c2 * c3) << std::endl;
    std::cout << "c2 / c3 (" << c2 << " / " << c3 << ") == " << (c2 / c3) << std::endl;

    std::cout << std::endl;
    // conjugation using operator!
    std::cout << "Conjugate of c2 (" << c2 << ") == " << !c2 << std::endl;

    // conjugation using conjugateNumbers() member function
    std::cout << "Conjugate of c2 using conjugateNumbers() member function:" << std::endl;
    c2.conjugateNumbers();
    std::cout << "c2 after conjugateNumbers(): " << c2 << std::endl;

    // reset c2 by conjugating it again to negate previous conjugation
    c2.conjugateNumbers();

    std::cout << std::endl;
    // declare vector
    std::vector<MyComplex<double>> complexVector;

    // declare iterator of vector<MyComplex<double>> datatype
    std::vector<MyComplex<double>>::iterator iter;

    for (int i = 0; i < 10; ++i) {
        complexVector.push_back(MyComplex<double>(i, 2 * i));
    }

    std::cout << "Vector output using indexed for-loop:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << complexVector[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Vector output using range-based for-loop:" << std::endl;
    for (const MyComplex<double>& complexNumber : complexVector) {
        std::cout << complexNumber << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Vector output using iterator for-loop:" << std::endl;
    for (iter = complexVector.begin(); iter != complexVector.end(); ++iter) {
        std::cout << *iter << std::endl;
    }

    // testing mutator functions
    MyComplex<double> m1;
    std::cout << "Initial m1: " << m1 << std::endl;
    m1.setReal(5.1);
    std::cout << "After m1.setReal(5): " << m1 << std::endl;

    m1.setImaginary(3.2);
    std::cout << "After m1.setImaginary(3): " << m1 << std::endl;

    m1.setNumbers(10.3, -4.4);
    std::cout << "After m1.setNumbers(10, -4): " << m1 << std::endl;

    m1.conjugateNumbers();
    std::cout << "After m1.conjugateNumbers(): " << m1 << std::endl;

    // testing istream operator
    std::cout << "\nTesting istream operator:" << std::endl;
    MyComplex<double> c5;
    std::cout << "Enter a complex number in the form a+bi (e.g., 3+4i): ";
    std::cin >> c5;
    if (!std::cin.fail()) {
        std::cout << "You entered: " << c5 << std::endl;
    } else {
        std::cout << "Invalid input." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // testing conjugateNumbers() member function
    std::cout << "\nTesting conjugateNumbers() member function:" << std::endl;
    std::cout << "Original c5: " << c5 << std::endl;
    c5.conjugateNumbers();
    std::cout << "Conjugated c5: " << c5 << std::endl;

    // testing operator<< with zero parts
    std::cout << "\nTesting operator<< with zero parts:" << std::endl;
    MyComplex<double> zeroNumber(0, 0);
    MyComplex<double> realOnlyNumber(-2.1, 0);
    MyComplex<double> imagOnlyNumber1(0, 3.2);
    MyComplex<double> imagOnlyNumber2(0, -4.3);

    std::cout << "zeroNumber (0+0i): " << zeroNumber << std::endl;
    std::cout << "realOnlyNumber (-2+0i): " << realOnlyNumber << std::endl;
    std::cout << "imagOnlyNumber1 (0+3i): " << imagOnlyNumber1 << std::endl;
    std::cout << "imagOnlyNumber2 (0-4i): " << imagOnlyNumber2 << std::endl;

    // testing HW 6 functions
    std::cout << "\n// Testing HW 6 functions\n" << std::endl;

    MyComplex<double> c6(3.1, 4.2);
    double scalar = 2.3;

    // addition with double
    std::cout << "Testing addition with double:" << std::endl;
    std::cout << "c6 + scalar (" << c6 << " + " << scalar << ") == " << (c6 + scalar) << std::endl;
    std::cout << "scalar + c6 (" << scalar << " + " << c6 << ") == " << (scalar + c6) << std::endl;

    // subtraction with double
    std::cout << "\nTesting subtraction with double:" << std::endl;
    std::cout << "c6 - scalar (" << c6 << " - " << scalar << ") == " << (c6 - scalar) << std::endl;
    std::cout << "scalar - c6 (" << scalar << " - " << c6 << ") == " << (scalar - c6) << std::endl;

    // multiplication with double
    std::cout << "\nTesting multiplication with double:" << std::endl;
    std::cout << "c6 * scalar (" << c6 << " * " << scalar << ") == " << (c6 * scalar) << std::endl;
    std::cout << "scalar * c6 (" << scalar << " * " << c6 << ") == " << (scalar * c6) << std::endl;

    // division with double
    std::cout << "\nTesting division with double:" << std::endl;
    std::cout << "c6 / scalar (" << c6 << " / " << scalar << ") == " << (c6 / scalar) << std::endl;
    std::cout << "scalar / c6 (" << scalar << " / " << c6 << ") == " << (scalar / c6) << std::endl;

    // division of two MyComplex objects
    std::cout << "\nTesting division of two MyComplex objects:" << std::endl;
    MyComplex<double> c7(1.1, -1.2);
    std::cout << "c6 / c7 (" << c6 << " / " << c7 << ") == " << (c6 / c7) << std::endl;

    std::cout << "\n===== Testing MyComplex<int> =====\n" << std::endl;

    MyComplex<int> c1_int; // default constructor
    MyComplex<int> c2_int(9, 8); // 2-value constructor
    MyComplex<int> c3_int(7, 6); // 2-value constructor
    MyComplex<int> c4_int(5); // 1-value constructor

    std::cout << "Value of c1_int (default constructor):" << std::endl;
    std::cout << "c1_int.getReal() == " << c1_int.getReal() << ", c1_int.getImaginary() == " << c1_int.getImaginary() << std::endl;

    std::cout << "\nValue of c2_int (2-value constructor):" << std::endl;
    std::cout << "c2_int.getReal() == " << c2_int.getReal() << ", c2_int.getImaginary() == " << c2_int.getImaginary() << std::endl;

    std::cout << "\nValue of c3_int (2-value constructor):" << std::endl;
    std::cout << "c3_int.getReal() == " << c3_int.getReal() << ", c3_int.getImaginary() == " << c3_int.getImaginary() << std::endl;

    std::cout << "\nValue of c4_int (1-value constructor):" << std::endl;
    std::cout << "c4_int.getReal() == " << c4_int.getReal() << ", c4_int.getImaginary() == " << c4_int.getImaginary() << std::endl;

    std::cout << "\nArithmetic operations with MyComplex<int>:" << std::endl;
    std::cout << "c2_int + c3_int (" << c2_int << " + " << c3_int << ") == " << (c2_int + c3_int) << std::endl;
    std::cout << "c2_int - c3_int (" << c2_int << " - " << c3_int << ") == " << (c2_int - c3_int) << std::endl;
    std::cout << "c2_int * c3_int (" << c2_int << " * " << c3_int << ") == " << (c2_int * c3_int) << std::endl;
    std::cout << "c2_int / c3_int (" << c2_int << " / " << c3_int << ") == " << (c2_int / c3_int) << std::endl;

    std::cout << "\nConjugate of c2_int (" << c2_int << ") == " << !c2_int << std::endl;

    // vector of MyComplex<int>
    std::vector<MyComplex<int>> complexVector_int;
    for (int i = 0; i < 5; ++i) {
        complexVector_int.push_back(MyComplex<int>(i, 2 * i));
    }

    std::cout << "\nVector of MyComplex<int>:" << std::endl;
    for (const MyComplex<int>& complexNumber : complexVector_int) {
        std::cout << complexNumber << std::endl;
    }

    // testing with double
    std::cout << "\nTesting MyComplex<double>\n" << std::endl;

    MyComplex<double> c1_double; // default constructor
    MyComplex<double> c2_double(9.0, 8.0); // 2-value constructor
    MyComplex<double> c3_double(7.0, 6.0); // 2-value constructor
    MyComplex<double> c4_double(5.0); // 1-value constructor

    std::cout << "Value of c1_double (default constructor):" << std::endl;
    std::cout << "c1_double.getReal() == " << c1_double.getReal() << ", c1_double.getImaginary() == " << c1_double.getImaginary() << std::endl;

    std::cout << "\nValue of c2_double (2-value constructor):" << std::endl;
    std::cout << "c2_double.getReal() == " << c2_double.getReal() << ", c2_double.getImaginary() == " << c2_double.getImaginary() << std::endl;

    std::cout << "\nValue of c3_double (2-value constructor):" << std::endl;
    std::cout << "c3_double.getReal() == " << c3_double.getReal() << ", c3_double.getImaginary() == " << c3_double.getImaginary() << std::endl;

    std::cout << "\nValue of c4_double (1-value constructor):" << std::endl;
    std::cout << "c4_double.getReal() == " << c4_double.getReal() << ", c4_double.getImaginary() == " << c4_double.getImaginary() << std::endl;

    std::cout << "\nArithmetic operations with MyComplex<double>:" << std::endl;
    std::cout << "c2_double + c3_double (" << c2_double << " + " << c3_double << ") == " << (c2_double + c3_double) << std::endl;
    std::cout << "c2_double - c3_double (" << c2_double << " - " << c3_double << ") == " << (c2_double - c3_double) << std::endl;
    std::cout << "c2_double * c3_double (" << c2_double << " * " << c3_double << ") == " << (c2_double * c3_double) << std::endl;
    std::cout << "c2_double / c3_double (" << c2_double << " / " << c3_double << ") == " << (c2_double / c3_double) << std::endl;

    std::cout << "\nConjugate of c2_double (" << c2_double << ") == " << !c2_double << std::endl;

    // vector of MyComplex<double>
    std::vector<MyComplex<double>> complexVector_double;
    for (int i = 0; i < 5; ++i) {
        complexVector_double.push_back(MyComplex<double>(i + 0.5, 2.0 * i + 0.5));
    }

    std::cout << "\nVector of MyComplex<double>:" << std::endl;
    for (const MyComplex<double>& complexNumber : complexVector_double) {
        std::cout << complexNumber << std::endl;
    }

    // testing scalar operations
    std::cout << "\nTesting Scalar Operations\n" << std::endl;

    // with int
    MyComplex<int> c_int(3, 4);
    int scalar_int = 2;

    std::cout << "Testing scalar operations with MyComplex<int>:" << std::endl;
    std::cout << "c_int + scalar_int (" << c_int << " + " << scalar_int << ") == " << (c_int + scalar_int) << std::endl;
    std::cout << "scalar_int + c_int (" << scalar_int << " + " << c_int << ") == " << (scalar_int + c_int) << std::endl;
    std::cout << "c_int - scalar_int (" << c_int << " - " << scalar_int << ") == " << (c_int - scalar_int) << std::endl;
    std::cout << "scalar_int - c_int (" << scalar_int << " - " << c_int << ") == " << (scalar_int - c_int) << std::endl;
    std::cout << "c_int * scalar_int (" << c_int << " * " << scalar_int << ") == " << (c_int * scalar_int) << std::endl;
    std::cout << "scalar_int * c_int (" << scalar_int << " * " << c_int << ") == " << (scalar_int * c_int) << std::endl;
    std::cout << "c_int / scalar_int (" << c_int << " / " << scalar_int << ") == " << (c_int / scalar_int) << std::endl;
    std::cout << "scalar_int / c_int (" << scalar_int << " / " << c_int << ") == " << (scalar_int / c_int) << std::endl;

    // with double
    MyComplex<double> c_double(3.0, 4.0);
    double scalar_double = 2.0;

    std::cout << "\nTesting scalar operations with MyComplex<double>:" << std::endl;
    std::cout << "c_double + scalar_double (" << c_double << " + " << scalar_double << ") == " << (c_double + scalar_double) << std::endl;
    std::cout << "scalar_double + c_double (" << scalar_double << " + " << c_double << ") == " << (scalar_double + c_double) << std::endl;
    std::cout << "c_double - scalar_double (" << c_double << " - " << scalar_double << ") == " << (c_double - scalar_double) << std::endl;
    std::cout << "scalar_double - c_double (" << scalar_double << " - " << c_double << ") == " << (scalar_double - c_double) << std::endl;
    std::cout << "c_double * scalar_double (" << c_double << " * " << scalar_double << ") == " << (c_double * scalar_double) << std::endl;
    std::cout << "scalar_double * c_double (" << scalar_double << " * " << c_double << ") == " << (scalar_double * c_double) << std::endl;
    std::cout << "c_double / scalar_double (" << c_double << " / " << scalar_double << ") == " << (c_double / scalar_double) << std::endl;
    std::cout << "scalar_double / c_double (" << scalar_double << " / " << c_double << ") == " << (scalar_double / c_double) << std::endl;

    // testing division of two MyComplex objects
    std::cout << "\nTesting Division of Two MyComplex Objects\n" << std::endl;

    MyComplex<int> c_dividend_int(5, 10);
    MyComplex<int> c_divisor_int(2, -3);

    std::cout << "Division with MyComplex<int>:" << std::endl;
    std::cout << c_dividend_int << " / " << c_divisor_int << " == " << (c_dividend_int / c_divisor_int) << std::endl;

    MyComplex<double> c_dividend_double(5.0, 10.0);
    MyComplex<double> c_divisor_double(2.0, -3.0);

    std::cout << "\nDivision with MyComplex<double>:" << std::endl;
    std::cout << c_dividend_double << " / " << c_divisor_double << " == " << (c_dividend_double / c_divisor_double) << std::endl;

    return 0;
}
