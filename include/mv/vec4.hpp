#ifndef MATVEC_MV_VEC4_HPP
#define MATVEC_MV_VEC4_HPP

#include "mv.hpp"
#include "vec3.hpp"

namespace mv{

    template <typename T> struct vec4{
		
        union{
            vec3<T> xyz;
            struct{ T x; T y; T z; };
        };
        T w;
        vec4(void)
            : x{0}
            , y{0}
            , z{0}
            , w{0}
        {
        }

        vec4(const T& _sca1, const T& _sca2, const T& _sca3, const T& _sca4){
            x=_sca1;
            y=_sca2;
            z=_sca3;
            w=_sca4;
        }
        ~vec4(){

        }
/*
        // Constructor & Destructor
        vec3();
        vec3(const T&);
        vec3(const T&, const T&, const T&);
        ~vec3();

        // Constant Functions
        vec3<T> normal() const;
        vec3<T> image(T(&)(T)) const;
        vec3<T> image(T(&)(const T&)) const;
        template <typename... A>
        vec3<T> image(T(&)(T, A...), A...) const;
        template <typename... A>
        vec3<T> image(T(&)(const T&, A...), A...) const;
        
        T norm() const;
        T norm(const T&) const;
        T square() const;
        
        void autoPrint() const;

        // Constant Operators
        vec3<T> operator+(const vec3<T>&) const;
        vec3<T> operator-(const vec3<T>&) const;
        vec3<T> operator*(const vec3<T>&) const;   // Hadamard Product
        vec3<T> operator/(const vec3<T>&) const;   // Hadamard Division
        vec3<T> operator%(const vec3<T>&) const;   // Hadamard Modulo
        vec3<T> operator+(const T&) const;
        vec3<T> operator-(const T&) const;
        vec3<T> operator*(const T&) const;
        vec3<T> operator/(const T&) const;
        vec3<T> operator%(const T&) const;
        vec3<T> operator+() const;                 // Identity Mapping 
        vec3<T> operator-() const;                 // Minus Mapping
        vec3<T> operator~() const;                 // Inverse
        
        T operator!() const;                       // Volume
        T operator--(int) const;                   // Trace
        T operator||(const vec3<T>&) const;        // Dot Product
        
        bool operator==(const vec3<T>&) const;
        bool operator!=(const vec3<T>&) const;

        // Altering Functions
        vec3<T>& zero();
        vec3<T>& ident();
        vec3<T>& normalize(); 
        vec3<T>& map(T(&)(T));
        vec3<T>& map(T(&)(const T&));
        template <typename... A>
        vec3<T>& map(T(&)(T, A...), A...);
        template <typename... A>
        vec3<T>& map(T(&)(const T&, A...), A...);

        // Altering Operators
        vec3<T>& operator+=(const vec3<T>&);
        vec3<T>& operator-=(const vec3<T>&);
        vec3<T>& operator*=(const vec3<T>&);
        vec3<T>& operator/=(const vec3<T>&);
        vec3<T>& operator%=(const vec3<T>&);
        vec3<T>& operator+=(const T&);
        vec3<T>& operator-=(const T&);
        vec3<T>& operator*=(const T&);
        vec3<T>& operator/=(const T&);
        vec3<T>& operator%=(const T&); 
        vec3<T>& operator++();                        // Increment
        vec3<T>& operator--();                        // Decrement

        // Specific Type Conversion Operators (at "conversion.cpp")
        vec3(const vec2<T>&, const T&);
        vec3(const T&, const vec2<T>&);
        vec2<T> xy() const;
        vec2<T> xz() const;
        vec2<T> yx() const;
        vec2<T> yz() const;
        vec2<T> zx() const;
        vec2<T> zy() const;
        
        mat33<T> operator&(const vec3<T>&) const;     // Wedge Product
        mat33<T> operator&&(const vec3<T>&) const;    // Dyadic Product
      
        vec3(const Mat<T>&);
        Mat<T> operator++(int) const;                 // Transpose
        Mat<T> operator()() const;                    // Transform to Matrix
*/
     };
}
/*
// General Functions
template <typename T>
std::ostream& operator<<(std::ostream&, const mv::vec3<T>&);
*/
//#include "vec4.cpp"

#endif
