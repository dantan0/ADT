// GROUP 38
// Name: Umar-Farooq Sheikh, ID: 20775784
// Name: Shi Jie Tan, ID: 20616539

// compiler directive
#ifndef SYDE223_LAB1_POLYNOMIAL 
#define SYDE223_LAB1_POLYNOMIAL

#include <iostream> // include iostream library
#include <vector> // include vector library for use in Polynomial class
#include <string> // include string library for parsing
#include <iterator> // for vector iterator

// declare Polynomial class
class Polynomial {
    // private class members

    // declare vector
    std::vector<int> data;

    //declare vector iterator
    std::vector<int>::iterator ptr;

public: 
    // empty class constructor
    Polynomial();

    // parametric class constructor; reads array and size into instance
    Polynomial(int A[], int size);

    // parametric class constructor; reads from file to build instance
    Polynomial(std::string filename);

    // class destructor
    ~Polynomial();

    // method to print polynomial to console
    void print();

    // overloaded operator== method; allows comparison of polynomials
    bool operator==(const Polynomial& target);

    // overloaded operator+ method; allows addition of polynomials
    Polynomial operator+(const Polynomial& target);

    // overloaded operator- method; allows subtraction of polynomials
    Polynomial operator-(const Polynomial& target);

    // overloaded operator* method; allows multiplication of polynomials
    Polynomial operator*(const Polynomial& target);

    // method to calculate the derivative of the polynomial
    Polynomial derivative();
    
    // friend testing class declaration
    friend class PolynomialTest;
};

class PolynomialTest {
public:
    // declare empty constructor test
    bool test_empty_constructor();

    // declare parametric constructor with array and size test
    bool test_parametric_constructor_array_and_size(int n_array[], int num);

    // declare parametric constructor reading a file test
    bool test_parametric_constructor_read_file(std::string n_file);

    // declare test print method;
    void test_print_method();

    // declare test operator== method
    bool test_operator_equal();

    // declare test operator+ method
    bool test_operator_add();

    // declare test operator- method
    bool test_operator_subtract();

    // declare test_operator* method
    bool test_operator_multiply();

    // declare test derivative method
    bool test_derivative();

    // declare function calling all tests
    void run();
};

#endif // LAB1_POLYNOMIAL_HPP; for completing compiler directive