#ifndef MATVEC_MV_CONVERT_CPP
#define MATVEC_MV_CONVERT_CPP

#include "mv.hpp"

namespace mv{
    
    // VEC2 & VEC3
    #if defined(MATVEC_MV_VEC2_HPP) && defined(MATVEC_MV_VEC3_HPP)
    // -> VEC3
    template <typename T>
    vec3<T>::vec3(const vec2<T>& _v2, const T& _sca)
        : x(_v2.x)
        , y(_v2.y)
        , z(_sca)
    {

    }
        
    template <typename T>
    vec3<T>::vec3(const T& _sca, const vec2<T>& _v2)
        : x(_sca)
        , y(_v2.x)
        , z(_v2.y)
    {

    }
        
    template <typename T>
    vec2<T> vec3<T>::xy() const{

        return {x, y};
    }

    template <typename T>
    vec2<T> vec3<T>::xz() const{

        return {x, z};
    }

    template <typename T>
    vec2<T> vec3<T>::yx() const{

        return {y, x};
    }

    template <typename T>
    vec2<T> vec3<T>::yz() const{

        return {y, z};
    }

    template <typename T>
    vec2<T> vec3<T>::zx() const{

            return {z, x};
        }

    template <typename T>
    vec2<T> vec3<T>::zy() const{

        return {z, y};
    }
    #endif
    

    // VEC2 & MAT22
    #if defined(MATVEC_MV_VEC2_HPP) && defined(MATVEC_MV_MAT22_HPP)
    // -> MAT22
    template <typename T>
    mat22<T> vec2<T>::operator^(const vec2<T>& _v2) const{
            
        return {
            static_cast<T>(0.0), x*_v2.y-y*_v2.x,
            y*_v2.x-x*_v2.y,     static_cast<T>(0.0)
        };
    }

    template <typename T>
    mat22<T> vec2<T>::operator&&(const vec2<T>& _v2) const{
            
        return {
            x*_v2.x, x*_v2.y,
            y*_v2.x, y*_v2.y
        };
    }
    #endif

    
    // VEC3 & MAT33
    #if defined(MATVEC_MV_VEC3_HPP) && defined(MATVEC_MV_MAT33_HPP)
    // -> MAT33
    template <typename T>
    mat33<T> vec3<T>::operator^(const vec3<T>& _v3) const{
            
        return {
            static_cast<T>(0.0), x*_v3.y-y*_v3.x,     x*_v3.z-z*_v3.x,
            y*_v3.x-x*_v3.y,     static_cast<T>(0.0), y*_v3.z-z*_v3.y,
            z*_v3.x-x*_v3.z,     z*_v3.y-y*_v3.z,     static_cast<T>(0.0)
        };
    }

    template <typename T>
    mat33<T> vec3<T>::operator&&(const vec3<T>& _v3) const{
            
        return {
            x*_v3.x, x*_v3.y, x*_v3.z,
            y*_v3.x, y*_v3.y, y*_v3.z,
            z*_v3.x, z*_v3.y, z*_v3.z
        };
    }
    #endif
}
#endif
