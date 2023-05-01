#ifndef FRACTION_HPP
#define FRACTION_HPP

#include "Fraction.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits.h>
#include <stdexcept>

 namespace ariel {

class Fraction {
private:
    int numerator;
    int denominator;
    void reduce();
    int gcd(int num,int den);
public:
    Fraction();
    Fraction(int numerator , int denominator);
    Fraction(double value);
    Fraction(float value);


    int getNumerator() const;
    int getDenominator() const;
    void setNumerator(int numerator);
    void setDenominator(int denominator);
    void chekOverflow(long numerator , long denominator)const;
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;
    bool operator==(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    Fraction operator++(); // pre-increment
    Fraction operator++(int); // post-increment
    Fraction operator--(); // pre-decrement
    Fraction operator--(int); // post-decrement
    friend std::ostream& operator<<(std::ostream& outs, const Fraction& fraction);
    friend std::istream& operator>>(std::istream& ins, Fraction& fraction);
    friend Fraction operator+(const Fraction& fraction, float value);
    friend Fraction operator+(float value, const Fraction& fraction);
    friend Fraction operator-(const Fraction& fraction, float value);
    friend Fraction operator-(float value, const Fraction& fraction);
    friend Fraction operator*(const Fraction& fraction, float value);
    friend Fraction operator*(float value, const Fraction& fraction);
    friend Fraction operator/(const Fraction& fraction, float value);
    friend Fraction operator/(float value, const Fraction& fraction);
    friend bool operator==(float value, const Fraction& fraction);
    friend bool operator!=(float value, const Fraction& fraction);
    friend bool operator!=(const Fraction& fraction,float value);
    friend bool operator>(float value, const Fraction& fraction);
    friend bool operator>(const Fraction& fraction,float value);
   
    friend bool operator<( const Fraction& fraction,float value);
    
    friend bool operator<(float value, const Fraction& fraction);
    friend bool operator<( const Fraction& fraction,double value);
    friend bool operator<(double value, const Fraction& fraction);
    friend bool operator<( const Fraction& fraction,int value);
    friend bool operator<(int value, const Fraction& fraction);
  
    friend bool operator>=( const Fraction& fraction,float value);
    friend bool operator>=(float value, const Fraction& fraction);
    friend bool operator>=( const Fraction& fraction,double value);
    friend bool operator>=(double value, const Fraction& fraction);
    friend bool operator>=(int value, const Fraction& fraction);
    friend bool operator>=( const Fraction& fraction,int value);

    friend bool operator<=(float value, const Fraction& fraction);
    friend bool operator<=( const Fraction& fraction,float value);
    friend bool operator<=(int value, const Fraction& fraction);
    friend bool operator<=( const Fraction& fraction,int value);
    friend bool operator<=( const Fraction& fraction,double value);
    friend bool operator<=(double value, const Fraction& fraction);

    friend std::ostream& operator<<(std::ostream& outs, const ariel::Fraction& fraction);
    friend std::istream& operator>>(std::istream& ins, ariel::Fraction& fraction);


};

}
#endif
