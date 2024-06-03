#ifndef MATVEC_MV_MAT22_CPP
#define MATVEC_MV_MAT22_CPP

#include "mat22.hpp"

#include <cmath>

namespace mv{
    
    // Constructors & Destructor
    template <typename T>
    mat22<T>::mat22()
        : x{}
        , y{}
    {

        return;
    }

    template <typename T>
    mat22<T>::mat22(const T& _sca)
        : x{_sca}
        , y{_sca}
    {

        return;
    }
    
    template <typename T>
    mat22<T>::mat22(const T& _sca11, const T& _sca22)
        : x{_sca11,              static_cast<T>(0.0)}
        , y{static_cast<T>(0.0), _sca22             }
    {

        return;
    }

    template <typename T>
    mat22<T>::mat22(
        const T& _sca11, const T& _sca12,
        const T& _sca21, const T& _sca22
    )
        : x{_sca11, _sca12}
        , y{_sca21, _sca22}
    {
        return;
    }

    template <typename T>
    mat22<T>::mat22(const vec2<T>& _v2)
        : x{_v2.x,               static_cast<T>(0.0)}
        , y{static_cast<T>(0.0), _v2.y              }
    {

        return;
    }
    
    template <typename T>
    mat22<T>::mat22(const vec2<T>& _v21, const vec2<T>& _v22)
        : x{_v21}
        , y{_v22}
    {

        return;
    }

    template <typename T>
    mat22<T>::~mat22(){
        
    }


    // Constant Functions(mat22<T>)
    template <typename T>
    mat22<T> mat22<T>::normal() const{
        
        return (*this)/(this->norm());
    }
    
    template <typename T>
    mat22<T> mat22<T>::sym() const{
        
        return (this->operator+(this->operator++(0))).operator/(static_cast<T>(2));
    }

    template <typename T>
    mat22<T> mat22<T>::alt() const{
        
        return (this->operator-(this->operator++(0))).operator/(static_cast<T>(2));
    }

    template <typename T>
    mat22<T> mat22<T>::image(T(& _func)(T)) const{
        
        return {x.image(_func), y.image(_func)};
    }

    template <typename T>
    mat22<T> mat22<T>::image(T(& _func)(const T&)) const{
       
        return {x.image(_func), y.image(_func)};
    }

    template <typename T> template <typename... A>
    mat22<T> mat22<T>::image(T(& _func)(T, A...), A... _args) const{
        
        return {
            x.image(_func, _args...),
            y.image(_func, _args...)
        };
    }
    
    template <typename T> template <typename... A>
    mat22<T> mat22<T>::image(T(& _func)(const T&, A...), A... _args) const{
        
        return {
            x.image(_func, _args...),
            y.image(_func, _args...)
        };
    }

    // Constant Functions(T)
    template <typename T>
    T mat22<T>::norm() const{

        return std::pow(x.square()+y.square(), static_cast<T>(0.5));
    }

    template <typename T>
    T mat22<T>::norm(const T& _sca) const{
        
        return std::pow(x.square()+y.square(), static_cast<T>(1.0)/_sca);
    }

    template <typename T>
    T mat22<T>::square() const{
        
        return x.square()+y.square();
    }

    // Constant Functions(void)
    template <typename T>
    void mat22<T>::autoPrint() const{

        std::cerr<<"x   : "<<x<<std::endl;
        std::cerr<<"y   : "<<y<<std::endl;
        std::cerr<<"Type: "<<typeid(xx).name()<<std::endl;
        std::cerr<<"Size: "<<sizeof(*this)<<std::endl;
        std::cerr<<std::endl;

        return;
    }


    // Constant Operators(mat22<T>)
    template <typename T>
    mat22<T> mat22<T>::operator+(const mat22<T>& _m22) const{

        return {x+_m22.x, y+_m22.y};
    }
    
    template <typename T>
    mat22<T> mat22<T>::operator-(const mat22<T>& _m22) const{
        
        return {x-_m22.x, y-_m22.y};
    }

    template <typename T>
    mat22<T> mat22<T>::operator*(const mat22<T>& _m22) const{
        
        return {x*_m22.x, y*_m22.y};
    }
    
    template <typename T>
    mat22<T> mat22<T>::operator|(const mat22<T>& _m22) const{
        
        return {
            xx*_m22.xx+xy*_m22.yx,
            xx*_m22.xy+xy*_m22.yy,
            yx*_m22.xx+yy*_m22.yx,
            yx*_m22.xy+yy*_m22.yy,
        };
    }
   
    template <typename T>
    mat22<T> mat22<T>::operator/(const mat22<T>& _m22) const{
        
        return {x/_m22.x, y/_m22.y};
    }

    template <typename T>
    mat22<T> mat22<T>::operator%(const mat22<T>& _m22) const{
        
        return {x%_m22.x, y%_m22.y};
    }

    template <typename T>
    mat22<T> mat22<T>::operator+(const T& _s) const{
        
        return {x+_s, y+_s};
    }
    
    template <typename T>
    mat22<T> mat22<T>::operator-(const T& _s) const{
        
        return {x-_s, y-_s};
    }

