#ifndef MATVEC_MV_MAT33_CPP
#define MATVEC_MV_MAT33_CPP

#include "mat33.hpp"

#include <cmath>

namespace mv{
    
    // Constructors & Destructor
    template <typename T>
    mat33<T>::mat33()
        : x{}
        , y{}
        , z{}
    {

    }

    template <typename T>
    mat33<T>::mat33(const T& _sca)
        : x{_sca}
        , y{_sca}
        , z{_sca}
    {

    }
    
    template <typename T>
    mat33<T>::mat33(const T& _sca11, const T& _sca22, const T& _sca33)
        : x{_sca11,              static_cast<T>(0.0), static_cast<T>(0.0)}
        , y{static_cast<T>(0.0), _sca22,              static_cast<T>(0.0)}
        , z{static_cast<T>(0.0), static_cast<T>(0.0), _sca33             }
    {

    }

    template <typename T>
    mat33<T>::mat33(
        const T& _sca11, const T& _sca12, const T& _sca13,
        const T& _sca21, const T& _sca22, const T& _sca23,
        const T& _sca31, const T& _sca32, const T& _sca33
    )
        : x{_sca11, _sca12, _sca13}
        , y{_sca21, _sca22, _sca23}
        , z{_sca31, _sca32, _sca33}
    {

    }

    template <typename T>
    mat33<T>::mat33(const vec3<T>& _v3)
        : x{_v3.x,               static_cast<T>(0.0), static_cast<T>(0.0)}
        , y{static_cast<T>(0.0), _v3.y,               static_cast<T>(0.0)}
        , z{static_cast<T>(0.0), static_cast<T>(0.0), _v3.z              }
    {

    }
    
    template <typename T>
    mat33<T>::mat33(const vec3<T>& _v31, const vec3<T>& _v32, const vec3<T>& _v33)
        : x{_v31}
        , y{_v32}
        , z{_v33}
    {

    }

    template <typename T>
    mat33<T>::~mat33(){
        
    }


    // Constant Functions(mat33<T>)
    template <typename T>
    mat33<T> mat33<T>::normal() const{
        
        return (*this)/(this->norm());
    }
    
    template <typename T>
    mat33<T> mat33<T>::sym() const{
        
        return (this->operator+(this->operator++(0))).operator/(static_cast<T>(2));
    }

    template <typename T>
    mat33<T> mat33<T>::alt() const{
        
        return (this->operator-(this->operator++(0))).operator/(static_cast<T>(2));
    }

    template <typename T>
    mat33<T> mat33<T>::image(T(& _func)(T)) const{
        
        return {x.image(_func), y.image(_func), z.image(_func)};
    }

    template <typename T>
    mat33<T> mat33<T>::image(T(& _func)(const T&)) const{
       
        return {x.image(_func), y.image(_func), z.image(_func)};
    }

    template <typename T> template <typename... A>
    mat33<T> mat33<T>::image(T(& _func)(T, A...), A... _args) const{
        
        return {
            x.image(_func, _args...),
            y.image(_func, _args...),
            z.image(_func, _args...)
        };
    }
    
    template <typename T> template <typename... A>
    mat33<T> mat33<T>::image(T(& _func)(const T&, A...), A... _args) const{
        
        return {
            x.image(_func, _args...),
            y.image(_func, _args...),
            z.image(_func, _args...)
        };
    }

    // Constant Functions(T)
    template <typename T>
    T mat33<T>::norm() const{

        return std::pow(x.square()+y.square()+z.square(), static_cast<T>(0.5));
    }

    template <typename T>
    T mat33<T>::norm(const T& _sca) const{
        
        return std::pow(x.square()+y.square()+z.square(), static_cast<T>(1.0)/_sca);
    }

    template <typename T>
    T mat33<T>::square() const{
        
        return x.square()+y.square()+z.square();
    }

    // Constant Functions(void)
    template <typename T>
    void mat33<T>::autoPrint() const{

        std::cerr<<"x   : "<<x<<std::endl;
        std::cerr<<"y   : "<<y<<std::endl;
        std::cerr<<"z   : "<<z<<std::endl;
        std::cerr<<"Type: "<<typeid(xx).name()<<std::endl;
        std::cerr<<"Size: "<<sizeof(*this)<<std::endl;
        std::cerr<<std::endl;

        return;
    }


