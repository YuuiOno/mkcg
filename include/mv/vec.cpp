#ifndef MATVEC_MV_MAT_CPP
#define MATVEC_MV_MAT_CPP

#include "vec.hpp"

namespace mv{
    
    //++++++++++++++++++++//
    //    Vector Class    //
    //++++++++++++++++++++//
    
    //---------------------//
    // Protected Functions //
    //---------------------//
    // For Inner Operations
    template <typename T> template <typename... A>
    void vec<T>::_input(size_t count_, const T& sca_,  A... args_){
        if(count_<_size) _elem[count_]=sca_;
        ++count_;
        _input(count_, args_...);
        
        return;
    }


    template <typename T>
    void vec<T>::_input(size_t count_){

        return;
    }
   

    template <typename T>
    temp::vec<T>& vec<T>::_find_free(size_t size_){
        temp::vec<T>* tvptr=nullptr;
        for(size_t a=0; a<_num; ++a){
            if((_vecs+a)->turn()){
                tvptr=_vecs+a;
                break;
            }
        }
        if(!tvptr){
            if(void* ptr_=std::realloc(_vecs, sizeof(T)*(++_num))){
                _vecs=reinterpret_cast<temp::vec<T>*>(ptr_);
                tvptr=&_vecs[_num-1];
                new(tvptr) temp::vec<T>(true);
            }else{
                _num=0;
                std::free(_vecs);
                _vecs=nullptr;
                #ifndef MATVEC_NO_EXCEPTION
                throw  failed_to_realloc{"vec<T>::_find_free()", _vecs, sizeof(T)* _num};
                #endif
            }
        }
        tvptr->resize(size_);
        tvptr->turn();

        return *tvptr;
    }
   


    //------------------//
    // Public Functions //
    //------------------//
    // Access or Controle Functions
    template <typename T>
    vec<T>::vec()
        : _size     {0}
        , _capacity {0}
        , _elem     {reinterpret_cast<T*>(std::malloc(0))}
    {
        #ifndef MATVEC_NO_EXCEPTION
        if(_elem==nullptr) throw failed_to_malloc{"mv::vec<T>::vec()", sizeof(T)*_size};
        #endif

        return;
    }
    

    template <typename T>
    vec<T>::vec(const vec<T>& vec_)
        : _size     {vec_._size}
        , _capacity {_size}
        , _elem     {reinterpret_cast<T*>(std::malloc(_size))}
    {
        #ifndef MATVEC_NO_EXCEPTION
        if(_elem==nullptr) throw failed_to_malloc{"mv::vec<T>::vec(const vec<T>&)", sizeof(T)*_size};
        #endif

        for(size_t a=0; a<_size; ++a) _elem[a]=vec_._elem[a];

        return;
    }
    
    
    template <typename T>
    vec<T>::vec(temp::vec<T>& vec_)
        : _size     {vec_._size}
        , _capacity {_size}
        , _elem     {reinterpret_cast<T*>(std::malloc(_size))}
    {
        #ifndef MATVEC_NO_EXCEPTION
        if(_elem==nullptr) throw failed_to_malloc{"mv::vec<T>::vec(const vec<T>&)", sizeof(T)*_size};
        #endif

        for(size_t a=0; a<_size; ++a) _elem[a]=vec_._elem[a];
        vec_.turn();

        return;
    }

    
    template <typename T>
    vec<T>::vec(size_t size_, const T& sca_)
        : _size     {size_}
        , _capacity {size_}
        , _elem     {reinterpret_cast<T*>(std::malloc(sizeof(T)*size_))}
    {
        #ifndef MATVEC_NO_EXCEPTION
        if(_elem==nullptr) throw failed_to_malloc{"mv::vec<T>::vec(size_, const T&)", sizeof(T)*_size};
        #endif

        for(size_t a=0; a<_size; ++a) _elem[a]=sca_;
    
        return;
    }

    
    template <typename T> template <typename... A>
    vec<T>::vec(size_t size_, A... args_)
        : _size     {size_}
        , _capacity {size_}
        , _elem     {reinterpret_cast<T*>(std::malloc(sizeof(T)*size_))}
    {
        #ifndef MATVEC_NO_EXCEPTION
        if(_elem==nullptr) throw failed_to_malloc{"mv::vec<T>::vec(size_, A...)", sizeof(T)*_size};
        #endif

        _input(0, args_...);

        return;
    }


