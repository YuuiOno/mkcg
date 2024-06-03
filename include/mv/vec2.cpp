#ifndef MATVEC_MV_VEC2_CPP
#define MATVEC_MV_VEC2_CPP

#include "vec2.hpp"

#include <cmath>
#include <typeinfo>

namespace mv{
    
    // Constructors & Destructor
    template <typename T>
    vec2<T>::vec2()
        : x{}
        , y{}
    {

    }

    template <typename T>
    vec2<T>::vec2(const T& sca_)
        : x{sca_}
        , y{sca_}
    {

    }

    template <typename T>
    vec2<T>::vec2(const T& sca1_, const T& sca2_)
        : x{sca1_}
        , y{sca2_}
    {

    }

    template <typename T>
    vec2<T>::~vec2(){
        
    }


    // Constant Functions(vec2<T>)
    template <typename T>
    vec2<T> vec2<T>::normal() const{
        
        return (*this)/(this->norm());
    }

    template <typename T>
    vec2<T> vec2<T>::image(T(& func_)(T)) const{
        
        return {func_(x), func_(y)};
    }

    template <typename T>
    vec2<T> vec2<T>::image(T(& func_)(const T&)) const{
        
        return {func_(x), func_(y)};
    }

    template <typename T> template <typename... A>
    vec2<T> vec2<T>::image(T(& func_)(T, A...), A... args_) const{
        
        return {func_(x, args_...), func_(y, args_...)};
    }
    
    template <typename T> template <typename... A>
    vec2<T> vec2<T>::image(T(& func_)(const T&, A...), A... args_) const{
        
        return {func_(x, args_...), func_(y, args_...)};
    }

    // Constant Functions(T)
    template <typename T>
    T vec2<T>::norm() const{

        return std::pow(x*x+y*y, static_cast<T>(0.5));
    }

    template <typename T>
    T vec2<T>::norm(const T& sca_) const{

        return std::pow(x*x+y*y, static_cast<T>(1.0)/sca_);
    }

    template <typename T>
    T vec2<T>::square() const{
        
        return x*x+y*y;
    }

    // Constant Functions(void)
    template <typename T>
    void vec2<T>::autoPrint() const{

        std::cerr<<"x   : "<<x<<std::endl;
        std::cerr<<"y   : "<<y<<std::endl;
        std::cerr<<"Type: "<<typeid(x).name()<<std::endl;
        std::cerr<<"Size: "<<sizeof(*this)<<std::endl;
        std::cerr<<std::endl;

        return;
    }



    // Constant Operators(vec2<T>)
    template <typename T>
    vec2<T> vec2<T>::operator+(const vec2<T>& v2_) const{

        return {x+v2_.x, y+v2_.y};
    }
    
    template <typename T>
    vec2<T> vec2<T>::operator-(const vec2<T>& v2_) const{
        
        return {x-v2_.x, y-v2_.y};
    }

    template <typename T>
    vec2<T> vec2<T>::operator*(const vec2<T>& v2_) const{
        
        return {x*v2_.x, y*v2_.y};
    }
    
    template <typename T>
    vec2<T> vec2<T>::operator/(const vec2<T>& v2_) const{
        
        return {x/v2_.x, y/v2_.y};
    }

    template <typename T>
    vec2<T> vec2<T>::operator%(const vec2<T>& v2_) const{
        
        return {x%v2_.x, y%v2_.y};
    }

    template <typename T>
    vec2<T> vec2<T>::operator+(const T& s_) const{
        
        return {x+s_, y+s_};
    }
    
    template <typename T>
    vec2<T> vec2<T>::operator-(const T& s_) const{
        
        return {x-s_, y-s_};
    }

    template <typename T>
    vec2<T> vec2<T>::operator*(const T& s_) const{
        
        return {x*s_, y*s_};
    }

    template <typename T>
    vec2<T> vec2<T>::operator/(const T& s_) const{
        
        return {x/s_, y/s_};
    }

    template <typename T>
    vec2<T> vec2<T>::operator%(const T& s_) const{
        
        return {x%s_, y%s_};
    }

    template <typename T>
    vec2<T> vec2<T>::operator+() const{
        
        return *(this);
    }
    
    template <typename T>
    vec2<T> vec2<T>::operator-() const{
        
        return {-x, -y};
    }

    template <typename T>
    vec2<T> vec2<T>::operator~() const{
        
        return {static_cast<T>(1.0)/x, static_cast<T>(1.0)/y};
    }

