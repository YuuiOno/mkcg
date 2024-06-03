#ifndef MV_GVEC_HPP
#define MV_GVEC_HPP

#include "forward.hpp"

//#include <cstddef>
//#include <initializer_list>
#include <iostream>

//======================//
//    namespace : mv    //
//======================//
namespace mv{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    mv::gvec<T, N> structure template     )//
    template <typename T, size_t N>
    struct gvec{
        
        //+    Member Variable    +//
        T v[N];


        //+    Member Function    +//
        //_ Constructor
             gvec      (void)                     noexcept         =default;
             gvec      (std::initializer_list<T>) noexcept;
        auto construct (std::initializer_list<T>) noexcept -> gvec&;
        
        //_ Destructor
             ~gvec     (void) noexcept          =default;
        auto  destruct (void) noexcept -> gvec&;
        
        //_ Writer
        void print (std::ostream&) const noexcept;
        void write (std::ostream&) const noexcept;

        //_ Reader
        void scan (std::istream&) noexcept;
        void read (std::istream&) noexcept;

        //_ Constant Unary Operator
        auto operator+  (void) const noexcept -> gvec<decltype(+std::declval<T>()), N>;
        auto operator-  (void) const noexcept -> gvec<decltype(-std::declval<T>()), N>;
        auto operator~  (void) const noexcept -> gvec<decltype(~std::declval<T>()), N>;
        auto operator!  (void) const noexcept -> gvec<decltype(!std::declval<T>()), N>;

        //_ Destructive Unary Operator
        //auto operator++ (void) noexcept -> gvec<decltype(++(std::declval<T>())), N>;
        auto operator++ (int)  noexcept -> gvec<decltype(std::declval<T>().operator++()), N>;
        //auto operator-- (void) noexcept -> gvec<decltype(--(std::declval<T>())), N>;
        //auto operator-- (int)  noexcept -> gvec<decltype(std::declval<T>()--), N>;
    
        //_ Constant Binary Operator
        /*
        template <typename U> auto operator== (const U&)          noexcept -> gvec<decltype(std::declval<T>()==std::declval<U>()), N>;
        template <typename U> auto operator== (const gvec<U, N>&) noexcept -> gvec<decltype(std::declval<T>()==std::declval<U>()), N>;
        template <typename U> auto operator!= (const U&)          noexcept -> gvec<decltype(std::declval<T>()!=std::declval<U>()), N>;
        template <typename U> auto operator!= (const gvec<U, N>&) noexcept -> gvec<decltype(std::declval<T>()!=std::declval<U>()), N>;
        template <typename U> auto operator<  (const U&)          noexcept -> gvec<decltype(std::declval<T>()<std::declval<U>()), N>;
        template <typename U> auto operator<  (const gvec<U, N>&) noexcept -> gvec<decltype(std::declval<T>()<std::declval<U>()), N>;
        template <typename U> auto operator<= (const U&)          noexcept -> gvec<decltype(std::declval<T>()<=std::declval<U>()), N>;
        template <typename U> auto operator<= (const gvec<U, N>&) noexcept -> gvec<decltype(std::declval<T>()<=std::declval<U>()), N>;
        template <typename U> auto operator>  (const U&)          noexcept -> gvec<decltype(std::declval<T>()>std::declval<U>()), N>;
        template <typename U> auto operator>  (const gvec<U, N>&) noexcept -> gvec<decltype(std::declval<T>()>std::declval<U>()), N>;
        template <typename U> auto operator>= (const U&)          noexcept -> gvec<decltype(std::declval<T>()>=std::declval<U>()), N>;
        template <typename U> auto operator>= (const gvec<U, N>&) noexcept -> gvec<decltype(std::declval<T>()>=std::declval<U>()), N>;
        */
    };

    template <size_t N>
    struct gvec<null, N>{
        static_assert(true, "Kaaa");        
    };
    
    template <typename T, size_t N>
    gvec<T,N>::gvec (std::initializer_list<T> lst_) noexcept
    {
        for(size_t a=0; a<N and a<lst_.size(); ++a) v[a]=*(lst_.begin()+a);    
        for(size_t a=lst_.size(); a<N; ++a)         v[a]=*(lst_.end()-1);
        
        return;
    }

};
#endif
