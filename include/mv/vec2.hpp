#ifndef MATVEC_MV_VEC2_HPP
#define MATVEC_MV_VEC2_HPP

#include "mv.hpp"

namespace mv{

    template <typename T> struct vec2{
		
        T x;
		T y;

        // Constructor & Destructor
        vec2();
        vec2(const T&);
        vec2(const T&, const T&);
        ~vec2();

        // Constant Functions(vec2<T>)
        vec2<T> normal() const;
        vec2<T> image(T(&)(T)) const;
        vec2<T> image(T(&)(const T&)) const;
        template <typename... A>
        vec2<T> image(T(&)(T, A...), A...) const;
        template <typename... A>
        vec2<T> image(T(&)(const T&, A...), A...) const;
        
        // Constant Functions(T)
        T norm() const;
        T norm(const T&) const;
        T square() const;
        
        // Constant Functions(void)
        void autoPrint() const;
       
        // Constant Operators(vec2<T>)
        vec2<T> operator+(const vec2<T>&) const;
        vec2<T> operator-(const vec2<T>&) const;
        vec2<T> operator*(const vec2<T>&) const;   // Hadamard Product
        vec2<T> operator/(const vec2<T>&) const;   // Hadamard Division
        vec2<T> operator%(const vec2<T>&) const;   // Hadamard Modulo
        vec2<T> operator+(const T&) const;
        vec2<T> operator-(const T&) const;
        vec2<T> operator*(const T&) const;
        vec2<T> operator/(const T&) const;
        vec2<T> operator%(const T&) const;
        vec2<T> operator+() const;                 // Identity Mapping 
        vec2<T> operator-() const;                 // Minus Mapping
        vec2<T> operator~() const;                 // Inverse
        
        // Constant Operators(T)
        T operator!() const;                       // Area
        T operator--(int) const;                   // Trace
        T operator||(const vec2<T>&) const;        // Dot Product
        T operator<<(const vec2<T>&) const;        // Left Outer Product
        T operator>>(const vec2<T>&) const;        // Right Outer Product
        
        // Constant Operators(bool)
        bool operator==(const vec2<T>&) const;
        bool operator!=(const vec2<T>&) const;

        // Altering Functions(vec2<T>&)
        vec2<T>& zero();
        vec2<T>& ident();
        vec2<T>& normalize();
        
        vec2<T>& map(T(&)(T));
        vec2<T>& map(T(&)(const T&));
        template <typename... A>
        vec2<T>& map(T(&)(T, A...), A...);
        template <typename... A>
        vec2<T>& map(T(&)(const T&, A...), A...);

        // Altering Operators(vec2<T>&)
        vec2<T>& operator+=(const vec2<T>&);
        vec2<T>& operator-=(const vec2<T>&);
        vec2<T>& operator*=(const vec2<T>&);
        vec2<T>& operator/=(const vec2<T>&);
        vec2<T>& operator%=(const vec2<T>&);
        vec2<T>& operator+=(const T&);
        vec2<T>& operator-=(const T&);
        vec2<T>& operator*=(const T&);
        vec2<T>& operator/=(const T&);
        vec2<T>& operator%=(const T&); 
        vec2<T>& operator++();                        // Increment
        vec2<T>& operator--();                        // Decrement

        // Specific Type Conversion Operators (at "conversion.cpp")
        mat22<T> operator^(const vec2<T>&) const;     // Wedge Product
        mat22<T> operator&&(const vec2<T>&) const;    // Dyadic Product

        mat<T>   operator++(int) const;               // Transpose
        mat<T>   operator()() const;                  // Transform to matrix
    };
}

// General Functions
template <typename T>
std::ostream& operator<<(std::ostream&, const mv::vec2<T>&);
template <typename T>
std::istream& operator>>(std::istream&, const mv::vec2<T>&);
template <typename T, typename U>
mv::vec2<U> matvec_cast(const mv::vec2<T>&);

#include "vec2.cpp"

#endif
