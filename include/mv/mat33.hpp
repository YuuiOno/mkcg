#ifndef MATVEC_MV_MAT33_HPP
#define MATVEC_MV_MAT33_HPP

#include "mv.hpp"
#include "vec3.hpp"

namespace mv{

    template <typename T> struct mat33{
        
        union{
            vec3<T> x;
            struct{ T xx; T xy; T xz; };
        };
        union{
            vec3<T> y;
            struct{ T yx; T yy; T yz; };
        };
        union{
            vec3<T> z;
            struct{ T zx; T zy; T zz; };
        };

        // Constructor & Destructor
        mat33();
        mat33(const T&);
        mat33(const T&, const T&, const T&);
        mat33(
            const T&, const T&, const T&,
            const T&, const T&, const T&,
            const T&, const T&, const T&
        );
        mat33(const vec3<T>&);
        mat33(const vec3<T>&, const vec3<T>&, const vec3<T>&);
        ~mat33();

        // Constant Functions
        mat33<T> normal() const;
        mat33<T> sym() const;
        mat33<T> alt() const;
        mat33<T> image(T(&)(T)) const;
        mat33<T> image(T(&)(const T&)) const;
        template <typename... A>
        mat33<T> image(T(&)(T, A...), A...) const;
        template <typename... A>
        mat33<T> image(T(&)(const T&, A...), A...) const;
        
        T norm() const;
        T norm(const T&) const;
        T square() const;
        
        void autoPrint() const;

        // Constant Operators
        mat33<T> operator+(const mat33<T>&) const;
        mat33<T> operator-(const mat33<T>&) const;
        mat33<T> operator*(const mat33<T>&) const;    // Hadamard Product
        mat33<T> operator|(const mat33<T>&) const;    // matrix Product
        mat33<T> operator/(const mat33<T>&) const;    // Hadamard Division
        mat33<T> operator%(const mat33<T>&) const;    // Hadamard Modulo
        mat33<T> operator+(const T&) const;
        mat33<T> operator-(const T&) const;
        mat33<T> operator*(const T&) const;
        mat33<T> operator/(const T&) const;
        mat33<T> operator%(const T&) const;
        mat33<T> operator+() const;                   // Identity Mapping 
        mat33<T> operator-() const;                   // Minus Mapping
        mat33<T> operator++(int) const;               // Transpose
        mat33<T> operator~() const;                   // Inverse
        
        vec3<T> operator|(const vec3<T>&) const;      // matrix Product
        vec3<T> operator*() const;                    // Hodge Star Operator 
        
        T operator!() const;                          // Determinant
        T operator--(int) const;                      // Trace
        T operator||(const mat33<T>&) const;          // Dot Product
     
        bool operator==(const mat33<T>&) const;
        bool operator!=(const mat33<T>&) const;

        // Altering Functions
        mat33<T>& zero();
        mat33<T>& ident();
        mat33<T>& normalize(); 
        mat33<T>& map(T(&)(T));
        mat33<T>& map(T(&)(const T&));
        template <typename... A>
        mat33<T>& map(T(&)(T, A...), A...);
        template <typename... A>
        mat33<T>& map(T(&)(const T&, A...), A...);

        // Altering Operators
        mat33<T>& operator+=(const mat33<T>&);
        mat33<T>& operator-=(const mat33<T>&);
        mat33<T>& operator*=(const mat33<T>&);
        mat33<T>& operator|=(const mat33<T>&);          // matrix Product
        mat33<T>& operator/=(const mat33<T>&);
        mat33<T>& operator%=(const mat33<T>&);
        mat33<T>& operator+=(const T&);
        mat33<T>& operator-=(const T&);
        mat33<T>& operator*=(const T&);
        mat33<T>& operator/=(const T&);
        mat33<T>& operator%=(const T&); 
        mat33<T>& operator++();                         // Increment
        mat33<T>& operator--();                         // Decrement

        // Specific Type Conversion Operators (at "conversion.cpp")
        tensor<T> operator&(const vec3<T>&) const;      // Wedge Product
        tensor<T> operator&(const mat33<T>&) const;     // Wedge Product
        tensor<T> operator&&(const mat33<T>&) const;    // Dyadic Product
        tensor<T> operator&&(const vec3<T>&) const;     // Dyadic Product
        
        mat<T>  operator()() const;                     // Transform to matrix
    };
}

// General Functions
template <typename T>
std::ostream& operator<<(std::ostream&, const mv::mat33<T>&);

#include "mat33.cpp"
#endif