    template <typename T>
    vec<T>::~vec(){
        _size    =0;
        _capacity=0;
        if(_elem!=nullptr){ std::free(_elem);  _elem=nullptr; }
        
        return;
    }

    

    // Access or Controle Functions
    template <typename T>
    size_t vec<T>::size() const{
     
        return _size;
    }


    template <typename T>
    size_t vec<T>::capacity() const{
        
        return _capacity;
    }


    template <typename T>
    size_t vec<T>::num() const{

        return _num;
    }
    
   
    template <typename T>
    vec<T>& vec<T>::auto_print(){

        for(size_t a=0; a<_size; ++a){
            std::cerr<<"["<<a<<"]: "<<_elem[a]<<std::endl;
        }
        std::cerr<<"Vector  : mv::vec"<<std::endl;
        std::cerr<<"Size    : "<<_size<<std::endl;
        std::cerr<<"Capacity: "<<_capacity<<std::endl;
        std::cerr<<"Elements: "<<_elem<<std::endl;
        std::cerr<<"Type    : "<<typeid(_elem[0]).name()<<std::endl;
        std::cerr<<std::endl;

        return *this;
    }
   

    template <typename T>
    T& vec<T>::operator[](size_t pos_){
        
        #ifndef MATVEC_NO_EXCEPTION
        if(pos_>=_capacity) throw over_capacity("vec<T>::operator[](size_t)", pos_, _capacity, _size);
        #endif
        
        return _elem[pos_];
    } 
 
    
    template <typename T>
    T* const vec<T>::elem(){

        return _elem;
    }


    template <typename T>
    void vec<T>::release_temp(){
        
        std::free(_vecs);
        _num  =0;
        _vecs=reinterpret_cast<temp::vec<T>*>(std::malloc(0));
        #ifndef MATVEC_NO_EXCEPTION
        if(_vecs==nullptr) throw failed_to_malloc{ "mv::vec<T>::release_temp()", 0 };
        #endif

        return;
    }
    
    
    template <typename T>
    void vec<T>::resize(size_t size_){
       
       if(size_>_capacity){
            if(void* ptr_=std::realloc(_elem, sizeof(T)*size_)){
                _elem=reinterpret_cast<T*>(ptr_);
                _capacity=size_;

            }else{
                _size    =0;
                _capacity=0;
                std::free(_elem);
                #ifndef MATVEC_NO_EXCEPTION
                throw failed_to_realloc{ "mv::vec<T>::resize(size_t)", _elem, sizeof(T)*size_ };
                #endif
                _elem=nullptr;
            }
        }
    
        _size=size_;

        return;
    }
    
    
    template <typename T>
    void vec<T>::resize(size_t size_, const T& sca_){
       
       if(size_>_capacity){
            if(void* ptr_=std::realloc(_elem, sizeof(T)*size_)){
                _elem=reinterpret_cast<T*>(ptr_);
                _capacity=size_;

            }else{
                _size    =0;
                _capacity=0;
                std::free(_elem);
                #ifndef MATVEC_NO_EXCEPTION
                throw failed_to_realloc{ "mv::vec<T>::resize(size_t, const T&)", _elem, sizeof(T)*size_ };
                #endif
                _elem=nullptr;
            }
        }
        
        if(size_>_size) for(size_t a=_size; a<size_; ++a) _elem[a]=sca_;
        
        _size=size_;

        return;
    }
 

    template <typename T>
    void vec<T>::reserve(size_t size_){
       
        if(size_>_capacity){
            if(void* ptr_=std::realloc(_elem, sizeof(T)*size_)){
                _elem=reinterpret_cast<T*>(ptr_);
                _capacity=size_;

            }else{
                _size    =0;
                _capacity=0;
                std::free(_elem);
                #ifndef MATVEC_NO_EXCEPTION
                throw failed_to_realloc{ "mv::vec<T>::reserve(size_t)", _elem, sizeof(T)*size_ };
                #endif
                _elem=nullptr;
            }
        }

        return;
    }
   

