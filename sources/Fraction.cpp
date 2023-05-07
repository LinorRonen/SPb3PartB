#include "Fraction.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <climits>


using namespace std;

namespace ariel
{

// Default constructor
Fraction::Fraction() : numerator(0), denominator(1) {}

//Constructor that gets numerator and denominator
Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

// Constructor that gets a float number
Fraction::Fraction(float numF)
{
    int digits = 1000; // Maximum of three digits after the decimal point
    this->numerator = static_cast<int>(round(numF * digits));
    this->denominator = digits;
    reduce();
}
	
// copy constructor
Fraction::Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

// Move constructor
Fraction::Fraction(Fraction&& other) noexcept : numerator(other.numerator), denominator(other.denominator)
{
    other.numerator = 0;
    other.denominator = 1;
}

// Copy assignment operator
Fraction& Fraction::operator=(const Fraction& other)
{
    if (this != &other) {
        // Assign the numerator and denominator of the other Fraction object to this object
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

// Move assignment operator
Fraction& Fraction::operator=(Fraction&& other)noexcept
{
    if (this != &other) {
        // Transfer the numerator and denominator of the other Fraction object to this object
        numerator = other.numerator;
        denominator = other.denominator;

        // Set the numerator and denominator of the other Fraction object to 0 and 1 respectively
        other.numerator = 0;
        other.denominator = 1;
    }
    return *this;
}

// Destructor
Fraction::~Fraction(){}

// reduce() - without parameters 
// This function reduces a fraction to its owest terms by dividing both the numerator and 
// denominator by their greatest common divisor (GCD).
void Fraction::reduce()
{
    if (denominator < 0)
    {
        this->numerator *= -1;
        this->denominator *= -1;
    }
    int div = gcd(abs(numerator), abs(denominator));
    this->numerator /= div;
    this->denominator /= div;
}

// reduce() - with a given &numerator and &denominator
void Fraction::reduce(int& numerator, int& denominator) const
{
    if (denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }
    int div = gcd(abs(numerator), abs(denominator));
    numerator /= div;
    denominator /= div;
}

// gcd() - this function calculates the greatest common divisor (GCD) of two integers using a recursive.
int Fraction::gcd(int num1, int num2)const{
    if (num1 == 0) {
        return num2;
    }
    return gcd(num2 % num1, num1);
}

// check overflow for +
int Fraction::overflow_Addition(const int& num1, const int& num2)
{
    if ((num1 > 0 && num2 > std::numeric_limits<int>::max() - num1) ||
        (num1 < 0 && num2 < std::numeric_limits<int>::min() - num1))
    {
        throw std::overflow_error("Addition overflow");
    }
    return (num1 + num2);
}

// check overflow for -
int Fraction::overflow_Subtraction(int num1, int num2)
{
    if ((num2 < 0 && num1 > std::numeric_limits<int>::max() + num2) ||
        (num2 > 0 && num1 < std::numeric_limits<int>::min() + num2))
    {
        throw std::overflow_error("Subtraction overflow");
    }
    return (num1 - num2);
}

// check overflow for *
int Fraction::overflow_Multiplication(int num1, int num2)
{
    if ((num1 > 0 && num2 > 0 && num1 > std::numeric_limits<int>::max() / num2) ||
        (num1 > 0 && num2 < 0 && num2 < std::numeric_limits<int>::min() / num1) ||
        (num1 < 0 && num2 > 0 && num1 < std::numeric_limits<int>::min() / num2) ||
        (num1 < 0 && num2 < 0 && num1 < std::numeric_limits<int>::max() / num2))
    {
        throw std::overflow_error("Multiplication overflow");
    }
    return num1 * num2;
}

// check overflow for /
int Fraction::overflow_Division(int num1, int num2)
{
    if (num2 == 0)
    {
        throw std::runtime_error("Division by zero");
    }
    if (num1 == std::numeric_limits<int>::min() && num2 == -1)
    {
        throw std::overflow_error("Division overflow");
    }
    return num1 / num2;
}

//operator+(const Fraction& other)  
//This function adds two fractions together and returns the result as a new fraction object.
Fraction Fraction::operator+(const Fraction& other) const {
    int theNumerator = overflow_Addition(overflow_Multiplication(this->numerator,other.denominator), overflow_Multiplication(other.numerator,this->denominator));
    int theDenominator = overflow_Multiplication(this->denominator, other.denominator);
    reduce(theNumerator, theDenominator);
    return Fraction(theNumerator, theDenominator);
}

//operator-(const Fraction& other)
//This function subtracts one fraction from another and returns the result as a new fraction object.
Fraction Fraction::operator-(const Fraction& other) const {
    int theNumerator = overflow_Subtraction(overflow_Multiplication(this->numerator, other.denominator) ,overflow_Multiplication(other.numerator, this->denominator));
    int theDenominator = overflow_Multiplication(this->denominator, other.denominator);
    reduce(theNumerator, theDenominator);
    return Fraction(theNumerator, theDenominator);
}

//operator*(const Fraction& other)
//This function Thimultiplies two fractions together and returns the result as a new fraction object.
Fraction Fraction::operator*(const Fraction& other) const
{
    int theNumerator =overflow_Multiplication(this->numerator, other.numerator);
    int theDenominator= overflow_Multiplication(this->denominator, other.denominator);
    reduce(theNumerator, theDenominator);
    return Fraction(theNumerator, theDenominator);
    
}

// operator/(const Fraction& other)
// This function divides one fraction by another and returns the result as a new fraction object.
Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) 
    {
        throw runtime_error("Cannot divide by zero!");
    }
    int theNumerator = overflow_Multiplication(this->numerator , other.denominator);
    int theDenominator= overflow_Multiplication(this->denominator, other.numerator);
    reduce(theNumerator, theDenominator);
    return Fraction(theNumerator, theDenominator);
}


//Comparison operations

//operator==(const Fraction& other)
//This function that takes a reference to a Fraction object named other as an argument and returns a boolean value indicating
// whether the current object is equal to the other object. 
bool Fraction::operator==(const Fraction& other) const
{
    // Compare the numerator and denominator of each fraction
    return (this->numerator == other.numerator) && (this->denominator == other.denominator);
}

//operator!=(const Fraction& other)
///This function checks if two fractions are not equal and returns a boolean value.
bool Fraction::operator!=(const Fraction& other) const
{
    return !(*this == other);
}

//operator>(const Fraction& other)
//This function checks if one fraction is greater than another and returns a boolean value.
bool Fraction::operator>(const Fraction& other) const
{
    int num1 = this->numerator * other.denominator;
    int num2 = other.numerator * this->denominator;
    return num1 > num2;
}

//operator<(const Fraction& other)
//This function checks if one fraction is less than another and returns a boolean value.
bool Fraction::operator<(const Fraction& other) const
{
    int num1 = this->numerator * other.denominator;
    int num2 = other.numerator * this->denominator;
    return num1 < num2;
}

//operator>=(const Fraction& other)
//This function checks if one fraction is greater than or equal to another and returns a boolean value.
bool Fraction::operator>=(const Fraction& other) const
{
    return ( (*this > other) || (*this == other) );
}

//operator<=(const Fraction& other)
//This function checks if one fraction is less than or equal to another and returns a boolean value.
bool Fraction::operator<=(const Fraction& other) const
{
    return ( (*this < other) || (*this == other) );
}

// Increment and decrement operations

//operator++() - pre-increment
//This function increments a fraction by adding its denominator to its numerator and returns the result as a new fraction object.
Fraction Fraction::operator++()
{
    this->numerator += this->denominator;
    reduce();
    return *this;
}

//operator++(int) - post-increment 
//This function increments a fraction by adding its denominator to its numerator and returns a copy of the original fraction object.
Fraction Fraction::operator++(int)
{
    Fraction beforeIncrement = *this;
    this->numerator += this->denominator;
    return beforeIncrement;
}

//operator--() - pre-decrement
//This function decrements a fraction by subtracting its denominator from its numerator and returns the result as a new fraction object.
Fraction Fraction::operator--()
{
    this->numerator -= this->denominator;
    reduce();
    return *this;
}

//operator--(int) - post-decrement
//This function ecrements a fraction by subtracting its denominator from its numerator and returns a copy of the original fraction object.
Fraction Fraction::operator--(int)
{
    Fraction beforeDecrement = *this;
    this->numerator -= this->denominator;
    return beforeDecrement;
}

//-------------------------------------------------------------------------------------

// Getter and setter functions

//getNumerator()
int Fraction::getNumerator() const 
{
    return this->numerator;
}

//getDenominator()
int Fraction::getDenominator() const 
{
    return this->denominator;
}

//setNumerator(int numerator) 
void Fraction::setNumerator(int numerator) 
{
    this->numerator = numerator;
}

//setDenominator(int denominator) 
void Fraction::setDenominator(int denominator) 
{
    this->denominator = denominator;
}

//---------------------------------------------------------------

// Friend functions

// operator<<(std::ostream& output, const Fraction& fraction)
//
std::ostream& operator<<(std::ostream& output, const Fraction& fraction)
{
    output << fraction.numerator << "/" << fraction.denominator;
    return output;
}

//operator>>(istream& input, Fraction& fraction)
//
istream& operator>>(istream& input, Fraction& fraction) {
    int theNumerator = 0, theDenominator= 0;

    input >> theNumerator >> theDenominator;

    if (input.fail()) {
        throw std::runtime_error("Invalid input");
    }

    if (theDenominator == 0) {
        throw std::runtime_error("Denominator cannot be zero");
    }

    fraction.setNumerator(theNumerator);
    fraction.setDenominator(theDenominator);
    fraction.reduce();

    return input;
}

//operator+(const float& num, const Fraction& other) 
Fraction operator+(const float& num, const Fraction& other) 
{
        return Fraction(num) + other;
}

//operator+(const Fraction& curr, const float& number) 
Fraction operator+(const Fraction& curr, const float& number) 
{
        return curr + Fraction(number);
}

//operator*(const float& num, const Fraction& other) 
Fraction operator*(const float& num, const Fraction& other) 
{
    return Fraction(num) * other;
}

//operator*(const Fraction& curr, const float& number) 
Fraction operator*(const Fraction& curr, const float& number) 
{
    return curr * Fraction(number);
}

//operator-(const float& num, const Fraction& other) 
Fraction operator-(const float& num, const Fraction& other) 
{
    return Fraction(num) - other;
}

//operator-(const Fraction& curr, const float& number) 
Fraction operator-(const Fraction& curr, const float& number) 
{
    return curr - Fraction(number);
}

// operator/(const float& num1, const Fraction& num2)
Fraction operator/(const float& num1, const Fraction& num2)
{
    if(num2.getNumerator()==0)
    {
        throw runtime_error("Can't divide by zero");
    }
    Fraction f(num1);
    return f / num2;
}

//  operator/(const Fraction& curr, const float& num)
Fraction operator/(const Fraction& curr, const float& num)
{   
    if(num==0)
    {
        throw runtime_error("Can't divide by zero");
    }
    Fraction f(num);
    return curr / f;
}

// operator>=(const float& num, const Fraction& fraction)
bool operator>=(const float& num, const Fraction& fraction) 
{
    return num >= static_cast<float>(fraction);
}

// operator<=(const float& num, const Fraction& fraction)
bool operator<=(const float& num, const Fraction& fraction) 
{
    return num <= static_cast<float>(fraction);
}

// Comparison operator overload for float < Fraction
bool operator<(const float& num, const Fraction& fraction) 
{
    return num < static_cast<float>(fraction);
}

// Comparison operator overload for Fraction < float
bool operator<(const Fraction& fraction, const float& num)
{
    return static_cast<float>(fraction) < num;
}

// Comparison operator overload for Fraction > float
bool operator>(const Fraction& fraction, const float& num) 
{
    return static_cast<float>(fraction) > num;
}

// Comparison operator overload for float > Fraction
bool operator>(const float& num, const Fraction& fraction) 
{
    return num > static_cast<float>(fraction);
}

//operator+=(Fraction& fraction, const Fraction& other) 
Fraction& operator+=(Fraction& fraction, const Fraction& other) 
{
    fraction.numerator = fraction.numerator * other.denominator + other.numerator * fraction.denominator;
    fraction.denominator *= other.denominator;
    fraction.reduce();
    return fraction;
}

//operator+=(Fraction& fraction, const float& num) 
Fraction& operator+=(Fraction& fraction, const float& num) 
{
    Fraction f(num);
    fraction += f;
    return fraction;
}

//-------------------------------------------------------------------------

// Explicit conversion operators
Fraction::operator float() const 
{
    return static_cast<float>(numerator) / static_cast<float>(denominator);
}
Fraction::operator double() const 
{
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}
//--------------------------------


}
   
