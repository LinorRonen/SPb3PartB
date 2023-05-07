#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <stdexcept>
#include <limits>
using namespace std;

namespace ariel
{

class Fraction {

private:

    //the numerator
    int numerator;

    //the denominator
    int denominator;
    
    // reduce() without parameters
    void reduce();

    // reduce() that get ref to numerator and ref to denominator
    void reduce(int& numerator, int& denominator) const;
    
    // gcd () function
    int gcd(int num1, int num2)const;

    //check overflow for +
    static int overflow_Addition(const int& num1, const int& num2);

    // check overflow for -
    static int overflow_Subtraction(int num1, int num2);

    // check overflow for *
    static int overflow_Multiplication(int num1, int num2);

    // check overflow for /
    static int overflow_Division(int num1, int num2);

public:

    // Default constructor
    Fraction(); 

    // constructor that get numerator and denominator
    Fraction(int numerator, int denominator);

    //Fraction(int numerator);
    Fraction(float num);

    // copy constructor
    Fraction(const Fraction& other); 

    // Move constructor
    Fraction(Fraction&& other)noexcept;

    // Copy assignment operator
    Fraction& operator=(const Fraction& other);

    // Move assignment operator
    Fraction& operator=(Fraction&& other)noexcept;

    // Destructor
    ~Fraction();

    // Arithmetic operations - get &Fraction

    // operator+
    Fraction operator+(const Fraction& other) const;

    // operator-
    Fraction operator-(const Fraction& other) const;

    // operator*
    Fraction operator*(const Fraction& other) const;

    // operator/
    Fraction operator/(const Fraction& other) const;

    // Comparison operations - get Fraction&

    // operator==
    bool operator==(const Fraction& other) const;

    // operator!=
    bool operator!=(const Fraction& other) const;

    // operator>
    bool operator>(const Fraction& other) const;

    // operator<
    bool operator<(const Fraction& other) const;

    // operator>=
    bool operator>=(const Fraction& other) const;

    // operator<=
    bool operator<=(const Fraction& other) const;

    // pre-increment
    Fraction operator++();

     // post-increment 
    Fraction operator++(int);

    // pre-decrement
    Fraction operator--(); 

    // post-decrement
    Fraction operator--(int); 


    // getNumerator()
    int getNumerator() const;

    // getDenominator()
    int getDenominator() const;

    // setNumerator(int numerator)
    void setNumerator(int numerator);
    
    // setDenominator(int denominator)
    void setDenominator(int denominator);

    
    // Output operation - ostream
    friend std::ostream& operator<<(std::ostream& output, const Fraction& fraction);

    //Input operation - istream
    friend std::istream& operator>>(std::istream& input, Fraction& fraction);


    //Arithmetic operations

    //Add float to fraction
    friend Fraction operator+(const float& num1, const Fraction& num2);

    //Add fraction to float
    friend Fraction operator+(const Fraction& curr, const float& num);
    
    //Subtract float from fraction
    friend Fraction operator-(const float& num1, const Fraction& num2);

    //Subtract fraction from float
    friend Fraction operator-(const Fraction& curr, const float& num);

    //Multiply fraction with float
    friend Fraction operator*(const float& num1, const Fraction& num2);

    //Multiply fraction with float
    friend Fraction operator*(const Fraction& curr, const float& num);

    //Divide float by fraction
    friend Fraction operator/(const float& num1, const Fraction& num2);

    //Divide fraction by float
    friend Fraction operator/(const Fraction& curr, const float& num1);

    //Greater than or equal to float
    friend bool operator>=(const float& num, const Fraction& fraction);

    //Less than or equal to float
    friend bool operator<=(const float& num, const Fraction& fraction);

    //Less than float
    friend bool operator<(const float& num, const Fraction& fraction);

    //Less than fraction
    friend bool operator<(const Fraction& fraction, const float& num);

    //Greater than float
    friend bool operator>(const float& num, const Fraction& fraction);

    //Greater than fraction
    friend bool operator>(const Fraction& fraction, const float& num);

    //operator+= method - get &fraction and &other
    friend Fraction& operator+=(Fraction& fraction, const Fraction& other);

    //operator+= method - get &fraction and float& num
    friend Fraction& operator+=(Fraction& fraction, const float& num);
    

    // Explicit conversion operators

    // Explicit conversion operator to convert Fraction to float
    explicit operator float() const;

    // Explicit conversion operator to convert Fraction to double
    explicit operator double() const;

};
    
}

#endif // FRACTION_HPP

