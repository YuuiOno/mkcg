#ifndef MATVEC_MV_VEC_HPP
#define MATVEC_MV_VEC_HPP

#include "exception.hpp"
#include "mv.hpp"

namespace mv{
    
    //++++++++++++++++++++//
    //    Vector Class    //
    //++++++++++++++++++++//
    template <typename T> class vec{

        protected :
        size_t _size;
        size_t _capacity;
        T*     _elem;

        static size_t        _num;
        static temp::vec<T>* _vecs;


        //---------------------//
        // Protected Functions //
        //---------------------//
        protected :
        // For Inner Operations
        template <typename... A>
        void     _input(size_t, const T&, A...);
        void     _input(size_t);
            
        temp::vec<T>& _find_free(size_t);

        //------------------//
        // Public Functions //
        //------------------//
        public :
        // Constructor & Destructor
        vec();
        vec(const vec<T>&);
        vec(temp::vec<T>&);
        vec(size_t, const T& =0);
        template <typename... A>
        vec(size_t, A...);
        ~vec();


        // Access or Controle Functions
        size_t   size()             const;
        size_t   capacity()         const;
        size_t   num()              const;
        
        vec<T>&  auto_print();

        T&       operator[](size_t);
        T* const elem();

        void release_temp();               // Release the Temporary Vector Array
        void resize(size_t);               // Resize the Vector Length
        void resize(size_t, const T&);     // Resize the Vector Length
        void reserve(size_t);              // Reserve the Vector Length
        T&   push_back(const T&);          // Push Back a Scholar Value


        // Sub Constant Functions
        temp::vec<T> normaxl();
        temp::vec<T> image(T(&)(T));
        temp::vec<T> image(T(&)(const T&));
        template <typename... A>
        temp::vec<T> image(T(&)(T, A...), A...);
        template <typename... A>
        temp::vec<T> image(T(&)(const T&, A...), A...);
        
        T norm() const;
        T norm(const T&) const;
        T square() const;
/*       

        //++++++++++++++++++++++++//
        size_t row() const;
        size_t col() const;
        size_t size() const;
        size_t capacity() const;
        const T& operator()(size_t) const;
        T& operator[](size_t);
        //const T& operator()(size_t, size_t);
        //+++++++++++++++++++++++++//

        // Constant Operators
        vec<T> operator+(const vec<T>&) const;
        vec<T> operator-(const vec<T>&) const;
        vec<T> operator*(const vec<T>&) const;    // Hadamard Product
        vec<T> operator|(const vec<T>&) const;    // Matrix Product
        vec<T> operator/(const vec<T>&) const;    // Hadamard Division
        vec<T> operator%(const vec<T>&) const;    // Hadamard Modulo
        vec<T> operator+(const T&) const;
        vec<T> operator-(const T&) const;
        vec<T> operator*(const T&) const;
        vec<T> operator/(const T&) const;
        vec<T> operator%(const T&) const;
        vec<T> operator+() const;                   // Identity Mapping 
        vec<T> operator-() const;                   // Minus Mapping
        vec<T> operator++(int) const;               // Transpose
        vec<T> operator~() const;                   // Inverse
        
        vec3<T> operator|(const vec3<T>&) const;      // Matrix Product
        vec3<T> operator*() const;                    // Hodge Star Operator 
        
        T operator!() const;                          // Determinant
        T operator--(int) const;                      // Trace
        T operator||(const vec<T>&) const;          // Dot Product
     
        bool operator==(const vec<T>&) const;
        bool operator!=(const vec<T>&) const;

        // Altering Functions
        vec<T>& zero();
        vec<T>& ident();
        vec<T>& normalize(); 
        vec<T>& map(T(&)(T));
        vec<T>& map(T(&)(const T&));
        template <typename... A>
        vec<T>& map(T(&)(T, A...), A...);
        template <typename... A>
        vec<T>& map(T(&)(const T&, A...), A...);

        // Altering Operators
        vec<T>& operator+=(const vec<T>&);
        vec<T>& operator-=(const vec<T>&);
        vec<T>& operator*=(const vec<T>&);
        vec<T>& operator|=(const vec<T>&);          // Matrix Product
        vec<T>& operator/=(const vec<T>&);
        vec<T>& operator%=(const vec<T>&);
        vec<T>& operator+=(const T&);
        vec<T>& operator-=(const T&);
        vec<T>& operator*=(const T&);
        vec<T>& operator/=(const T&);
        vec<T>& operator%=(const T&); 
        vec<T>& operator++();                         // Increment
        vec<T>& operator--();                         // Decrement

        // Specific Type Conversion Operators (at "conversion.cpp")
        Tensor<T> operator&(const vec3<T>&) const;      // Wedge Product
        Tensor<T> operator&(const vec<T>&) const;     // Wedge Product
        Tensor<T> operator&&(const vec<T>&) const;    // Dyadic Product
        Tensor<T> operator&&(const vec3<T>&) const;     // Dyadic Product
        
        Mat<T>  operator()() const;                     // Transform to Matrix
    */
    };
    template <typename T> size_t        vec<T>::_num  =0;
    template <typename T> temp::vec<T>* vec<T>::_vecs=reinterpret_cast<temp::vec<T>*>(std::malloc(0));
}


