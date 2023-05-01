#include "Fraction.hpp"

namespace ariel
{
// constructors
    Fraction::Fraction(int numerator, int denominator)
    {
        if (denominator == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero");
        }

        this->numerator = numerator;
        this->denominator = denominator;
        reduce();
    }

    Fraction::Fraction(float value)
    {
        this->numerator = value * 1000;
        this->denominator = 1000;
        reduce();
    }
    Fraction::Fraction(double value)
    {
        this->numerator = value * 1000;
        this->denominator = 1000;
        reduce();
    }

    Fraction::Fraction()
    {
        numerator = 0;
        denominator = 1;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // methods requier.
    void Fraction::reduce()
    {
        int x = gcd(this->numerator, this->denominator);
        this->numerator = this->numerator / x;
        this->denominator = this->denominator / x;
        if (this->denominator < 0)
        {
            this->numerator = -this->numerator;
            this->denominator = -this->denominator;
        }
    }

    int Fraction::gcd(int num, int den)
    {
        while (den != 0)
        {
            int temp = den;
            den = num % den;
            num = temp;
        }
        return num;
    }

void Fraction::chekOverflow(long numerator, long denominator) const
{
    constexpr long INT_MAX_L = static_cast<long>(std::numeric_limits<int>::max());
    constexpr long INT_MIN_L = static_cast<long>(std::numeric_limits<int>::min());
    
    if (numerator < INT_MIN_L || numerator > INT_MAX_L || denominator < INT_MIN_L || denominator > INT_MAX_L)
    {
        throw std::overflow_error("The numerator or the denominator are too large or small");
    }
}

    // void Fraction ::chekOverflow(long numerator, long denominator) const
    // {
    //     if (denominator < INT_MIN || numerator < INT_MIN || numerator > INT_MAX || denominator > INT_MAX)
    //     {
    //         throw std::overflow_error("The numerator or the denominator are too large or small");
    //     }
    // }

    int Fraction::getNumerator() const
    {
        return numerator;
    }

    int Fraction::getDenominator() const
    {
        return denominator;
    }

    void Fraction::setNumerator(int numerator)
    {
        this->numerator = numerator;
        reduce();
    }

    void Fraction::setDenominator(int denominator)
    {
        if (denominator == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        this->denominator = denominator;
        reduce();
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // + operator
    Fraction Fraction::operator+(const Fraction &other) const
    {
        long longDenominator = (long)denominator * other.denominator;
        long longNumerator = (long)numerator * other.denominator + other.numerator * denominator;
        chekOverflow(longNumerator, longDenominator);
        int newDenominator = denominator * other.denominator;
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator+(const Fraction &fraction, float value)
    {
        Fraction new_fraction((fraction.getNumerator() * 1000) + (value * 1000 * fraction.getDenominator()), 1000);
        new_fraction.denominator = new_fraction.denominator * fraction.denominator;
        new_fraction.reduce();
        return new_fraction;
    }

    Fraction operator+(float value, const Fraction &fraction)
    {

        return fraction + value;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // operator -
    Fraction Fraction::operator-(const Fraction &other) const
    {
        long longDenominator = (long)denominator * other.denominator;
        long longNumerator = (long)numerator * other.denominator - other.numerator * denominator;
        chekOverflow(longNumerator, longDenominator);
        int newDenominator = denominator * other.denominator;
        int newNumerator = numerator * other.denominator - other.numerator * denominator;
        Fraction sub(newNumerator, newDenominator);

        return sub;
    }
    Fraction operator-(const Fraction &fraction, float value)
    {
        Fraction new_fraction(value * 1000, 1000);
        new_fraction.reduce();
        Fraction sub = fraction - new_fraction;
        sub.reduce();
        return sub;
    }

    Fraction operator-(float value, const Fraction &fraction)
    {
        Fraction new_fraction(value * 1000, 1000);
        new_fraction.reduce();
        std::cout << "fraction" << fraction << "\n";
        std::cout << "new_fraction" << new_fraction << "\n";
        Fraction sub = new_fraction - fraction;
        sub.reduce();
        std::cout << "sub" << sub << "\n";

        return sub;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // operator *
    Fraction Fraction::operator*(const Fraction &other) const
    {
        long longDenominator = (long)denominator * other.denominator;
        long longNumerator = (long)numerator * other.numerator;
        chekOverflow(longNumerator, longDenominator);
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }
    Fraction operator*(const Fraction &fraction, float value)
    {
        Fraction new_fraction((fraction.getNumerator()) * (int)(value * 1000), 1000 * fraction.getDenominator());
        new_fraction.reduce();
        return new_fraction;
    }

    Fraction operator*(float value, const Fraction &fraction)
    {

        return fraction * value;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // operator /
    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.numerator == 0)
            throw std::runtime_error("Denominator cannot be zero");

        long longNumerator = (long)numerator * other.denominator;
        long longDenominator = (long)other.numerator * denominator;
        chekOverflow(longNumerator, longDenominator);

        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }
    Fraction operator/(const Fraction &fraction, float value)
    {
        if (value == 0)
            throw std::runtime_error("Denominator cannot be zero");
        Fraction new_fraction(1000, value * 1000);
        new_fraction.reduce();

        return fraction * new_fraction;
    }

    Fraction operator/(float value, const Fraction &fraction)
    {
        Fraction new_value(value * 1000, 1000);
        new_value.reduce();
        Fraction new_fraction(fraction.getDenominator(), fraction.getNumerator());
        return new_value * new_fraction;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // operator ==
    bool Fraction::operator==(const Fraction &other) const
    {
        float num1 = std::round((float)this->numerator / this->denominator * 1000) / 1000;
        float num2 = std::round((float)other.numerator / other.denominator * 1000) / 1000;
        return num1 == num2;
    }

    bool operator==(float value, const Fraction &fraction)
    {
        float num1 = std::round((float)fraction.numerator / fraction.denominator * 1000) / 1000;
        float num2 = std::round(value * 1000) / 1000;
        return num1 == num2;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    //operator !=
     bool operator!=(float value, const Fraction &fraction)
    {

        return fraction != value;
    }
    bool operator!=(const Fraction &fraction, float value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a != value)
            return true;
        return false;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // operator >
    bool Fraction::operator>(const Fraction &other) const
    {
        return numerator * other.denominator > other.numerator * denominator;
    }

    bool operator>(float value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a < value)
            return true;
        return false;
    }

    bool operator>(const Fraction &fraction, float value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();

        if (a > value)
            return true;
        return false;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // operator <
    bool Fraction::operator<(const Fraction &other) const
    {
        return numerator * other.denominator < other.numerator * denominator;
    }
    bool operator<(float value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a > value)
            return true;
        return false;
    }

    bool operator<(const Fraction &fraction, float value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a < value)
            return true;
        return false;
    }
    bool operator<(double value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a > value)
            return true;
        return false;
    }

    bool operator<(const Fraction &fraction, double value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a < value)
            return true;
        return false;
    }
    bool operator<(int value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a > value)
            return true;
        return false;
    }

    bool operator<(const Fraction &fraction, int value)
    {
        float a = (int)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a < value)
            return true;
        return false;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // >= operaotr
    bool Fraction::operator>=(const Fraction &other) const
    {
        return numerator * other.denominator >= other.numerator * denominator;
    }

    bool operator>=(float value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a <= value)
            return true;
        return false;
    }

    bool operator>=(const Fraction &fraction, float value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a >= value)
            return true;
        return false;
    }
    bool operator>=(double value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a <= value)
            return true;
        return false;
    }

    bool operator>=(const Fraction &fraction, double value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a >= value)
            return true;
        return false;
    }
    bool operator>=(int value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a <= value)
            return true;
        return false;
    }

    bool operator>=(const Fraction &fraction, int value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a >= value)
            return true;
        return false;
    }
    ///////////////////////////////////////////////////////////////////////////////////
    //<= operator
    bool Fraction::operator<=(const Fraction &other) const
    {
        return numerator * other.denominator <= other.numerator * denominator;
    }

      bool operator<=(float value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a >= value)
            return true;
        return false;
    }
    bool operator<=(const Fraction &fraction, float value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a <= value)
            return true;
        return false;
    }
    bool operator<=(double value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a >= value)
            return true;
        return false;
    }
    bool operator<=(const Fraction &fraction, double value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a <= value)
            return true;
        return false;
    }
    bool operator<=(int value, const Fraction &fraction)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a >= value)
            return true;
        return false;
    }
    bool operator<=(const Fraction &fraction, int value)
    {
        float a = (float)fraction.getNumerator() / (float)fraction.getDenominator();
        if (a <= value)
            return true;
        return false;
    }
    //
    //increament and decreament operators
    Fraction Fraction::operator++()
    {
        numerator += denominator;
        reduce();
        return *this;
    }

    Fraction Fraction::operator++(int)
    {
        Fraction temp(*this);
        numerator += denominator;
        reduce();
        return temp;
    }

    Fraction Fraction::operator--()
    {
        numerator -= denominator;
        reduce();
        return *this;
    }

    Fraction Fraction::operator--(int)
    {
        Fraction temp(*this);
        numerator -= denominator;
        reduce();
        return temp;
    }

    // input / output operators
    std::ostream &operator<<(std::ostream &outs, const Fraction &fraction)
    {
        outs << fraction.numerator << "/" << fraction.denominator;
        return outs;
    }

    std::istream &operator>>(std::istream &ins, Fraction &fraction)
    {

        int den, num;

        if (ins >> num >> den && den != 0)
        {
            if (den != 0)
            {
                fraction = Fraction(num, den);
            }
        }

        else
        {
            throw std::runtime_error(" input is 1 number");
        }
        return ins;
    }

    // bool operator==(float value, const Fraction& fraction) {
    //     float num1 = std::round((float)fraction.numerator/fraction.denominator *1000)/1000;
    //     float num2 = std::round(value * 1000)/1000;
    //     return num1==num2;

    // }

   
  
}