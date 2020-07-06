#pragma once
#include <Common/Structs.h>

#include <stdexcept>

namespace NGeometry
{
    template<class Type1, class Type2>
    bool equal(const Type1& i_el1, const Type2& i_el2)
    {
        auto eps = std::min(std::numeric_limits<Type1>::epsilon(),
                            std::numeric_limits<Type2>::epsilon());
        return std::abs(i_el1 - i_el2) < eps;
    }
    template<int Size>
    class Point : public std::array<double, Size>
    {
    public:
        Point() = default;
        Point(const std::array<double, Size>& i_values);
        explicit Point(const std::vector<double>& i_values);
        Point(const Point&) = default;
        using BaseClass = std::array<double, Size>;
        double length() const;
        double lenSqr() const;
        Point operator+(const Point& i_point) const;
        Point operator-(const Point& i_point) const;
        Point operator*(double i_coef) const;
        Point operator/(double i_coef) const;
        double operator*(const Point& i_point) const;
        Point operator-() const;
        Point operator+(double i_value) const;
        void normalize();
    };
    template<int Size>
    Point<Size>::Point(const std::array<double, Size>& i_values) :
        BaseClass(i_values)
    {
    }
    template<int Size>
    Point<Size>::Point(const std::vector<double>& i_values)
    {
        BaseClass::fill(0.);
        for (int i = 0; i < Size && i < i_values.size(); ++i)
            BaseClass::operator[](i) = i_values[i];
    }

    template<int Size>
    double Point<Size>::length() const
    {
        return sqrt(this->lenSqr());
    }
    template<int Size>
    double Point<Size>::lenSqr() const
    {
        return (*this) * (*this);
    }
    template<int Size>
    Point<Size> Point<Size>::operator+(const Point<Size>& i_point) const
    {
        Point<Size> answer;
        for (int i = 0; i < Size; ++i)
            answer[i] = BaseClass::operator[](i) + i_point[i];
        return answer;
    }
    template<int Size>
    Point<Size> Point<Size>::operator-(const Point<Size>& i_point) const
    {
        Point<Size> answer;
        for (int i = 0; i < Size; ++i)
            answer[i] = BaseClass::operator[](i) - i_point[i];
        return answer;
    }
    template<int Size>
    Point<Size> Point<Size>::operator*(double i_coef) const
    {
        Point<Size> answer;
        for (int i = 0; i < Size; ++i)
            answer[i] = BaseClass::operator[](i) * i_coef;
        return answer;
    }
    template<int Size>
    Point<Size> Point<Size>::operator/(double i_coef) const
    {
        if (equal(i_coef, double{}))
            throw std::runtime_error("divide by zero");
        return (*this) * (1. / i_coef);
    }
    template<int Size>
    double Point<Size>::operator*(const Point& i_point) const
    {
        double sum = 0.;
        for (int i = 0; i < Size; ++i)
            sum += i_point[i] * BaseClass::operator[](i);
        return sum;
    }
    template<int Size>
    Point<Size> Point<Size>::operator-() const
    {
        // make norm;
        return Point<Size>{} - *this;
    }
    template<int Size>
    Point<Size> Point<Size>::operator+(double i_value) const
    {
        Point<Size> answer = *this;
        for (int i = 0; i < Size; ++i)
            answer[i] += i_value;
        return answer;
    }
    template<int Size>
    void Point<Size>::normalize()
    {
        if (equal(this->lenSqr(), 0.))
            return;
        *this = *this / this->length();
    }

    using Point2 = Point<2>;
    using Point3 = Point<3>;
}