namespace mv{
    
    //++++++++++++++++++++++++++++++//
    //    Temporary Vector Class    //
    //++++++++++++++++++++++++++++++//
    template <typename T> class temp::vec : public mv::vec<T>{

        bool _flag;
        
        public :
        // Constructor & Destructor
        vec(bool);

        // Altering Function
        bool turn();
           
        // Access or Controle Function
        temp::vec<T>& auto_print();

        // Sub Constant Functions
        temp::vec<T>& image(T(&)(T));
        temp::vec<T>& image(T(&)(const T&));
        template <typename... A>
        temp::vec<T>& image(T(&)(T, A...), A...);
        template <typename... A>
        temp::vec<T>& image(T(&)(const T&, A...), A...);
        
/*
        //+++++++++++++++++++++++++++//
        //    Protected Functions    //
        //+++++++++++++++++++++++++++//
        // Protected Functions for Inner Operation
        protected :
        template <typename... A>
        void _input(size_t, const T&, A...);
        void _input(size_t);
    
        //++++++++++++++++++++++++//
        //    Public Functions    //
        //++++++++++++++++++++++++//
        public :
        // Constructor & Destructor
        vec();
        vec(size_t, const T& =0);
        template <typename... A>
        vec(size_t, A...);
        ~vec();

        // 

        // Constant Functions
        vec<T> normal() const;
        vec<T> image(T(&)(T)) const;
        vec<T> image(T(&)(const T&)) const;
        template <typename... A>
        vec<T> image(T(&)(T, A...), A...) const;
        template <typename... A>
        vec<T> image(T(&)(const T&, A...), A...) const;
        
        T norm() const;
        T norm(const T&) const;
        T square() const;
       

        //+++++++++++++++++++++++//
        void autoPrint() const;
        size_t row() const;
        size_t col() const;
        size_t size() const;
        size_t capacity() const;
        const T& operator()(size_t) const;
        T& operator[](size_t);
        //const T& operator()(size_t, size_t);
        //+++++++++++++++++++++++//

        // Constant Operators
        vec<T> operator+(const vec<T>&) const;
        vec<T> operator-(const vec<T>&) const;
        vec<T> operator*(const vec<T>&) const;    // Hadamard Product
        vec<T> operator|(const vec<T>&) const;    // Matrix Product
        vec<T> operator/(const vec<T>&) const;    // Hadamard Division
        vec<T> operator%(const vec<T>&) const;    // Hadamard Modulo
        vec<T> operator+(const T&) const;
        vec<T> operator-(const T&) const;
        vec<T> operator*(const T&) const;
        vec<T> operator/(const T&) const;
        vec<T> operator%(const T&) const;
        vec<T> operator+() const;                   // Identity Mapping 
        vec<T> operator-() const;                   // Minus Mapping
        vec<T> operator++(int) const;               // Transpose
        vec<T> operator~() const;                   // Inverse
        
        vec3<T> operator|(const vec3<T>&) const;      // Matrix Product
        vec3<T> operator*() const;                    // Hodge Star Operator 
        
        T operator!() const;                          // Determinant
        T operator--(int) const;                      // Trace
        T operator||(const vec<T>&) const;          // Dot Product
     
        bool operator==(const vec<T>&) const;
        bool operator!=(const vec<T>&) const;

        // Altering Functions
        vec<T>& zero();
        vec<T>& ident();
        vec<T>& normalize(); 
        vec<T>& map(T(&)(T));
        vec<T>& map(T(&)(const T&));
        template <typename... A>
        vec<T>& map(T(&)(T, A...), A...);
        template <typename... A>
        vec<T>& map(T(&)(const T&, A...), A...);

        // Altering Operators
        vec<T>& operator+=(const vec<T>&);
        vec<T>& operator-=(const vec<T>&);
        vec<T>& operator*=(const vec<T>&);
        vec<T>& operator|=(const vec<T>&);          // Matrix Product
        vec<T>& operator/=(const vec<T>&);
        vec<T>& operator%=(const vec<T>&);
        vec<T>& operator+=(const T&);
        vec<T>& operator-=(const T&);
        vec<T>& operator*=(const T&);
        vec<T>& operator/=(const T&);
        vec<T>& operator%=(const T&); 
        vec<T>& operator++();                         // Increment
        vec<T>& operator--();                         // Decrement

        // Specific Type Conversion Operators (at "conversion.cpp")
        Tensor<T> operator&(const vec3<T>&) const;      // Wedge Product
        Tensor<T> operator&(const vec<T>&) const;     // Wedge Product
        Tensor<T> operator&&(const vec<T>&) const;    // Dyadic Product
        Tensor<T> operator&&(const vec3<T>&) const;     // Dyadic Product
        
        Mat<T>  operator()() const;                     // Transform to Matrix
        */
    };
}

// General Functions
template <typename T>
std::ostream& operator<<(std::ostream&, const mv::vec<T>&);

#include "vec.cpp"
#endif
