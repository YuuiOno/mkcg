#ifndef MATVEC_MV_VEC3_CPP
#define MATVEC_MV_VEC3_CPP

#include "vec3.hpp"

#include <cmath>

namespace mv{
    
    // Constructors & Destructor
    template <typename T>
    vec3<T>::vec3()
        : x{}
        , y{}
        , z{}
    {

    }

    template <typename T>
    vec3<T>::vec3(const T& _sca)
        : x{_sca}
        , y{_sca}
        , z{_sca}
    {

    }

    template <typename T>
    vec3<T>::vec3(const T& _sca1, const T& _sca2, const T& _sca3)
        : x{_sca1}
        , y{_sca2}
        , z{_sca3}
    {

    }

    template <typename T>
    vec3<T>::~vec3(){
        
    }


    // Constant Functions(vec3<T>)
    template <typename T>
    vec3<T> vec3<T>::normal() const{
        
        return (*this)/(this->norm());
    }

    template <typename T>
    vec3<T> vec3<T>::image(T(& _func)(T)) const{
        
        return {_func(x), _func(y), _func(z)};
    }

    template <typename T>
    vec3<T> vec3<T>::image(T(& _func)(const T&)) const{
        
        return {_func(x), _func(y), _func(z)};
    }

    template <typename T> template <typename... A>
    vec3<T> vec3<T>::image(T(& _func)(T, A...), A... _args) const{
        
        return {_func(x, _args...), _func(y, _args...), _func(z, _args...)};
    }
    
    template <typename T> template <typename... A>
    vec3<T> vec3<T>::image(T(& _func)(const T&, A...), A... _args) const{
        
        return {_func(x, _args...), _func(y, _args...), _func(z, _args...)};
    }

    // Constant Functions(T)
    template <typename T>
    T vec3<T>::norm() const{

        return std::pow(x*x+y*y+z*z, static_cast<T>(0.5));
    }

    template <typename T>
    T vec3<T>::norm(const T& _sca) const{

        return std::pow(x*x+y*y+z*z, static_cast<T>(1.0)/_sca);
    }

    template <typename T>
    T vec3<T>::square() const{
        
        return x*x+y*y+z*z;
    }

    // Constant Functions(void)
    template <typename T>
    void vec3<T>::autoPrint() const{

        std::cerr<<"x   : "<<x<<std::endl;
        std::cerr<<"y   : "<<y<<std::endl;
        std::cerr<<"z   : "<<z<<std::endl;
        std::cerr<<"Type: "<<typeid(x).name()<<std::endl;
        std::cerr<<"Size: "<<sizeof(*this)<<std::endl;
        std::cerr<<std::endl;

        return;
    }


    // Constant Operators(vec3<T>)
    template <typename T>
    vec3<T> vec3<T>::operator+(const vec3<T>& _v3) const{

        return {x+_v3.x, y+_v3.y, z+_v3.z};
    }
    
    template <typename T>
    vec3<T> vec3<T>::operator-(const vec3<T>& _v3) const{
        
        return {x-_v3.x, y-_v3.y, z-_v3.z};
    }

    template <typename T>
    vec3<T> vec3<T>::operator*(const vec3<T>& _v3) const{
        
        return {x*_v3.x, y*_v3.y, z*_v3.z};
    }
    
    template <typename T>
    vec3<T> vec3<T>::operator/(const vec3<T>& _v3) const{
        
        return {x/_v3.x, y/_v3.y, z/_v3.z};
    }

    template <typename T>
    vec3<T> vec3<T>::operator%(const vec3<T>& _v3) const{
        
        return {x%_v3.x, y%_v3.y, z%_v3.z};
    }

    template <typename T>
    vec3<T> vec3<T>::operator+(const T& _s) const{
        
        return {x+_s, y+_s, z+_s};
    }
    
    template <typename T>
    vec3<T> vec3<T>::operator-(const T& _s) const{
        
        return {x-_s, y-_s, z-_s};
    }

    template <typename T>
    vec3<T> vec3<T>::operator*(const T& _s) const{
        
        return {x*_s, y*_s, z*_s};
    }

    template <typename T>
    vec3<T> vec3<T>::operator/(const T& _s) const{
        
        return {x/_s, y/_s, z/_s};
    }

    template <typename T>
    vec3<T> vec3<T>::operator%(const T& _s) const{
        
        return {x%_s, y%_s, z%_s};
    }

    template <typename T>
    vec3<T> vec3<T>::operator+() const{
        
        return *(this);
    }
    
