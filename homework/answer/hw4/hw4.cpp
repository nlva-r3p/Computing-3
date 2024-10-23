#include <iostream>
#include <vector>

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

    // Accessors
    double getReal() const;
    double getImaginary() const;
    void outputNumbers() const;

    // Operator overloads
    friend std::ostream& operator<<(std::ostream& os, const MyComplex& number);

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
std::ostream& operator<<(std::ostream& os, const MyComplex& number) {
    os << number.real;
    if (number.imaginary >= 0)
        os << '+';
    os << number.imaginary << 'i';
    return os;
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
    // conjugation
    std::cout << "Conjugate of c2 (" << c2 << ") == " << !c2 << std::endl;

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

    return 0;
}