    template <typename T>
    T& vec<T>::push_back(const T& sca_){
    
        size_t size_=++_size;
        if(size_>_capacity){
            if(void* ptr_=std::realloc(_elem, sizeof(T)*size_)){
                _elem=reinterpret_cast<T*>(ptr_);
                _capacity=size_;

            }else{
                _size    =0;
                _capacity=0;
                std::free(_elem);
                #ifndef MATVEC_NO_EXCEPTION
                throw failed_to_realloc{ "mv::vec<T>::push_back(const T&)", _elem, sizeof(T)*size_ };
                #endif
                _elem=nullptr;
            }
        }

        return _elem[_size-1]=sca_;
    }



    // Sub Constant Functions
    template <typename T>
    temp::vec<T> vec<T>::normal(){
        
        temp::vec<T>& tvec=_find_free(_size);

        return tvec/(this->norm());
    }  


    template <typename T>
    temp::vec<T> vec<T>::image(T(& func_)(T)){
        
        temp::vec<T>& tvec=_find_free(_size);
        for(size_t a=0; a<_size; ++a) tvec[a]=func_(_elem[a]);
    
        return tvec;
    }


    template <typename T>
    temp::vec<T> vec<T>::image(T(& func_)(const T&)){
  
        temp::vec<T>& tvec=_find_free(_size);
        for(size_t a=0; a<_size; ++a) tvec[a]=func_(_elem[a]);
    
        return tvec;
    }


    template <typename T> template <typename... A>
    temp::vec<T> vec<T>::image(T(& func_)(T, A...), A... args_){
        
        temp::vec<T>& tvec=_find_free(_size);
        for(size_t a=0; a<_size; ++a) tvec[a]=func_(_elem[a], args_...);
    
        return tvec;
    }


    template <typename T> template <typename... A>
    temp::vec<T> vec<T>::image(T(& func_)(const T&, A...), A... args_){
     
        temp::vec<T>& tvec=_find_free(_size);
        for(size_t a=0; a<_size; ++a) tvec[a]=func_(_elem[a], args_...);
    
        return tvec;
    }


    template <typename T>
    T vec<T>::norm() const{

        return std::pow(this->square(), static_cast<T>(0.5));
    }


    template <typename T>
    T vec<T>::norm(const T& _sca) const{
        
        return std::pow(this->square(), static_cast<T>(1.0)/_sca);
    }


