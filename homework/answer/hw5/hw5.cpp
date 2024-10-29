#include <iostream>
#include <vector>
#include <limits> // need to to use max

class MyComplex {
public:
    // Constructors
    MyComplex() : real(0), imaginary(0) {}
    MyComplex(double r) : real(r), imaginary(0) {}
    MyComplex(double r, double i) : real(r), imaginary(i) {}

    // Mutators
    void setReal(double r);
    void setImaginary(double i);
    void setNumbers(double r, double i);
    void conjugateNumbers();

    // Accessors
    double getReal() const;
    double getImaginary() const;
    void outputNumbers() const;

    // Operator overloads
    friend std::ostream& operator<<(std::ostream& os, const MyComplex& number);
    friend std::istream& operator>>(std::istream& is, MyComplex& number);

    MyComplex operator+(const MyComplex& other) const;
    MyComplex operator-(const MyComplex& other) const;
    MyComplex operator*(const MyComplex& other) const;
    MyComplex operator/(const MyComplex& other) const;
    MyComplex operator!() const;

private:
    double real;
    double imaginary;
};

// Mutator definitions
void MyComplex::setReal(double r) {
    real = r;
}

void MyComplex::setImaginary(double i) {
    imaginary = i;
}

void MyComplex::setNumbers(double r, double i) {
    real = r;
    imaginary = i;
}

void MyComplex::conjugateNumbers() {
    imaginary *= -1;
}

// Accessor definitions
double MyComplex::getReal() const {
    return real;
}

double MyComplex::getImaginary() const {
    return imaginary;
}

void MyComplex::outputNumbers() const {
    std::cout << "Re == " << real << ", Im == " << imaginary << std::endl;
}

// Operator overload definitions

// For operator<< we have to consider:
// a) both real and imaginary is 0
// b) either one, but not both is a zero (2 cases)
// c) both not zero
// d) if imaginary is negative, then + won't be printed
// c and d is implemented in hw4

std::ostream& operator<<(std::ostream& os, const MyComplex& number) {
    if (number.real == 0 && number.imaginary == 0) {
        os << number.real; // since both is zero, we can just output whichever
        // os << number.imaginary;
        // os << '0';
    } else if (number.real == 0) {
        os << number.imaginary << 'i';
    } else if (number.imaginary == 0) {
        os << number.real;
    } else {
        os << number.real;
        if (number.imaginary >= 0)
            os << '+';
        os << number.imaginary << 'i';
    }
    return os;
}

std::istream& operator>>(std::istream& is, MyComplex& number) {
    double r;
    is >> r;

    char op; // operator is a reserved keyword so can't use char operator
    is >> op;

    double i;
    is >> i;

    char i_placeholder;
    is >> i_placeholder;

    number.real = r;

    if (op == '+')
        number.imaginary = i;
    else if (op == '-')
        number.imaginary = -i;

    return is;
}

MyComplex MyComplex::operator+(const MyComplex& other) const {
    return MyComplex(real + other.real, imaginary + other.imaginary);
}

MyComplex MyComplex::operator-(const MyComplex& other) const {
    return MyComplex(real - other.real, imaginary - other.imaginary);
}

MyComplex MyComplex::operator*(const MyComplex& other) const {
    double newReal = real * other.real - imaginary * other.imaginary;
    double newImaginary = real * other.imaginary + imaginary * other.real;
    return MyComplex(newReal, newImaginary);
}

MyComplex MyComplex::operator/(const MyComplex& other) const {
    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    double newReal = (real * other.real + imaginary * other.imaginary) / denominator;
    double newImaginary = (imaginary * other.real - real * other.imaginary) / denominator;
    return MyComplex(newReal, newImaginary);
}

MyComplex MyComplex::operator!() const {
    return MyComplex(real, -imaginary);
}