    template <typename T>
    vec3<T> vec3<T>::operator-() const{
        
        return {-x, -y, -z};
    }

    template <typename T>
    vec3<T> vec3<T>::operator~() const{
        
        return {static_cast<T>(1.0)/x, static_cast<T>(1.0)/y, static_cast<T>(1.0)/z};
    }

    // Constant Operators(T)
    template <typename T>
    T vec3<T>::operator!() const{

        return x*y*z;
    }
    
    template <typename T>
    T vec3<T>::operator--(int) const{

        return x+y+z;
    }

    template <typename T>
    T vec3<T>::operator||(const vec3<T>& _v3) const{

        return x*_v3.x+y*_v3.y+z*_v3.z;
    }
 
    // Constant Operators(bool)
    template <typename T>
    bool vec3<T>::operator==(const vec3<T>& _v3) const{
        
        if(x==_v3.x && y==_v3.y && z==_v3.z) return true;
        else                                 return false;
    }

    template <typename T>
    bool vec3<T>::operator!=(const vec3<T>& _v3) const{
        
        if(x==_v3.x && y==_v3.y && z==_v3.z) return false;
        else                                 return true;
    }


    // Altering Functions
    template <typename T>
    vec3<T>& vec3<T>::zero(){

        return (*this)={(static_cast<T>(0.0))};
    }
    
    template <typename T>
    vec3<T>& vec3<T>::ident(){

        return (*this)={(static_cast<T>(1.0))};
    }
    
    template <typename T>
    vec3<T>& vec3<T>::normalize(){
        
        return (*this).operator/=(this->norm());
    }
        
        
    template <typename T>
    vec3<T>& vec3<T>::map(T(& _func)(T)){
        
        return (*this)=this->image(_func);
    }

    template <typename T>
    vec3<T>& vec3<T>::map(T(& _func)(const T&)){
        
        return (*this)=this->image(_func);
    }
    
    template <typename T> template <typename... A>
    vec3<T>& vec3<T>::map(T(& _func)(T, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    template <typename T> template <typename... A>
    vec3<T>& vec3<T>::map(T(& _func)(const T&, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    
    // Altering Operators
    template <typename T>
    vec3<T>& vec3<T>::operator+=(const vec3<T>& _v3){

        return (*this)=this->operator+(_v3);
    }
    
    template <typename T>
    vec3<T>& vec3<T>::operator-=(const vec3<T>& _v3){

        return (*this)=this->operator-(_v3);
    }
    
    template <typename T>
    vec3<T>& vec3<T>::operator*=(const vec3<T>& _v3){

        return (*this)=this->operator*(_v3);
    }

    template <typename T>
    vec3<T>& vec3<T>::operator/=(const vec3<T>& _v3){

        return (*this)=this->operator/(_v3);
    }

    template <typename T>
    vec3<T>& vec3<T>::operator%=(const vec3<T>& _v3){

        return (*this)=this->operator%(_v3);
    }
    
    template <typename T>
    vec3<T>& vec3<T>::operator+=(const T& _s){

        return (*this)=this->operator+(_s);
    }
    
    template <typename T>
    vec3<T>& vec3<T>::operator-=(const T& _s){

        return (*this)=this->operator-(_s);
    }

    template <typename T>
    vec3<T>& vec3<T>::operator*=(const T& _s){

        return (*this)=this->operator*(_s);
    }

    template <typename T>
    vec3<T>& vec3<T>::operator/=(const T& _s){

        return (*this)=this->operator/(_s);
    }

    template <typename T>
    vec3<T>& vec3<T>::operator%=(const T& _s){

        return (*this)=this->operator%(_s);
    }

    template <typename T>
    vec3<T>& vec3<T>::operator++(){

        return (*this)={++x, ++y, ++z};
    }
    
    template <typename T>
    vec3<T>& vec3<T>::operator--(){

        return (*this)={--x, --y, --z};
    }

    // General Functions
    template <typename T>
    std::ostream& operator<<(std::ostream& _os, const mv::vec3<T>& _v3){

        return _os<<_v3.x<<" "<<_v3.y<<" "<<_v3.z;
    }


    template <typename T>
    std::istream& operator>>(std::istream& _is, mv::vec3<T>& _v3){

        return _is>>_v3.x>>_v3.y>>_v3.z;
    }


    template <typename T, typename I>
    mv::vec3<T> matvec_cast(const mv::vec3<I>& v3_){
    
        return mv::vec3<T>{static_cast<T>(v3_.x), static_cast<T>(v3_.y), static_cast<T>(v3_.z)};
    }









}


#endif