    template <typename T>
    T vec<T>::square() const{
        
        T ot=static_cast<T>(0.0);
        for(size_t a=0; a<_size; ++a) ot+=_elem[a]*_elem[a];

        return ot;
    }

/*

    // Constant Operators(vec<T>)
    template <typename T>
    vec<T> vec<T>::operator+(const vec<T>& _m33) const{

        return {x+_m33.x, y+_m33.y, z+_m33.z};
    }
    
    template <typename T>
    vec<T> vec<T>::operator-(const vec<T>& _m33) const{
        
        return {x-_m33.x, y-_m33.y, z-_m33.z};
    }

    template <typename T>
    vec<T> vec<T>::operator*(const vec<T>& _m33) const{
        
        return {x*_m33.x, y*_m33.y, z*_m33.z};
    }
    
    template <typename T>
    vec<T> vec<T>::operator|(const vec<T>& _m33) const{
        
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
    vec<T> vec<T>::operator/(const vec<T>& _m33) const{
        
        return {x/_m33.x, y/_m33.y, z/_m33.z};
    }

    template <typename T>
    vec<T> vec<T>::operator%(const vec<T>& _m33) const{
        
        return {x%_m33.x, y%_m33.y, z%_m33.z};
    }

    template <typename T>
    vec<T> vec<T>::operator+(const T& _s) const{
        
        return {x+_s, y+_s, z+_s};
    }
    
    template <typename T>
    vec<T> vec<T>::operator-(const T& _s) const{
        
        return {x-_s, y-_s, z-_s};
    }

    template <typename T>
    vec<T> vec<T>::operator*(const T& _s) const{
        
        return {x*_s, y*_s, z*_s};
    }

    template <typename T>
    vec<T> vec<T>::operator/(const T& _s) const{
        
        return {x/_s, y/_s, z/_s};
    }

    template <typename T>
    vec<T> vec<T>::operator%(const T& _s) const{
     
        return {x%_s, y%_s, z%_s};
    }

    template <typename T>
    vec<T> vec<T>::operator+() const{
        
        return *(this);
    }
    
    template <typename T>
    vec<T> vec<T>::operator-() const{
        
        return {-x, -y, -z};
    }
    
    template <typename T>
    vec<T> vec<T>::operator++(int) const{

        return {xx, yx, zx, xy, yy, zy, xz, yz, zz};
    }


    template <typename T>
    vec<T> vec<T>::operator~() const{
        
        return vec<T>(
            yy*zz-yz*zy, xz*zy-xy*zz, xy*yz-xz*yy,
            yz*zx-yx*zz, xx*zz-xz*zx, xz*yx-xx*yz,
            yx*zy-yy*zx, xy*zx-xx*zy, xx*yy-xy*yx
        )/(this->operator!());
    }

    // Constant Operators(vec3<T>)
    template <typename T>
    vec3<T> vec<T>::operator|(const vec3<T>& _v3) const{
     
        return {(x||_v3), (y||_v3), (z||_v3)};
    }

    template <typename T>
    vec3<T> vec<T>::operator*() const{
     
        return {yz, zx, xy};
    }

    // Constant Operators(T)
    template <typename T>
    T vec<T>::operator!() const{

        return xx*yy*zz+xy*yz*zx+xz*yx*zy-xz*yy*zx-xy*yx*zz-xx*yz*zy;
    }
 
    template <typename T>
    T vec<T>::operator--(int) const{

        return xx+yy+zz;
    }

    template <typename T>
    T vec<T>::operator||(const vec<T>& _m33) const{

        return x*_m33.x+y*_m33.y+z*_m33.z;
    }

    // Constant Operators(bool)
    template <typename T>
    bool vec<T>::operator==(const vec<T>& _m33) const{
        
        if(x==_m33.x && y==_m33.y && z==_m33.z) return true;
        else                                    return false;
    }

    template <typename T>
    bool vec<T>::operator!=(const vec<T>& _m33) const{
        
        if(x==_m33.x && y==_m33.y && z==_m33.z) return false;
        else                                    return true;
    }


    // Altering Functions
    template <typename T>
    vec<T>& vec<T>::zero(){

        return (*this)=(static_cast<T>(0.0));
    }
    
    template <typename T>
    vec<T>& vec<T>::ident(){

        return (*this)=vec3<T>(static_cast<T>(1.0));
    }
    
    template <typename T>
    vec<T>& vec<T>::normalize(){
        
        return (*this).operator/=(this->norm());
    }
             
    template <typename T>
    vec<T>& vec<T>::map(T(& _func)(T)){
        
        return (*this)=this->image(_func);
    }

    template <typename T>
    vec<T>& vec<T>::map(T(& _func)(const T&)){
        
        return (*this)=this->image(_func);
    }
    
    template <typename T> template <typename... A>
    vec<T>& vec<T>::map(T(& _func)(T, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    template <typename T> template <typename... A>
    vec<T>& vec<T>::map(T(& _func)(const T&, A...), A... _args){
    
        return (*this)=this->image<A...>(_func, _args...);
    }

    // Altering Operators
    template <typename T>
    vec<T>& vec<T>::operator+=(const vec<T>& _m33){

        return (*this)=this->operator+(_m33);
    }
    
    template <typename T>
    vec<T>& vec<T>::operator-=(const vec<T>& _m33){

        return (*this)=this->operator-(_m33);
    }
    
    template <typename T>
    vec<T>& vec<T>::operator*=(const vec<T>& _m33){

        return (*this)=this->operator*(_m33);
    }

    template <typename T>
    vec<T>& vec<T>::operator|=(const vec<T>& _m33){

        return (*this)=this->operator|(_m33);
    }

    template <typename T>
    vec<T>& vec<T>::operator/=(const vec<T>& _m33){

        return (*this)=this->operator/(_m33);
    }

    template <typename T>
    vec<T>& vec<T>::operator%=(const vec<T>& _m33){

        return (*this)=this->operator%(_m33);
    }

    template <typename T>
    vec<T>& vec<T>::operator+=(const T& _s){

        return (*this)=this->operator+(_s);
    }
    
    template <typename T>
    vec<T>& vec<T>::operator-=(const T& _s){

        return (*this)=this->operator-(_s);
    }

    template <typename T>
    vec<T>& vec<T>::operator*=(const T& _s){

        return (*this)=this->operator*(_s);
    }

    template <typename T>
    vec<T>& vec<T>::operator/=(const T& _s){

        return (*this)=this->operator/(_s);
    }

    template <typename T>
    vec<T>& vec<T>::operator%=(const T& _s){

        return (*this)=this->operator%(_s);
    }

    template <typename T>
    vec<T>& vec<T>::operator++(){

        return (*this)={++x, ++y, ++z};
    }
    
    template <typename T>
    vec<T>& vec<T>::operator--(){

        return (*this)={--x, --y, --z};
    }


    // Constant Functions
    template <typename T>
    size_t vec<T>::row() const{
        return __row;
    }


    template <typename T>
    size_t vec<T>::col() const{
        return __col;
    }


    template <typename T>
    size_t vec<T>::size() const{
        return __size;
    }


    template <typename T>
    size_t vec<T>::capacity() const{
        return __capacity;
    }

    template <typename T>
    const T& vec<T>::operator()(size_t _pos) const{
        return __elem[_pos];
    }

    template <typename T>
    T& vec<T>::operator[](size_t _pos){
        return __elem[_pos];
    }

    
*/
}


