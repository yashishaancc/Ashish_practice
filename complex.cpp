#include <iostream>
using namespace std;

#define print1(a) std::cout << "[" << __LINE__ << "]"  << #a": " << a \
    << std::endl;
#define print2(a, b) std::cout << "[" << __LINE__ << "]" << #a": " << a \
    << ", "#b": " << b << std::endl;
#define print3(a, b, c) std::cout << "[" << __LINE__ << "]"  << #a": " << a \
    << ", "#b": " << b << ", "#c": " << c << std::endl;
#define print4(a, b, c, d) std::cout << "[" << __LINE__ << "]"  << #a": " << a \
    << ", "#b": " << b << ", "#c": " << c << ", "#d": " << d << std::endl;
#define print5(a, b, c, d, e) std::cout << "[" << __LINE__ << "]"  \
    << #a": " << a << ", "#b": " << b << ", "#c": " << c << ", "#d": " << d \
    << ", "#e": " << e << std::endl;


class Complex {
    double real;
    double imag;
public:
    // Constructors
    Complex() : real(0.0), imag(0.0) {
        std::cout << "no argument constructor called " << this << "\n";
    }
    Complex(double real, double imag) : real(real), imag(imag) {
        std::cout << "two argument constructor called " << this << "\n";
    }
    Complex(const Complex & other){
        std::cout << "copy constructor called " << this << "\n";
        real = other.real;
        imag = other.imag;
    }
    ~Complex(){
        std::cout << "destructor called: " << this << " ";
        std:cout << real << " + " << imag << "i\n";
    }
    void operator=(const Complex& other){
        std::cout << "= operator called" << std::endl;
        real = other.real;
        imag = other.imag;
    }
    // Getter methods
    double getReal() const {
        return real;
    }

    double getImaginary() const {
        return imag;
    }

    // Setter methods
    void setReal(double newReal) {
        real = newReal;
    }

    void setImaginary(double newImag) {
        imag = newImag;
    }

    // Other methods
    Complex add(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex subtract(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex multiply(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, \
            real * other.imag + imag * other.real);
    }
    /*how to overload any operator*/
    /*
    RETURN_TYPE operator OPERATOR_SYMBOL (ARGUMENTS){
        // definition
    }
    
    Here, OPERATOR_SYMBOL can be anything. 
    Examples: +, -, *, /, (), [], <<, >>, ++, --, +=, etc
    Every symbol requires a specific signature. 
    Google what's the signature for [] operator?
    Return_type and Arguments depend on the signature for that symbol.

    Example: overloading operator+
    Complex operator+ (const Complex& other){
        std::cout << "+ operator called. other.real = " << other.real \
                  << ", other.img: " << other.imag << std::endl;
        Complex newComplex(real+other.real, img+other.img);
        return newComplex;
    }
    */

   Complex operator+(const Complex& other){
        std::cout << "+ operator called. other.real = " << other.real \
                  << ", other.img: " << other.imag << std::endl;
        Complex newComplex(real+other.real, imag+other.imag);
        // print1(newComplex);
        return newComplex;
    }

    Complex operator+(double other){
        // std::cout << "+ operator called. other.real = " << other.real \
        //           << ", other.img: " << other.imag << std::endl;
        Complex newComplex(real+other, imag+other);
        // print1(newComplex);
        return newComplex;
    }

    Complex operator-(const Complex& other){
        std::cout << "- operator called. other.real = " << other.real \
                  << ", other.img: " << other.imag << std::endl;
        Complex newComplex(real-other.real, imag-other.imag);
        print1(newComplex);
        return newComplex;
    }

    Complex operator*(const Complex& other){
        std::cout << "* operator called. other.real = " << other.real \
                  << ", other.img: " << other.imag << std::endl;
        Complex newComplex(real*other.real-imag*other.imag, \
                           real*other.imag+imag*other.real);
        print1(newComplex);
        return newComplex;
    }

    Complex operator/(const Complex& other){
        std::cout << "/ operator called. other.real = " << other.real \
                  << ", other.img: " << other.imag << std::endl;
        double a = real, b = imag, c = other.real, d = other.imag;
        Complex newComplex((a*c+b*d)/(c*c+d*d), (b*c-a*d)/(c*c+d*d));
        print1(newComplex);
        return newComplex;
    }

    void operator()(int arg) {
        std::cout << "Calling function with argument: " << arg << std::endl;
    }

    void operator()(double r, double i) {
        std::cout << "Calling function with 2 arguments" << std::endl;
        real = r;
        imag = i;
    }

    double& operator[](int index) {
        if (index == 0)return real;
        else if (index == 1)return imag;
        else throw std::out_of_range("Invalid index for complex number");
    }

    Complex& operator++(int){
        std::cout << "++ operator called" << std::endl;
        real += 1;
        imag += 1;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c){
        // std::cout << "operator << called" << std::endl;
        // os << "real: " << c.real << ", imag: " << c.imag;
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};

std::ostream& operator<<(std::ostream& os, const Complex* const &c){
    // std::cout << "operator << called" << std::endl;
    // os << "real: " << c.real << ", imag: " << c.imag;
    os << c->getReal() << " + " << c->getImaginary() << "i";
    return os;
}

int main(){
    Complex c1(3.0, 4.0);
    Complex c2(1.5, 2.5);
    {
        Complex x(c1);
        Complex y;
        y = c2;
        y(55);
        y++;
        Complex* z = new Complex(5, 3);
        cout << z << endl;
        delete z;
    }
    c1(2, 4);
    // new (&c1) Complex(); // new placent
    print1(c1);
    Complex c3 = c2, c4, c5, c6, c7;
    c4 = c3;

    c4 = c1+c2;
    c4 = c1+3;
    // c5 = c1-c2;
    // c6 = c1*c2;
    // c7 = c1/c2;
    // c4 = c1.operator+(c2);
    //Above two lines are exactly the same.
    c4[0] = 5;
    c4[1] = 2;
    print3(c4, c1, c2);
    // print4(c4, c5, c6, c7);
    // std::cout << "c4: " << c4 << ", c1: " << c1 << ", c2: " << c2 << std::endl;

    // Complex sum = c1.add(c2);
    // Complex subtraction = c1.subtract(c2);
    // Complex product = c1.multiply(c2);

    // double realPart = sum.getReal();
    // double imagPart = sum.getImaginary();

    // std::cout << "Sum: " << realPart << " + " << imagPart << "i" << std::endl;
    // std::cout << "Subtraction: " << subtraction.getReal() << " + " 
    //           << subtraction.getImaginary() << "i" << std::endl;
    // std::cout << "Product: " << product.getReal() << " + " 
    //           << product.getImaginary() << "i" << std::endl;
}