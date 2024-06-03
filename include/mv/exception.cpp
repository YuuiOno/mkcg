#ifndef MATVEC_MV_EXCEPTION_CPP
#define MATVEC_MV_EXCEPTION_CPP

#include "exception.hpp"
#include <sstream>

namespace mv{

    // Base Exception
    template <typename T>
    std::string base_exception::numToString(const T& num_){
        std::stringstream ss1;
        ss1<<num_;

        return ss1.str();
    }

    // Failed to Malloc
    failed_to_malloc::failed_to_malloc(const std::string& str_, size_t size_)
        : std::runtime_error{ std::stringstream{ str_+":  Failed to Malloc. (Requested Size -> "+numToString(size_)+")\n" }.str() }
    {
        
        return;
    }
    
    // Failed to Realloc
    failed_to_realloc::failed_to_realloc(const std::string& str_, const void* const ptr_, size_t size_)
        : std::runtime_error{ std::stringstream{ str_+":  Failed to Realloc. (Pointer -> "+numToString<const void*>(ptr_)+", Requested Size -> "+numToString<size_t>(size_)+")\n" }.str() }
    {

        return;
    }

    // Over Capacity
    over_capacity::over_capacity(const std::string& str_, size_t pos_, size_t capacity_, size_t size_)
        : std::runtime_error{ std::stringstream{ str_+":  Over the Array Capacity. (Requested Position -> "+numToString<size_t>(pos_)+", Capacity -> "+numToString<size_t>(capacity_)+", Array Size -> "+numToString<size_t>(size_)+")\n"}.str() }
    {

    }
}

#endif
