// GROUP 38
// Name: Umar-Farooq Sheikh, ID: 20775784
// Name: Shi Jie Tan, ID: 20616539

#include "lab1_polynomial.hpp" // include header file for compiler

#include <iostream> // include iostream library
#include <fstream> // include fstream library to read files
#include <vector> // include vector library for use in Polynomial class
#include <string> // include string library for parsing
#include <random> // include random library for generation of random numbers
#include <cassert> // include cassert library for testing
#include <ctime> // include ctime vector library for randomization


// implement Polynomial parametric constructor
// contains polynomial coefficients and populates internal array with inputted values
Polynomial::Polynomial(int A[], int size) {
    // resize data vector with size input
    data.resize(size, 0);

    // set each value at index of data vector 
    // equal to value at index of A vector
    for (int i = 0; i < size; ++i) {
        data[i] = A[i];
    }
}

// implement Polynomial empty constructor
Polynomial::Polynomial() {
    int degree = rand() % 1001;  // initialize variable representing the degree of the polynomial
    int rand_coeff; // initialize randomized coefficient variable

    // loop generates random coefficients to input into vector using an iterator
    for (int iterator = 0, rand_num, rand_sign; iterator < degree; ++iterator) {
        rand_num = rand() % 1001;
        rand_sign = rand() % 2;

        // if statement on rand_sign; determine sign of coefficient
        if (rand_sign == 1) {
            rand_coeff = rand_num;
        } else {
            rand_coeff = -rand_num;
        }

        // add randomized coefficient to vector
        data.push_back(rand_coeff);
    }
}

// implement Polynomial parametric constructor 
// file reads polynomial size and coefficients
Polynomial::Polynomial (std::string fileName) {
    // declare function-scope variables
    std::ifstream inputFile(fileName); // ifstream from the fileName input
    int size; // to hold size of Polynomial data vector from file

    if (!inputFile) { // check if file is open
        std::cout << "File \"" << fileName << "\" cannot be opened." << std::endl;
    } else if (inputFile.peek() == std::ifstream::traits_type::eof()) { // check if file is empty
        std::cout << "File \"" << fileName << "\" is empty. No data to be read." << std::endl;
    } else { // else read from file
        // read value into size variable
        inputFile >> size;

        // resize data vector to match size
        data.resize(size, 0);

        // fill data vector in from file
        for (int i = 0; i <= data.size(); ++i) {
            if (inputFile.good()) { // if file is ok, read value in from file
                inputFile >> data[i];
            } else { // else, set data at index equal to 0
                data[i] = 0;
            }
        }
    }
}


// Polynomial destructor; no need for implementation
Polynomial::~Polynomial() {

}

// implement Polynomial class print function
void Polynomial::print() {
    // declare function-scope variables
    std::string temp = "", expression = ""; // expression to be printed out
    int pop_back_limit = 3; // limit for popping the last three characters of expression variable
    
    // loop through array; add temp value to expression depending on condition
    for (int i = data.size() - 1; i >= 0; --i) {
        if (data[i] == 0) { // if value is 0, temp is kept empty, nothing added to expression
            temp = "";
        } else if (data[i] > 0){ // else if value positive, temp set to part of expression
            temp = std::to_string(data[i]) + "x^" + std::to_string(i) + " + ";
        } else { // else value is negative, wrap negative term in ()
            temp = "(" + std::to_string(data[i]) + "x^" + std::to_string(i) + ") + ";
        }

        // add temp to expression
        expression += temp;
    }

    // if expression is empty, means that data does not contain non-zero values, print out 0
    if (expression.empty()) std::cout << "0" << std::endl;

    // if expression is not empty, pop last three characters 
    // of expression (" + ") and print expression
    if (!expression.empty()) {
        for (int i = 0; i < pop_back_limit; ++i) {
            expression.pop_back();
        }

        std::cout << expression << std::endl;
    }
}

// implement the overloaded operators and functions defined above
bool Polynomial::operator==(const Polynomial& target) {
    // compare target coefficients with the data coefficients
    // vectors have in-built operator== :)
    if (data == target.data) { // return true if vectors equal
        return true;
    } else { // else, return false
        return false;
    }
}

// implement overloaded operator+ for Polynomial class
Polynomial Polynomial::operator+ (const Polynomial& target) {
    // resize data vector if target vector bigger
    if (target.data.size() > data.size()) {
        data.resize(target.data.size(), 0);
    }

    // loop until size of target reached; add vectors at index together
    for (int i = 0; i < target.data.size(); ++i) {
        data[i] = data[i] + target.data[i];
    }

    // return "this" instance, data vector adjusted
    return *this;
} 

// implement overloaded operator- for Polynomial class
Polynomial Polynomial::operator- (const Polynomial& target) {
    // resize data vector if target vector bigger
    if (target.data.size() > data.size()) {
        data.resize(target.data.size(), 0);
    }

    // loop until size of target reached; subtract vectors at index together
    for (int i = 0; i < target.data.size(); ++i) {
        data[i] = data[i] - target.data[i];
    }

    // return "this" instance, data vector adjusted
    return *this;
}