// Main function
int main() {
    MyComplex c1; // default constructor
    MyComplex c2(9, 8); // 2-value constructor
    MyComplex c3(7, 6); // 2-value constructor
    MyComplex c4(5); // 1-value constructor

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
    // arithmetics
    std::cout << "c2 + c3 (" << c2 << " + " << c3 << ") == " << (c2 + c3) << std::endl;
    std::cout << "c2 - c3 (" << c2 << " - " << c3 << ") == " << (c2 - c3) << std::endl;
    std::cout << "c2 * c3 (" << c2 << " * " << c3 << ") == " << (c2 * c3) << std::endl;
    std::cout << "c2 / c3 (" << c2 << " / " << c3 << ") == " << (c2 / c3) << std::endl;

    std::cout << std::endl;
    // conjugation using operator!
    std::cout << "Conjugate of c2 (" << c2 << ") == " << !c2 << std::endl;

    // conjugation using conjugate() member function
    std::cout << "Conjugate of c2 using conjugate() member function:" << std::endl;
    c2.conjugateNumbers();
    std::cout << "c2 after conjugate(): " << c2 << std::endl;

    // reset c2 by conjugating it again to negate previous conjugation
    c2.conjugateNumbers();

    std::cout << std::endl;
    // declare vector
    std::vector<MyComplex> complexVector;

    // declare iterator of vector<MyComplex> datatype
    std::vector<MyComplex>::iterator iter;

    for (int i = 0; i < 10; ++i) {
        complexVector.push_back(MyComplex(i, 2 * i));
    }

    std::cout << "Vector output using indexed for-loop:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << complexVector[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Vector output using ranged-based for-loop:" << std::endl;
    for (MyComplex complexNumber : complexVector) {
        std::cout << complexNumber << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Vector output using iterator for-loop:" << std::endl;
    for (iter = complexVector.begin(); iter != complexVector.end(); ++iter) {
        std::cout << *iter << std::endl;
    }



    // Testing mutator functions because didn't do it for hw4
    // Using setReal
    MyComplex m1;
    std::cout << "Initial m1: " << m1 << std::endl;
    m1.setReal(5);
    std::cout << "After m1.setReal(5): " << m1 << std::endl;

    // Using setImaginary
    m1.setImaginary(3);
    std::cout << "After m1.setImaginary(3): " << m1 << std::endl;

    // Using setNumbers
    m1.setNumbers(10, -4);
    std::cout << "After m1.setNumbers(10, -4): " << m1 << std::endl;

    // Using conjugate
    m1.conjugate();
    std::cout << "After m1.conjugate(): " << m1 << std::endl;




    // Testing hw5 functions
    std::cout << "\nTesting istream operator:" << std::endl;
    MyComplex c5;
    std::cout << "Enter a complex number in the form a+bi (e.g., 3+4i): ";
    std::cin >> c5;
    if (!std::cin.fail()) {
        std::cout << "You entered: " << c5 << std::endl;
    } else {
        std::cout << "Invalid input." << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // from cs lab
    }

    // Testing conjugate() member function
    std::cout << "\nTesting conjugate() member function:" << std::endl;
    std::cout << "Original c5: " << c5 << std::endl;
    c5.conjugateNumbers();
    std::cout << "Conjugated c5: " << c5 << std::endl;

    // Testing operator<< with zero parts
    std::cout << "\nTesting operator<< with zero parts:" << std::endl;
    MyComplex zeroNumber(0, 0);
    MyComplex realOnlyNumber(-2, 0);
    MyComplex imagOnlyNumber1(0, 3);
    MyComplex imagOnlyNumber2(0, -4);

    std::cout << "zeroNumber (0+0i): " << zeroNumber << std::endl;
    std::cout << "realOnlyNumber (-2+0i): " << realOnlyNumber << std::endl;
    std::cout << "imagOnlyNumber1 (0+3i): " << imagOnlyNumber1 << std::endl;
    std::cout << "imagOnlyNumber2 (0-4i): " << imagOnlyNumber2 << std::endl;

    return 0;
}

