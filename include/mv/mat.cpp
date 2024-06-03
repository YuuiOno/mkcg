#ifndef MATVEC_MV_MAT_CPP
#define MATVEC_MV_MAT_CPP

#include "mat.hpp"

#include <cmath>

namespace mv{
    
    //+++++++++++++++++++++++++//
    //    Private Functions    //
    //+++++++++++++++++++++++++//
    template <typename T> template <typename... A>
    void mat<T>::__input(size_t _count, const T& _sca,  A... _args){
        if(_count<__size) __elem[_count]=_sca;
        ++_count;
        __input(_count, _args...);
        
        return;
    }


    template <typename T>
    void mat<T>::__input(size_t _count){

        return;
    }


    
    //++++++++++++++++++++++++//
    //    Public Functions    //
    //++++++++++++++++++++++++//
    // Constructors & Destructor
    template <typename T>
    mat<T>::mat()
        : __row      {0}
        , __col      {0}
        , __size     {0}
        , __elem     {reinterpret_cast<T*>(std::malloc(0))}
        , __capacity {0}
    {

        return;
    }
    
    
    template <typename T>
    mat<T>::mat(size_t _row, size_t _col, const T& _sca)
        : __row      {_row}
        , __col      {_col}
        , __size     {__row*__col}
        , __elem     {reinterpret_cast<T*>(std::malloc(sizeof(T)*__size))}
        , __capacity {__size}
    {
        for(size_t a=0; a<__size; ++a) __elem[a]=_sca;
    
        return;
    }
    
    template <typename T> template <typename... A>
    mat<T>::mat(size_t _row, size_t _col, A... _args)
        : __row      {_row}
        , __col      {_col}
        , __size     {__row*__col}
        , __elem     {reinterpret_cast<T*>(std::malloc(sizeof(T)*__size))}
        , __capacity {__size}
    {
        __input(0, _args...);

        return;
    }