    // Constant Operators(mat33<T>)
    template <typename T>
    mat33<T> mat33<T>::operator+(const mat33<T>& _m33) const{

        return {x+_m33.x, y+_m33.y, z+_m33.z};
    }
    
    template <typename T>
    mat33<T> mat33<T>::operator-(const mat33<T>& _m33) const{
        
        return {x-_m33.x, y-_m33.y, z-_m33.z};
    }

    template <typename T>
    mat33<T> mat33<T>::operator*(const mat33<T>& _m33) const{
        
        return {x*_m33.x, y*_m33.y, z*_m33.z};
    }
    
    template <typename T>
    mat33<T> mat33<T>::operator|(const mat33<T>& _m33) const{
        
        return {
            xx*_m33.xx+xy*_m33.yx+xz*_m33.zx,
            xx*_m33.xy+xy*_m33.yy+xz*_m33.zy,
            xx*_m33.xz+xy*_m33.yz+xz*_m33.zz,
            yx*_m33.xx+yy*_m33.yx+yz*_m33.zx,
            yx*_m33.xy+yy*_m33.yy+yz*_m33.zy,
            yx*_m33.xz+yy*_m33.yz+yz*_m33.zz,
            zx*_m33.xx+zy*_m33.yx+zz*_m33.zx,
            zx*_m33.xy+zy*_m33.yy+zz*_m33.zy,
            zx*_m33.xz+zy*_m33.yz+zz*_m33.zz
        };
    }
   
    template <typename T>
    mat33<T> mat33<T>::operator/(const mat33<T>& _m33) const{
        
        return {x/_m33.x, y/_m33.y, z/_m33.z};
    }

    template <typename T>
    mat33<T> mat33<T>::operator%(const mat33<T>& _m33) const{
        
        return {x%_m33.x, y%_m33.y, z%_m33.z};
    }

    template <typename T>
    mat33<T> mat33<T>::operator+(const T& _s) const{
        
        return {x+_s, y+_s, z+_s};
    }
    
    template <typename T>
    mat33<T> mat33<T>::operator-(const T& _s) const{
        
        return {x-_s, y-_s, z-_s};
    }

    template <typename T>
    mat33<T> mat33<T>::operator*(const T& _s) const{
        
        return {x*_s, y*_s, z*_s};
    }

    template <typename T>
    mat33<T> mat33<T>::operator/(const T& _s) const{
        
        return {x/_s, y/_s, z/_s};
    }

    template <typename T>
    mat33<T> mat33<T>::operator%(const T& _s) const{
     
        return {x%_s, y%_s, z%_s};
    }

    template <typename T>
    mat33<T> mat33<T>::operator+() const{
        
        return *(this);
    }
    
    template <typename T>
    mat33<T> mat33<T>::operator-() const{
        
        return {-x, -y, -z};
    }
    
    template <typename T>
    mat33<T> mat33<T>::operator++(int) const{

        return {xx, yx, zx, xy, yy, zy, xz, yz, zz};
    }


    template <typename T>
    mat33<T> mat33<T>::operator~() const{
        
        return mat33<T>(
            yy*zz-yz*zy, xz*zy-xy*zz, xy*yz-xz*yy,
            yz*zx-yx*zz, xx*zz-xz*zx, xz*yx-xx*yz,
            yx*zy-yy*zx, xy*zx-xx*zy, xx*yy-xy*yx
        )/(this->operator!());
    }

    // Constant Operators(vec3<T>)
    template <typename T>
    vec3<T> mat33<T>::operator|(const vec3<T>& _v3) const{
     
        return {(x||_v3), (y||_v3), (z||_v3)};
    }

    template <typename T>
    vec3<T> mat33<T>::operator*() const{
     
        return {yz, zx, xy};
    }

    // Constant Operators(T)
    template <typename T>
    T mat33<T>::operator!() const{

        return xx*yy*zz+xy*yz*zx+xz*yx*zy-xz*yy*zx-xy*yx*zz-xx*yz*zy;
    }
 