    // Constant Operators(T)
    template <typename T>
    T vec2<T>::operator!() const{

        return x*y;
    }
    
    template <typename T>
    T vec2<T>::operator--(int) const{

        return x+y;
    }

    template <typename T>
    T vec2<T>::operator||(const vec2<T>& v2_) const{

        return x*v2_.x+y*v2_.y;
    }


    template <typename T>
    T vec2<T>::operator<<(const vec2<T>& v2_) const{

        return x*v2_.y-y*v2_.x;
    }


    template <typename T>
    T vec2<T>::operator>>(const vec2<T>& v2_) const{

        return y*v2_.x-x*v2_.y;
    }



    // Constant Operators(bool)
    template <typename T>
    bool vec2<T>::operator==(const vec2<T>& v2_) const{
        
        if(x==v2_.x && y==v2_.y) return true;
        else                     return false;
    }

    template <typename T>
    bool vec2<T>::operator!=(const vec2<T>& v2_) const{
        
        if(x==v2_.x && y==v2_.y) return false;
        else                     return true;
    }


    // Altering Functions
    template <typename T>
    vec2<T>& vec2<T>::zero(){

        return (*this)={(static_cast<T>(0.0))};
    }
    
    template <typename T>
    vec2<T>& vec2<T>::ident(){

        return (*this)={(static_cast<T>(1.0))};
    }
    
    template <typename T>
    vec2<T>& vec2<T>::normalize(){
        
        return (*this).operator/=(this->norm());
    }
        
        
    template <typename T>
    vec2<T>& vec2<T>::map(T(& func_)(T)){
        
        return (*this)=this->image(func_);
    }

    template <typename T>
    vec2<T>& vec2<T>::map(T(& func_)(const T&)){
        
        return (*this)=this->image(func_);
    }
    
    template <typename T> template <typename... A>
    vec2<T>& vec2<T>::map(T(& func_)(T, A...), A... args_){
    
        return (*this)=this->image<A...>(func_, args_...);
    }

    template <typename T> template <typename... A>
    vec2<T>& vec2<T>::map(T(& func_)(const T&, A...), A... args_){
    
        return (*this)=this->image<A...>(func_, args_...);
    }

    
    // Altering Operators
    template <typename T>
    vec2<T>& vec2<T>::operator+=(const vec2<T>& v2_){

        return (*this)=this->operator+(v2_);
    }
    
    template <typename T>
    vec2<T>& vec2<T>::operator-=(const vec2<T>& v2_){

        return (*this)=this->operator-(v2_);
    }
    
    template <typename T>
    vec2<T>& vec2<T>::operator*=(const vec2<T>& v2_){

        return (*this)=this->operator*(v2_);
    }

    template <typename T>
    vec2<T>& vec2<T>::operator/=(const vec2<T>& v2_){

        return (*this)=this->operator/(v2_);
    }

    template <typename T>
    vec2<T>& vec2<T>::operator%=(const vec2<T>& v2_){

        return (*this)=this->operator%(v2_);
    }

    template <typename T>
    vec2<T>& vec2<T>::operator+=(const T& s_){

        return (*this)=this->operator+(s_);
    }
    
    template <typename T>
    vec2<T>& vec2<T>::operator-=(const T& s_){

        return (*this)=this->operator-(s_);
    }

    template <typename T>
    vec2<T>& vec2<T>::operator*=(const T& s_){

        return (*this)=this->operator*(s_);
    }

    template <typename T>
    vec2<T>& vec2<T>::operator/=(const T& s_){

        return (*this)=this->operator/(s_);
    }

    template <typename T>
    vec2<T>& vec2<T>::operator%=(const T& s_){

        return (*this)=this->operator%(s_);
    }

    template <typename T>
    vec2<T>& vec2<T>::operator++(){

        return (*this)={++x, ++y};
    }
    
    template <typename T>
    vec2<T>& vec2<T>::operator--(){

        return (*this)={--x, --y};
    }
}


// General Functions
template <typename T>
std::ostream& operator<<(std::ostream& _os, const mv::vec2<T>& v2_){

    return _os<<v2_.x<<" "<<v2_.y;
}
template <typename T>
std::istream& operator>>(std::istream& is_, mv::vec2<T>& v2_){

    return is_>>v2_.x>>v2_.y;
}


template <typename T, typename I>
mv::vec2<T> matvec_cast(const mv::vec2<I>& v2_){
    
    return mv::vec2<T>{static_cast<T>(v2_.x), static_cast<T>(v2_.y)};
}
#endif