    template <typename T>
    mat<T>::~mat(){
        __row=0;
        __col=0;
        __size=0;
        if(__elem!=nullptr) delete[] __elem;
        __capacity=0;
        
        return;
    }
/*

    // Constant Functions(mat<T>)
    template <typename T>
    mat<T> mat<T>::normal() const{
        
        return (*this)/(this->norm());
    }
    
    template <typename T>
    mat<T> mat<T>::sym() const{
        
        return (this->operator+(this->operator++(0))).operator/(static_cast<T>(2));
    }

    template <typename T>
    mat<T> mat<T>::alt() const{
        
        return (this->operator-(this->operator++(0))).operator/(static_cast<T>(2));
    }

    template <typename T>
    mat<T> mat<T>::image(T(& _func)(T)) const{
        
        return {x.image(_func), y.image(_func), z.image(_func)};
    }

    template <typename T>
    mat<T> mat<T>::image(T(& _func)(const T&)) const{
       
        return {x.image(_func), y.image(_func), z.image(_func)};
    }

    template <typename T> template <typename... A>
    mat<T> mat<T>::image(T(& _func)(T, A...), A... _args) const{
        
        return {
            x.image(_func, _args...),
            y.image(_func, _args...),
            z.image(_func, _args...)
        };
    }
    
    template <typename T> template <typename... A>
    mat<T> mat<T>::image(T(& _func)(const T&, A...), A... _args) const{
        
        return {
            x.image(_func, _args...),
            y.image(_func, _args...),
            z.image(_func, _args...)
        };
    }

    // Constant Functions(T)
    template <typename T>
    T mat<T>::norm() const{

        return std::pow(x.square()+y.square()+z.square(), static_cast<T>(0.5));
    }

    template <typename T>
    T mat<T>::norm(const T& _sca) const{
        
        return std::pow(x.square()+y.square()+z.square(), static_cast<T>(1.0)/_sca);
    }

    template <typename T>
    T mat<T>::square() const{
        
        return x.square()+y.square()+z.square();
    }

    // Constant Functions(void)
    template <typename T>
    void mat<T>::autoPrint() const{

        std::cerr<<"x   : "<<x<<std::endl;
        std::cerr<<"y   : "<<y<<std::endl;
        std::cerr<<"z   : "<<z<<std::endl;
        std::cerr<<"Type: "<<typeid(xx).name()<<std::endl;
        std::cerr<<"Size: "<<sizeof(*this)<<std::endl;
        std::cerr<<std::endl;

        return;
    }


    // Constant Operators(mat<T>)
    template <typename T>
    mat<T> mat<T>::operator+(const mat<T>& _m33) const{

        return {x+_m33.x, y+_m33.y, z+_m33.z};
    }
    
    template <typename T>
    mat<T> mat<T>::operator-(const mat<T>& _m33) const{
        
        return {x-_m33.x, y-_m33.y, z-_m33.z};
    }

    template <typename T>
    mat<T> mat<T>::operator*(const mat<T>& _m33) const{
        
        return {x*_m33.x, y*_m33.y, z*_m33.z};
    }
    
    template <typename T>
    mat<T> mat<T>::operator|(const mat<T>& _m33) const{
        
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
    mat<T> mat<T>::operator/(const mat<T>& _m33) const{
        
        return {x/_m33.x, y/_m33.y, z/_m33.z};
    }

    template <typename T>
    mat<T> mat<T>::operator%(const mat<T>& _m33) const{
        
        return {x%_m33.x, y%_m33.y, z%_m33.z};
    }

    template <typename T>
    mat<T> mat<T>::operator+(const T& _s) const{
        
        return {x+_s, y+_s, z+_s};
    }
    
    template <typename T>
    mat<T> mat<T>::operator-(const T& _s) const{
        
        return {x-_s, y-_s, z-_s};
    }

    template <typename T>
    mat<T> mat<T>::operator*(const T& _s) const{
        
        return {x*_s, y*_s, z*_s};
    }

    template <typename T>
    mat<T> mat<T>::operator/(const T& _s) const{
        
        return {x/_s, y/_s, z/_s};
    }

    template <typename T>
    mat<T> mat<T>::operator%(const T& _s) const{
     
        return {x%_s, y%_s, z%_s};
    }

    template <typename T>
    mat<T> mat<T>::operator+() const{
        
        return *(this);
    }
    
    template <typename T>
    mat<T> mat<T>::operator-() const{
        
        return {-x, -y, -z};
    }
    
    template <typename T>
    mat<T> mat<T>::operator++(int) const{

        return {xx, yx, zx, xy, yy, zy, xz, yz, zz};
    }


    template <typename T>
    mat<T> mat<T>::operator~() const{
        
        return mat<T>(
            yy*zz-yz*zy, xz*zy-xy*zz, xy*yz-xz*yy,
            yz*zx-yx*zz, xx*zz-xz*zx, xz*yx-xx*yz,
            yx*zy-yy*zx, xy*zx-xx*zy, xx*yy-xy*yx
        )/(this->operator!());
    }

    // Constant Operators(vec3<T>)
    template <typename T>
    vec3<T> mat<T>::operator|(const vec3<T>& _v3) const{
     
        return {(x||_v3), (y||_v3), (z||_v3)};
    }

    template <typename T>
    vec3<T> mat<T>::operator*() const{
     
        return {yz, zx, xy};
    }

    // Constant Operators(T)
    template <typename T>
    T mat<T>::operator!() const{

        return xx*yy*zz+xy*yz*zx+xz*yx*zy-xz*yy*zx-xy*yx*zz-xx*yz*zy;
    }
 
    template <typename T>
    T mat<T>::operator--(int) const{

        return xx+yy+zz;
    }

    template <typename T>
    T mat<T>::operator||(const mat<T>& _m33) const{

        return x*_m33.x+y*_m33.y+z*_m33.z;
    }

    // Constant Operators(bool)
    template <typename T>
    bool mat<T>::operator==(const mat<T>& _m33) const{
        
        if(x==_m33.x && y==_m33.y && z==_m33.z) return true;
        else                                    return false;
    }

    template <typename T>
    bool mat<T>::operator!=(const mat<T>& _m33) const{
        
        if(x==_m33.x && y==_m33.y && z==_m33.z) return false;
        else                                    return true;
    }


    // Altering Functions
    template <typename T>
    mat<T>& mat<T>::zero(){

        return (*this)=(static_cast<T>(0.0));
    }
    
    template <typename T>
    mat<T>& mat<T>::ident(){

        return (*this)=vec3<T>(static_cast<T>(1.0));
    }
    
    template <typename T>
    mat<T>& mat<T>::normalize(){
        
        return (*this).operator/=(this->norm());
    }
             
    template <typename T>
    mat<T>& mat<T>::map(T(& _func)(T)){
        
        return (*this)=this->image(_func);
    }

    template <typename T>
    mat<T>& mat<T>::map(T(& _func)(const T&)){
        
        return (*this)=this->image(_func);
    }
    
    template <typename T> template <typename... A>
    mat<T>& mat<T>::map(T(& _func)(T, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    template <typename T> template <typename... A>
    mat<T>& mat<T>::map(T(& _func)(const T&, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    // Altering Operators
    template <typename T>
    mat<T>& mat<T>::operator+=(const mat<T>& _m33){

        return (*this)=this->operator+(_m33);
    }
    
    template <typename T>
    mat<T>& mat<T>::operator-=(const mat<T>& _m33){

        return (*this)=this->operator-(_m33);
    }
    
    template <typename T>
    mat<T>& mat<T>::operator*=(const mat<T>& _m33){

        return (*this)=this->operator*(_m33);
    }

    template <typename T>
    mat<T>& mat<T>::operator|=(const mat<T>& _m33){

        return (*this)=this->operator|(_m33);
    }

    template <typename T>
    mat<T>& mat<T>::operator/=(const mat<T>& _m33){

        return (*this)=this->operator/(_m33);
    }

    template <typename T>
    mat<T>& mat<T>::operator%=(const mat<T>& _m33){

        return (*this)=this->operator%(_m33);
    }

    template <typename T>
    mat<T>& mat<T>::operator+=(const T& _s){

        return (*this)=this->operator+(_s);
    }
    
    template <typename T>
    mat<T>& mat<T>::operator-=(const T& _s){

        return (*this)=this->operator-(_s);
    }

    template <typename T>
    mat<T>& mat<T>::operator*=(const T& _s){

        return (*this)=this->operator*(_s);
    }

    template <typename T>
    mat<T>& mat<T>::operator/=(const T& _s){

        return (*this)=this->operator/(_s);
    }

    template <typename T>
    mat<T>& mat<T>::operator%=(const T& _s){

        return (*this)=this->operator%(_s);
    }

    template <typename T>
    mat<T>& mat<T>::operator++(){

        return (*this)={++x, ++y, ++z};
    }
    
    template <typename T>
    mat<T>& mat<T>::operator--(){

        return (*this)={--x, --y, --z};
    }
*/

    // Constant Functions
    template <typename T>
    size_t mat<T>::row() const{
        return __row;
    }


    template <typename T>
    size_t mat<T>::col() const{
        return __col;
    }


    template <typename T>
    size_t mat<T>::size() const{
        return __size;
    }


    template <typename T>
    size_t mat<T>::capacity() const{
        return __capacity;
    }

    template <typename T>
    const T& mat<T>::operator()(size_t _pos) const{
        return __elem[_pos];
    }

    template <typename T>
    T& mat<T>::operator[](size_t _pos){
        return __elem[_pos];
    }

    

}



// General Functions
template <typename T>
std::ostream& operator<<(std::ostream& _os, const mv::mat<T>& _m){
    
    for(size_t a=0, b=0; a<_m.col(); ++a, b+=_m.row()){
        if(b!=0) _os<<"\n";
        for(size_t c=0; c<_m.row(); ++c){
            const T sca=_m(b+c);
            _os<<sca<<" ";
        }
    }

    return _os;
}


#endif