    template <typename T>
    T mat33<T>::operator--(int) const{

        return xx+yy+zz;
    }

    template <typename T>
    T mat33<T>::operator||(const mat33<T>& _m33) const{

        return x*_m33.x+y*_m33.y+z*_m33.z;
    }

    // Constant Operators(bool)
    template <typename T>
    bool mat33<T>::operator==(const mat33<T>& _m33) const{
        
        if(x==_m33.x && y==_m33.y && z==_m33.z) return true;
        else                                    return false;
    }

    template <typename T>
    bool mat33<T>::operator!=(const mat33<T>& _m33) const{
        
        if(x==_m33.x && y==_m33.y && z==_m33.z) return false;
        else                                    return true;
    }


    // Altering Functions
    template <typename T>
    mat33<T>& mat33<T>::zero(){

        return (*this)=(static_cast<T>(0.0));
    }
    
    template <typename T>
    mat33<T>& mat33<T>::ident(){

        return (*this)=vec3<T>(static_cast<T>(1.0));
    }
    
    template <typename T>
    mat33<T>& mat33<T>::normalize(){
        
        return (*this).operator/=(this->norm());
    }
             
    template <typename T>
    mat33<T>& mat33<T>::map(T(& _func)(T)){
        
        return (*this)=this->image(_func);
    }

    template <typename T>
    mat33<T>& mat33<T>::map(T(& _func)(const T&)){
        
        return (*this)=this->image(_func);
    }
    
    template <typename T> template <typename... A>
    mat33<T>& mat33<T>::map(T(& _func)(T, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    template <typename T> template <typename... A>
    mat33<T>& mat33<T>::map(T(& _func)(const T&, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    // Altering Operators
    template <typename T>
    mat33<T>& mat33<T>::operator+=(const mat33<T>& _m33){

        return (*this)=this->operator+(_m33);
    }
    
    template <typename T>
    mat33<T>& mat33<T>::operator-=(const mat33<T>& _m33){

        return (*this)=this->operator-(_m33);
    }
    
    template <typename T>
    mat33<T>& mat33<T>::operator*=(const mat33<T>& _m33){

        return (*this)=this->operator*(_m33);
    }

    template <typename T>
    mat33<T>& mat33<T>::operator|=(const mat33<T>& _m33){

        return (*this)=this->operator|(_m33);
    }

    template <typename T>
    mat33<T>& mat33<T>::operator/=(const mat33<T>& _m33){

        return (*this)=this->operator/(_m33);
    }

    template <typename T>
    mat33<T>& mat33<T>::operator%=(const mat33<T>& _m33){

        return (*this)=this->operator%(_m33);
    }

    template <typename T>
    mat33<T>& mat33<T>::operator+=(const T& _s){

        return (*this)=this->operator+(_s);
    }
    
    template <typename T>
    mat33<T>& mat33<T>::operator-=(const T& _s){

        return (*this)=this->operator-(_s);
    }

    template <typename T>
    mat33<T>& mat33<T>::operator*=(const T& _s){

        return (*this)=this->operator*(_s);
    }

    template <typename T>
    mat33<T>& mat33<T>::operator/=(const T& _s){

        return (*this)=this->operator/(_s);
    }

    template <typename T>
    mat33<T>& mat33<T>::operator%=(const T& _s){

        return (*this)=this->operator%(_s);
    }

    template <typename T>
    mat33<T>& mat33<T>::operator++(){

        return (*this)={++x, ++y, ++z};
    }
    
    template <typename T>
    mat33<T>& mat33<T>::operator--(){

        return (*this)={--x, --y, --z};
    }
}

// General Functions
template <typename T>
std::ostream& operator<<(std::ostream& _os, const mv::mat33<T>& _m33){

    return _os<<_m33.xx<<" "<<_m33.xy<<" "<<_m33.xz<<"\n"<<_m33.yx<<" "<<_m33.yy<<" "<<_m33.yz<<"\n"<<_m33.zx<<" "<<_m33.zy<<" "<<_m33.zz;
}

#endif
