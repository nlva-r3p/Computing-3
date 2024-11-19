#include <iostream>
#include <limits> // For numeric limits

// Template class definition
template<typename T>
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
    MyComplex operator+(const T& other) const;
    MyComplex operator+(const MyComplex& other) const;
    MyComplex operator-(const T& other) const;
    MyComplex operator-(const MyComplex& other) const;
    MyComplex operator*(const T& other) const;
    MyComplex operator*(const MyComplex& other) const;
    MyComplex operator/(const T& other) const;
    MyComplex operator/(const MyComplex& other) const;
    MyComplex operator!() const;

    // Friend functions
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const MyComplex<U>& number);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, MyComplex<U>& number);

    template<typename U>
    friend MyComplex<U> operator+(const U& num, const MyComplex<U>& cnum);

    template<typename U>
    friend MyComplex<U> operator-(const U& num, const MyComplex<U>& cnum);

    template<typename U>
    friend MyComplex<U> operator*(const U& num, const MyComplex<U>& cnum);

    template<typename U>
    friend MyComplex<U> operator/(const U& num, const MyComplex<U>& cnum);

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
// b) either one, but not both is zero (2 cases)
// c) both not zero
// d) if imaginary is negative, then + won't be printed
// c and d are implemented in hw4

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyComplex<T>& number) {
    if (number.real == T(0) && number.imaginary == T(0)) {
        os << number.real; // Since both are zero, output real part
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

    // Peek at the next character
    char nextChar = is.peek();
    while (nextChar == ' ') {
        is.get();
        nextChar = is.peek();
    }

    // Check if the input is the imaginary part
    if (nextChar == 'i') {
        number.imaginary = r;
        is.get(); // Consume 'i'
        return is;
    } else {
        number.real = r; // Proceed as normal
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
            is.get(); // Consume 'i'
            number.imaginary = (nextChar == '+') ? i : -i;
        } else {
            number.real += (nextChar == '+') ? i : -i;
        }
    } else {
        is.unget();
    }

    return is;
}

// Operator overloads within the class
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
    if (other == T(0)) {
        std::cerr << "Error! Division by 0!" << std::endl;
        return MyComplex<T>(T(0), T(0)); // Return zero complex number
    }
    return MyComplex<T>(real / other, imaginary / other);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator/(const MyComplex<T>& other) const {
    T denominator = other.real * other.real + other.imaginary * other.imaginary;

    if (denominator == T(0)) {
        std::cerr << "Error! Division by 0!" << std::endl;
        return MyComplex<T>(T(0), T(0)); // Return zero complex number
    }

    T newReal = (real * other.real + imaginary * other.imaginary) / denominator;
    T newImaginary = (imaginary * other.real - real * other.imaginary) / denominator;
    return MyComplex<T>(newReal, newImaginary);
}

template<typename T>
MyComplex<T> MyComplex<T>::operator!() const {
    return MyComplex<T>(real, -imaginary);
}

// Friend operator overloads
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

    if (denominator == T(0)) {
        std::cerr << "Error! Division by 0!" << std::endl;
        return MyComplex<T>(T(0), T(0)); // Return zero complex number
    }

    T newReal = num * cnum.real / denominator;
    T newImaginary = -num * cnum.imaginary / denominator;

    return MyComplex<T>(newReal, newImaginary);
}

// Test the template class with int and double
int main() {
    // Testing with int
    MyComplex<int> a(3, 4);
    MyComplex<int> b(1, -2);

    MyComplex<int> c = a + b;
    std::cout << "a + b = " << c << std::endl;

    MyComplex<int> d = a - b;
    std::cout << "a - b = " << d << std::endl;

    MyComplex<int> e = a * b;
    std::cout << "a * b = " << e << std::endl;

    MyComplex<int> f = a / b; // Note: Integer division
    std::cout << "a / b = " << f << std::endl;

    // Testing with double
    MyComplex<double> x(3.0, 4.0);
    MyComplex<double> y(1.0, -2.0);

    MyComplex<double> z = x + y;
    std::cout << "x + y = " << z << std::endl;

    MyComplex<double> w = x - y;
    std::cout << "x - y = " << w << std::endl;

    MyComplex<double> u = x * y;
    std::cout << "x * y = " << u << std::endl;

    MyComplex<double> v = x / y;
    std::cout << "x / y = " << v << std::endl;

    return 0;
}