namespace mv{
    
    //++++++++++++++++++++++++++++++//
    //    Temporary Vector Class    //
    //++++++++++++++++++++++++++++++//
    // Constructor & Destructor
    template <typename T>
    temp::vec<T>::vec(bool flag_)
        : mv::vec<T> {10}
        , _flag       {flag_}
    {    
 
        return;
    }
        

    // Altering Functions
    template <typename T>
    bool temp::vec<T>::turn(){
        _flag=!_flag;

        return _flag;
    }
        

    // Access or Controle Functions
    template <typename T>
    temp::vec<T>& temp::vec<T>::auto_print(){

        for(size_t a=0; a<this->_size; ++a){
            std::cerr<<"["<<a<<"]: "<<this->_elem[a]<<std::endl;
        }
        std::cerr<<"Vector  : mv::temp::vec"<<std::endl;
        std::cerr<<"Size    : "<<this->_size<<std::endl;
        std::cerr<<"Capacity: "<<this->_capacity<<std::endl;
        std::cerr<<"Elements: "<<this->_elem<<std::endl;
        std::cerr<<"Flag    : "<<(_flag ? "true" : "false")<<std::endl;
        std::cerr<<"Type    : "<<typeid(this->_elem[0]).name()<<std::endl;
        std::cerr<<std::endl;

        return *this;
    }



    // Sub Constant Functions
    template <typename T>
    temp::vec<T>& temp::vec<T>::image(T(& func_)(T)){
            
        for(size_t a=0; a<this->_size; ++a) this->_elem[a]=func_(this->_elem[a]);

        return *this;
    }


    template <typename T>
    temp::vec<T>& temp::vec<T>::image(T(& func_)(const T&)){
  
        for(size_t a=0; a<this->_size; ++a) this->_elem[a]=func_(this->_elem[a]);

        return *this;
    }


    template <typename T> template <typename... A>
    temp::vec<T>& temp::vec<T>::image(T(& func_)(T, A...), A... args_){
        
        for(size_t a=0; a<this->_size; ++a) this->_elem[a]=func_(this->_elem[a], args_...);
    
        return *this;
    }


    template <typename T> template <typename... A>
    temp::vec<T>& temp::vec<T>::image(T(& func_)(const T&, A...), A... args_){
     
        for(size_t a=0; a<this->_size; ++a) this->_elem[a]=func_(this->_elem[a], args_...);
    
        return *this;
    }
}


/*
// General Functions
template <typename T>
std::ostream& operator<<(std::ostream& _os, const mv::vec<T>& _m){
    
    for(size_t a=0, b=0; a<_m.col(); ++a, b+=_m.row()){
        if(b!=0) _os<<"\n";
        for(size_t c=0; c<_m.row(); ++c){
            const T sca=_m(b+c);
            _os<<sca<<" ";
        }
    }

    return _os;
}
*/

#endif
