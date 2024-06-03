#ifndef MATVEC_MV_VECN_HPP
#define MATVEC_MV_VECN_HPP
#include <type_traits>
#include "mv.hpp"


namespace mv{

    template <typename T, size_t N>
    class vecn{
		
        T cmp[N];

        public :
        // Constructor & Destructor
        vecn(void);
        vecn(const T&);
        vecn(const std::initializer_list<T>&);
        vecn(const vecn<T,N>&);
        ~vecn(void);

        // Access Function
        size_t   dim(void) const; 
        T&       operator[](size_t);
        const T& operator()(size_t) const;

        // Constant Functions
        vecn<T,N> normal(void) const;
        vecn<T,N> image(T(&)(T)) const;
        vecn<T,N> image(T(&)(const T&)) const;
        template <typename... A>
        vecn<T,N> image(T(&)(T, A...), A...) const;
        template <typename... A>
        vecn<T,N> image(T(&)(const T&, A...), A...) const;
        
        T norm(void) const;
        T norm(const T&) const;
        T square(void) const;
        
        void autoPrint(void) const;

        // Constant Operators
        vecn<T,N> operator+(const vecn<T,N>&) const;
        vecn<T,N> operator-(const vecn<T,N>&) const;
        vecn<T,N> operator*(const vecn<T,N>&) const;   // Hadamard Product
        vecn<T,N> operator/(const vecn<T,N>&) const;   // Hadamard Division
        vecn<T,N> operator%(const vecn<T,N>&) const;   // Hadamard Modulo
        vecn<T,N> operator+(const T&) const;
        vecn<T,N> operator-(const T&) const;
        vecn<T,N> operator*(const T&) const;
        vecn<T,N> operator/(const T&) const;
        vecn<T,N> operator%(const T&) const;
        vecn<T,N> operator+(void) const;             // Identity Mapping 
        vecn<T,N> operator-(void) const;             // Minus Mapping
        vecn<T,N> operator~(void) const;             // Inverse
        
        T operator!(void) const;                     // Volume
        T operator--(int) const;                     // Trace
        T operator||(const vecn<T,N>&) const;        // Dot Product
        
        bool operator==(const vecn<T,N>&) const;
        bool operator!=(const vecn<T,N>&) const;

        // Altering Functions
        vecn<T,N>& zero(void);
        vecn<T,N>& ident(void);
        vecn<T,N>& normalize(void); 
        vecn<T,N>& map(T(&)(T));
        vecn<T,N>& map(T(&)(const T&));
        template <typename... A>
        vecn<T,N>& map(T(&)(T, A...), A...);
        template <typename... A>
        vecn<T,N>& map(T(&)(const T&, A...), A...);

        // Altering Operators
        vecn<T,N>& operator+=(const vecn<T,N>&);
        vecn<T,N>& operator-=(const vecn<T,N>&);
        vecn<T,N>& operator*=(const vecn<T,N>&);
        vecn<T,N>& operator/=(const vecn<T,N>&);
        vecn<T,N>& operator%=(const vecn<T,N>&);
        vecn<T,N>& operator+=(const T&);
        vecn<T,N>& operator-=(const T&);
        vecn<T,N>& operator*=(const T&);
        vecn<T,N>& operator/=(const T&);
        vecn<T,N>& operator%=(const T&); 
        vecn<T,N>& operator++(void);                    // Increment
        vecn<T,N>& operator--(void);                    // Decrement

        // Specific Type Conversion Operators (at "conversion.cpp")
        //mat33<T> operator^(const vecn<T,N>&) const;     // Wedge Product
        //mat33<T> operator&&(const vecn<T,N>&) const;    // Dyadic Product
      
        //vecn(const mat<T>&);
        //matm,<T> operator++(int) const;                 // Transpose
        //matnm<T> operator(void)() const;                // Transform to matrix

     };
}

// General Functions
template <typename T, size_t N>
std::ostream& operator<<(std::ostream&, const mv::vecn<T,N>&);

#include "vecn.cpp"

#endif