// implement overloaded operator* for Polynomial class
Polynomial Polynomial::operator* (const Polynomial& target) {
    // function-scope variable; captures product of two Polynomials
    std::vector<int> new_data;

    // resize new_data vector to allow for all products to be added
    new_data.resize(target.data.size() + data.size() - 1, 0);

    // loop through both Polynomials and multiply; add result to new_data vector
    for (int i = 0; i < target.data.size(); ++i) {
        for (int j = 0; j < data.size(); ++j) {
            new_data[i + j] += target.data[i] * data[j];
        }
    }

    // set data to the new_data vectpr
    data = new_data;

    // return "this" instance, data vector adjusted
    return *this;
}

// implement derivative method for Polynomial class
Polynomial Polynomial::derivative() {
    // loop through data vector, deriving each term
    for (int i = 0; i < data.size() - 1; i++) {
        data[i] = data[i + 1] * (i + 1);
    }

    // remove the last / largest term
    if (data.size() > 0) data.pop_back();
    
    // return "this" instance, data vector adjusted
    return *this;
}

// implement tests
// test if the polynomial function contains data
bool PolynomialTest::test_empty_constructor() {
    // empty construtors used for 2 instances
    Polynomial poly;
    Polynomial poly2;

    // check to see if instances are different; initialize new bool variable
    bool poly_check = !(poly == poly2);

    // return bool variable
    return poly_check;
}

// test if the polynomial array and size operate
bool PolynomialTest::test_parametric_constructor_array_and_size(int n_array[], int size) {
    // initialize test variables; test Polynomial and test int vector
    Polynomial poly(n_array, size);
    std::vector<int> check_data_vector;
    
    // loop through array and add to test data vector
    for (int i = 0; i < size; i++) {
        check_data_vector.push_back(n_array[i]);
    }

    // Polynomial data vector should be equal to test vector
    bool check_data = (poly.data == check_data_vector);

    // return bool variable
    return check_data;
}

// test if the polynomial parametric constructor reads a file
bool PolynomialTest::test_parametric_constructor_read_file(std::string n_file) {
    // initialize test variables
    Polynomial data(n_file); // read file into test Polynomial
    std::ifstream inputFile(n_file); // ifstream for testing with file separate from Polynomial
    std::vector<int> check_data; // copy data from file into vector
    int size = 0; // read size of vector
    bool check = true; // bool variable for return


    if (!inputFile) { // check if file is open
        std::cout << "File \"" << n_file << "\" cannot be opened." << std::endl;
    } else if (inputFile.peek() == std::ifstream::traits_type::eof()) { // check if file is empty
        std::cout << "File \"" << n_file << "\" is empty. No data to be read." << std::endl;
    } else { // else read from file
        // read value into size variable
        inputFile >> size;

        // resize check_data vector to match size
        check_data.resize(size, 0);

        // fill check_data vector in from file
        for (int i = 0; i <= size; ++i) {
            if (inputFile.good()) { // if file is ok, read value in from file
                inputFile >> check_data[i];
            } else { // else, set data at index equal to 0, if file does not contain all the data
                check_data[i] = 0;
            }
        }
    }

    // check if vectors are the same after read in
    check = check && (check_data == data.data);

    // return check
    return check;
}

// implement test print method;
void PolynomialTest::test_print_method() {
    int n_array[2] = {1, 1};
    Polynomial poly(n_array, 2);

    std::cout << "Should return \"1x^1 + 1x^0\"" << std::endl;
    std::cout << "Result: ";
    poly.print();
};

// implement test operator== method
// 3 cases coded in test method
bool PolynomialTest::test_operator_equal() {
    int n_array[0] = {};
    int n_array2[2] = {1, 1};
    Polynomial poly(n_array, 0);
    Polynomial poly2(n_array2, 2);
    Polynomial poly3(n_array, 0);
    Polynomial poly4(n_array2, 2);
    bool check = true;
    
    // test case 1: empty Polynomial not equal to non-empty Polynomial
    check = check && !(poly == poly2);

    // test case 2: empty Polynomials are equal
    check = check && (poly == poly3);

    // test case 3: identical Polynomials are equal
    check = check && (poly2 == poly4);

    return check;
}

// implement test operator+ method
bool PolynomialTest::test_operator_add() {
    int n_array[0] = {};
    int n_array2[2] = {1, 1};
    Polynomial poly(n_array, 0);
    Polynomial poly2(n_array2, 2);
    Polynomial poly3(n_array, 0);
    Polynomial poly4(n_array2, 2);
    bool check = true;

    // test case 1: add empty vectors together into one polynomial, check if they are still equal
    poly = poly + poly3;
    check = check && (poly == poly3);

    // test case 2: add empty and filled vectors together into empty vector,
    //              check if original empty vector now filled / unequal to other empty vector
    poly = poly + poly2;
    check = check && !(poly == poly3);

    // test case 3: add filled vectors together, check if correctly added to a test result
    int n_array3[2] = {2, 2};
    Polynomial test(n_array3, 2);
    poly2 = poly2 + poly4;
    check = check && (poly2 == test);

    return check;
}