    template <typename T>
    mat22<T> mat22<T>::operator*(const T& _s) const{
        
        return {x*_s, y*_s};
    }

    template <typename T>
    mat22<T> mat22<T>::operator/(const T& _s) const{
        
        return {x/_s, y/_s};
    }

    template <typename T>
    mat22<T> mat22<T>::operator%(const T& _s) const{
     
        return {x%_s, y%_s};
    }

    template <typename T>
    mat22<T> mat22<T>::operator+() const{
        
        return *(this);
    }
    
    template <typename T>
    mat22<T> mat22<T>::operator-() const{
        
        return {-x, -y};
    }
    
    template <typename T>
    mat22<T> mat22<T>::operator++(int) const{

        return {xx, yx, xy, yy};
    }


    template <typename T>
    mat22<T> mat22<T>::operator~() const{
        
        return mat22<T>(
             yy, -xy,
            -yx,  xx
        )/(this->operator!());
    }

    // Constant Operators(vec2<T>)
    template <typename T>
    vec2<T> mat22<T>::operator|(const vec2<T>& _v2) const{
     
        return {(x||_v2), (y||_v2)};
    }

    
    template <typename T>
    T mat22<T>::operator*() const{
     
        return xy;
    }
    

    // Constant Operators(T)
    template <typename T>
    T mat22<T>::operator!() const{

        return xx*yy-xy*yx;
    }
 
    template <typename T>
    T mat22<T>::operator--(int) const{

        return xx+yy;
    }

    template <typename T>
    T mat22<T>::operator||(const mat22<T>& _m22) const{

        return x*_m22.x+y*_m22.y;
    }

    // Constant Operators(bool)
    template <typename T>
    bool mat22<T>::operator==(const mat22<T>& _m22) const{
        
        if(x==_m22.x && y==_m22.y) return true;
        else                       return false;
    }

    template <typename T>
    bool mat22<T>::operator!=(const mat22<T>& _m22) const{
        
        if(x==_m22.x && y==_m22.y) return false;
        else                       return true;
    }


    // Altering Functions
    template <typename T>
    mat22<T>& mat22<T>::zero(){

        return (*this)=(static_cast<T>(0.0));
    }
    
    template <typename T>
    mat22<T>& mat22<T>::ident(){

        return (*this)=vec2<T>(static_cast<T>(1.0));
    }
    
    template <typename T>
    mat22<T>& mat22<T>::normalize(){
        
        return (*this).operator/=(this->norm());
    }
             
    template <typename T>
    mat22<T>& mat22<T>::map(T(& _func)(T)){
        
        return (*this)=this->image(_func);
    }

    template <typename T>
    mat22<T>& mat22<T>::map(T(& _func)(const T&)){
        
        return (*this)=this->image(_func);
    }
    
    template <typename T> template <typename... A>
    mat22<T>& mat22<T>::map(T(& _func)(T, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    template <typename T> template <typename... A>
    mat22<T>& mat22<T>::map(T(& _func)(const T&, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    // Altering Operators
    template <typename T>
    mat22<T>& mat22<T>::operator+=(const mat22<T>& _m22){

        return (*this)=this->operator+(_m22);
    }
    
    template <typename T>
    mat22<T>& mat22<T>::operator-=(const mat22<T>& _m22){

        return (*this)=this->operator-(_m22);
    }
    
    template <typename T>
    mat22<T>& mat22<T>::operator*=(const mat22<T>& _m22){

        return (*this)=this->operator*(_m22);
    }

    template <typename T>
    mat22<T>& mat22<T>::operator|=(const mat22<T>& _m22){

        return (*this)=this->operator|(_m22);
    }

    template <typename T>
    mat22<T>& mat22<T>::operator/=(const mat22<T>& _m22){

        return (*this)=this->operator/(_m22);
    }

    template <typename T>
    mat22<T>& mat22<T>::operator%=(const mat22<T>& _m22){

        return (*this)=this->operator%(_m22);
    }

    template <typename T>
    mat22<T>& mat22<T>::operator+=(const T& _s){

        return (*this)=this->operator+(_s);
    }
    
    template <typename T>
    mat22<T>& mat22<T>::operator-=(const T& _s){

        return (*this)=this->operator-(_s);
    }

    template <typename T>
    mat22<T>& mat22<T>::operator*=(const T& _s){

        return (*this)=this->operator*(_s);
    }

    template <typename T>
    mat22<T>& mat22<T>::operator/=(const T& _s){

        return (*this)=this->operator/(_s);
    }

    template <typename T>
    mat22<T>& mat22<T>::operator%=(const T& _s){

        return (*this)=this->operator%(_s);
    }

    template <typename T>
    mat22<T>& mat22<T>::operator++(){

        return (*this)={++x, ++y};
    }
    
    template <typename T>
    mat22<T>& mat22<T>::operator--(){

        return (*this)={--x, --y};
    }
}

// General Functions
template <typename T>
std::ostream& operator<<(std::ostream& _os, const mv::mat22<T>& _m22){

    return _os<<_m22.xx<<" "<<_m22.xy<<"\n"<<_m22.yx<<" "<<_m22.yy;
}

#endif
