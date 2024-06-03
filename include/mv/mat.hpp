#ifndef MATVEC_MV_MAT_HPP
#define MATVEC_MV_MAT_HPP

#include "mv.hpp"

namespace mv{

    template <typename T> class Mat{

        size_t __row;
        size_t __col;
        size_t __size;
        T*     __elem;

        size_t __capacity;


        //+++++++++++++++++++++++++++//
        //    Protected Functions    //
        //+++++++++++++++++++++++++++//
        // Protected Functions for Inner Operation
        protected :
        template <typename... A>
        void __input(size_t, const T&, A...);
        void __input(size_t);
    
        //++++++++++++++++++++++++//
        //    Public Functions    //
        //++++++++++++++++++++++++//
        public :
        // Constructor & Destructor
        mat();
        mat(size_t, size_t, const T& =0);
        template <typename... A>
        mat(size_t, size_t, A...);
        ~mat();

        // Constant Functions
        mat<T> normal() const;
        mat<T> sym() const;
        mat<T> alt() const;
        mat<T> image(T(&)(T)) const;
        mat<T> image(T(&)(const T&)) const;
        template <typename... A>
        mat<T> image(T(&)(T, A...), A...) const;
        template <typename... A>
        mat<T> image(T(&)(const T&, A...), A...) const;
        
        T norm() const;
        T norm(const T&) const;
        T square() const;
       

        /**************************/
        void autoPrint() const;
        size_t row() const;
        size_t col() const;
        size_t size() const;
        size_t capacity() const;
        const T& operator()(size_t) const;
        T& operator[](size_t);
        //const T& operator()(size_t, size_t);
        /**************************/

        // Constant Operators
        mat<T> operator+(const mat<T>&) const;
        mat<T> operator-(const mat<T>&) const;
        mat<T> operator*(const mat<T>&) const;    // Hadamard Product
        mat<T> operator|(const mat<T>&) const;    // Matrix Product
        mat<T> operator/(const mat<T>&) const;    // Hadamard Division
        mat<T> operator%(const mat<T>&) const;    // Hadamard Modulo
        mat<T> operator+(const T&) const;
        mat<T> operator-(const T&) const;
        mat<T> operator*(const T&) const;
        mat<T> operator/(const T&) const;
        mat<T> operator%(const T&) const;
        mat<T> operator+() const;                   // Identity Mapping 
        mat<T> operator-() const;                   // Minus Mapping
        mat<T> operator++(int) const;               // Transpose
        mat<T> operator~() const;                   // Inverse
        
        vec3<T> operator|(const vec3<T>&) const;      // Matrix Product
        vec3<T> operator*() const;                    // Hodge Star Operator 
        
        T operator!() const;                          // Determinant
        T operator--(int) const;                      // Trace
        T operator||(const mat<T>&) const;          // Dot Product
     
        bool operator==(const mat<T>&) const;
        bool operator!=(const mat<T>&) const;

        // Altering Functions
        mat<T>& zero();
        mat<T>& ident();
        mat<T>& normalize(); 
        mat<T>& map(T(&)(T));
        mat<T>& map(T(&)(const T&));
        template <typename... A>
        mat<T>& map(T(&)(T, A...), A...);
        template <typename... A>
        mat<T>& map(T(&)(const T&, A...), A...);

        // Altering Operators
        mat<T>& operator+=(const mat<T>&);
        mat<T>& operator-=(const mat<T>&);
        mat<T>& operator*=(const mat<T>&);
        mat<T>& operator|=(const mat<T>&);          // Matrix Product
        mat<T>& operator/=(const mat<T>&);
        mat<T>& operator%=(const mat<T>&);
        mat<T>& operator+=(const T&);
        mat<T>& operator-=(const T&);
        mat<T>& operator*=(const T&);
        mat<T>& operator/=(const T&);
        mat<T>& operator%=(const T&); 
        mat<T>& operator++();                         // Increment
        mat<T>& operator--();                         // Decrement

        // Specific Type Conversion Operators (at "conversion.cpp")
        Tensor<T> operator&(const vec3<T>&) const;      // Wedge Product
        Tensor<T> operator&(const mat<T>&) const;     // Wedge Product
        Tensor<T> operator&&(const mat<T>&) const;    // Dyadic Product
        Tensor<T> operator&&(const vec3<T>&) const;     // Dyadic Product
        
        Mat<T>  operator()() const;                     // Transform to Matrix
    };
}

// General Functions
template <typename T>
std::ostream& operator<<(std::ostream&, const mv::mat<T>&);

#include "mat.cpp"
#endif
