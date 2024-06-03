#ifndef MATVEC_MV_EXCEPTION_HPP
#define MATVEC_MV_EXCEPTION_HPP

#include "mv.hpp"

namespace mv{
    
    class base_exception{

        protected :
        template <typename T>
        std::string numToString(const T&);
    
    };


    class failed_to_malloc : public base_exception, public std::runtime_error{

        public :
        failed_to_malloc(const std::string&, size_t);

    };
   

    class failed_to_realloc : public base_exception, public std::runtime_error{

        public :
        failed_to_realloc(const std::string&, const void* const, size_t);

    };


    class over_capacity : public base_exception, public std::runtime_error{

        public :
        over_capacity(const std::string&, size_t, size_t, size_t);
    
    };

}

#include "exception.cpp"

#endif
