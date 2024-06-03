#ifndef MATVEC_MV_MAT22_HPP
#define MATVEC_MV_MAT22_HPP

#include "mv.hpp"
#include "vec2.hpp"

namespace mv{

    template <typename T> struct mat22{
        
        union{
            vec2<T> x;
            struct{ T xx; T xy;};
        };
        union{
            vec2<T> y;
            struct{ T yx; T yy;};
        };

        // Constructor & Destructor
        mat22();
        mat22(const T&);
        mat22(const T&, const T&);
        mat22(
            const T&, const T&,
            const T&, const T&
        );
        mat22(const vec2<T>&);
        mat22(const vec2<T>&, const vec2<T>&);
        ~mat22();

        // Constant Functions
        mat22<T> normal() const;
        mat22<T> sym() const;
        mat22<T> alt() const;
        mat22<T> image(T(&)(T)) const;
        mat22<T> image(T(&)(const T&)) const;
        template <typename... A>
        mat22<T> image(T(&)(T, A...), A...) const;
        template <typename... A>
        mat22<T> image(T(&)(const T&, A...), A...) const;
        
        T norm() const;
        T norm(const T&) const;
        T square() const;
        
        void autoPrint() const;

        // Constant Operators
        mat22<T> operator+(const mat22<T>&) const;
        mat22<T> operator-(const mat22<T>&) const;
        mat22<T> operator*(const mat22<T>&) const;    // Hadamard Product
        mat22<T> operator|(const mat22<T>&) const;    // matrix Product
        mat22<T> operator/(const mat22<T>&) const;    // Hadamard Division
        mat22<T> operator%(const mat22<T>&) const;    // Hadamard Modulo
        mat22<T> operator+(const T&) const;
        mat22<T> operator-(const T&) const;
        mat22<T> operator*(const T&) const;
        mat22<T> operator/(const T&) const;
        mat22<T> operator%(const T&) const;
        mat22<T> operator+() const;                   // Identity Mapping 
        mat22<T> operator-() const;                   // Minus Mapping
        mat22<T> operator++(int) const;               // Transpose
        mat22<T> operator~() const;                   // Inverse
        
        vec2<T> operator|(const vec2<T>&) const;      // matrix Product
        T       operator*() const;                    // Hodge Star Operator 
        
        T operator!() const;                          // Determinant
        T operator--(int) const;                      // Trace
        T operator||(const mat22<T>&) const;          // Dot Product
     
        bool operator==(const mat22<T>&) const;
        bool operator!=(const mat22<T>&) const;

        // Altering Functions
        mat22<T>& zero();
        mat22<T>& ident();
        mat22<T>& normalize(); 
        mat22<T>& map(T(&)(T));
        mat22<T>& map(T(&)(const T&));
        template <typename... A>
        mat22<T>& map(T(&)(T, A...), A...);
        template <typename... A>
        mat22<T>& map(T(&)(const T&, A...), A...);

        // Altering Operators
        mat22<T>& operator+=(const mat22<T>&);
        mat22<T>& operator-=(const mat22<T>&);
        mat22<T>& operator*=(const mat22<T>&);
        mat22<T>& operator|=(const mat22<T>&);          // matrix Product
        mat22<T>& operator/=(const mat22<T>&);
        mat22<T>& operator%=(const mat22<T>&);
        mat22<T>& operator+=(const T&);
        mat22<T>& operator-=(const T&);
        mat22<T>& operator*=(const T&);
        mat22<T>& operator/=(const T&);
        mat22<T>& operator%=(const T&); 
        mat22<T>& operator++();                         // Increment
        mat22<T>& operator--();                         // Decrement

        // Specific Type Conversion Operators (at "conversion.cpp")
        tensor<T> operator&(const vec2<T>&) const;      // Wedge Product
        tensor<T> operator&(const mat22<T>&) const;     // Wedge Product
        tensor<T> operator&&(const mat22<T>&) const;    // Dyadic Product
        tensor<T> operator&&(const vec2<T>&) const;     // Dyadic Product
        
        mat<T>  operator()() const;                     // Transform to matrix
    };
}

// General Functions
template <typename T>
std::ostream& operator<<(std::ostream&, const mv::mat22<T>&);

#include "mat22.cpp"
#endif