// implement test operator- method
bool PolynomialTest::test_operator_subtract() {
    int n_array[0] = {};
    int n_array2[2] = {1, 1};
    int n_array3[1] = {1};
    Polynomial poly(n_array, 0);
    Polynomial poly2(n_array2, 2);
    Polynomial poly3(n_array, 0);
    Polynomial poly4(n_array3, 2);
    bool check = true;

    // test case 1: subtract empty vectors from each other into one polynomial, 
    // check if they are still equal
    poly = poly - poly3;
    check = check && (poly == poly3);

    // test case 2: subtract filled vectors from empty vector into empty vector,
    //              check if original empty vector now filled / unequal to other empty vector
    poly = poly - poly2;
    check = check && !(poly == poly3);

    // test case 3: subtract 1 filled vector from other, check if correctly added to a test result
    int n_array4[2] = {1, 0};
    Polynomial test(n_array4, 2);
    poly2 = poly2 - poly4;
    check = check && (poly2 == test);

    return check;
}

// implement test_operator* method
bool PolynomialTest::test_operator_multiply() {
    int n_array[0] = {};
    int n_array2[2] = {2, 1};
    Polynomial poly(n_array, 0);
    Polynomial poly2(n_array2, 2);
    Polynomial poly3(n_array, 0);
    Polynomial poly4(n_array2, 2);
    bool check = true;

    // test case 1: multiply empty vectors together into one polynomial, check if they are still equal
    poly = poly * poly3;
    check = check && (poly == poly3);

    // test case 2: multiply empty and filled vectors together into empty vector,
    //              check if original empty vector still equal to other empty vector
    poly = poly * poly2;
    check = check && (poly == poly3);

    // test case 3: multpily filled vectors together, check if correctly equal to a test result
    int n_array3[3] = {4, 4, 1};
    Polynomial test(n_array3, 3);
    poly2 = poly2 * poly4;
    check = check && (poly2 == test);

    return check;
}

// implement test derivative method
bool PolynomialTest::test_derivative() {
    int n_array[0] = {};
    int n_array2[2] = {1, 1};
    std::vector<int> zero_vect = {};
    Polynomial poly(n_array, 0);
    Polynomial poly2(n_array2, 2);
    Polynomial poly3(n_array, 0);
    Polynomial poly4(n_array2, 2);
    bool check = true;

    // test case 1: derivative of empty polynomial, check if still empty
    poly.derivative();
    check = check && (poly == poly3);

    // test case 2: add empty and filled vectors together into empty vector,
    //              derive then check if original empty vector now filled / unequal to other empty vector
    int n_array3[1] = {1};
    Polynomial test(n_array3, 1);
    poly = poly + poly2;
    poly.derivative();
    check = check && !(poly == poly3);

    // test case 3: derive then check if original empty vector is now equal to other empty vector
    poly.derivative();
    check = check && (poly == poly3);

    return check;
}

// implement run function calling all tests
void PolynomialTest::run() {
    int my_array[3] = {1, 2, 3};
    int size = 3;
    std::string filename = "readtest.txt"; // submitted with code
    PolynomialTest test;

    if (test.test_empty_constructor()) {
        std::cout << "Empty constructor test ran correctly." << std::endl;
    } else {
        std::cout << "Empty constructor test failed." << std::endl;
    }

    if (test.test_parametric_constructor_array_and_size(my_array, size)) {
        std::cout << "Parametric constructor from array and size test ran correctly." << std::endl;
    } else {
        std::cout << "Parametric constructor from array and size test failed." << std::endl;
    }

    if (test.test_parametric_constructor_read_file(filename)) {
        std::cout << "Parametric constructor from file test ran correctly." << std::endl;
    } else {
        std::cout << "Parametric constructor from file test failed." << std::endl;
    }

    test.test_print_method();

    if (test.test_operator_equal()) {
        std::cout << "Operator== test ran correctly." << std::endl;
    } else {
        std::cout << "Operator== test failed." << std::endl;
    }

    if (test.test_operator_add()) {
        std::cout << "Operator+ test ran correctly." << std::endl;
    } else {
        std::cout << "Operator+ test failed." << std::endl;
    }

    if (test.test_operator_subtract()) {
        std::cout << "Operator- test ran correctly." << std::endl;
    } else {
        std::cout << "Operator- test failed." << std::endl;
    }

    if (test.test_operator_multiply()) {
        std::cout << "Operator* test ran correctly." << std::endl;
    } else {
        std::cout << "Operator* test failed." << std::endl;
    }

    if (test.test_derivative()) {
        std::cout << "Derivative test ran correctly." << std::endl;
    } else {
        std::cout << "Derivative test failed." << std::endl;
    }
}

int main() {
    srand(time(0));

    PolynomialTest testing123;

    testing123.run();

    return 0;
}

