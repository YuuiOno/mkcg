#ifndef MATVEC_MV_VECN_CPP
#define MATVEC_MV_VECN_CPP

#include "vecn.hpp"

#include <cmath>

namespace mv{
    
    // Constructors & Destructor
    template <typename T, size_t N>
    vecn<T,N>::vecn(void)
         : cmp { }
    {
        for(size_t a=0; a<N; ++a) new(&cmp+a) T();

        return;
    }


    template <typename T, size_t N>
    vecn<T,N>::vecn(const T& sca_)
        : cmp { }
    {
        for(size_t a=0; a<N; ++a) new(&cmp+a) T(sca_);
        
        return;
    }

   

    template <typename T, size_t N>
    vecn<T,N>::vecn(const std::initializer_list<T>& list_)
        : cmp { }
    {
        for(size_t a=0; a<N; ++a) new(&cmp+a) T(*(list_.begin()+a));
        
        return;
    }


    template <typename T, size_t N>
    vecn<T,N>::vecn(const vecn<T,N>& vn_)
        : cmp { }
    {

        for(size_t a=0; a<N; ++a) new(&cmp+a) T(vn_(a));
        
        return;
    }


    template <typename T, size_t N>
    vecn<T,N>::~vecn(void){
    
        return;
    }



    // Access Function
    template <typename T, size_t N>
    size_t vecn<T,N>::dim(void) const{

        return N;
    }


    template <typename T, size_t N>
    T& vecn<T,N>::operator[](size_t index_){

        return cmp[index_];
    }
    
    
    template <typename T, size_t N>
    const T& vecn<T,N>::operator()(size_t index_) const{

        return cmp[index_];
    }




    // Constant Functions(vecn<T,N>)
    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::normal(void) const{
        
        return (*this)/(this->norm());
    }


    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::image(T(& func_)(T)) const{
        
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=func_(cmp[a]);
        
        return ot;
    }


    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::image(T(& func_)(const T&)) const{
      
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=func_(cmp[a]);
        
        return ot;
    }


    template <typename T, size_t N> template <typename... A>
    vecn<T,N> vecn<T,N>::image(T(& func_)(T, A...), A... args_) const{
 
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=func_(cmp[a], args_...);
        
        return ot;
    }


    template <typename T, size_t N> template <typename... A>
    vecn<T,N> vecn<T,N>::image(T(& _func)(const T&, A...), A... args_) const{
    
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=func_(cmp[a], args_...);
        
        return ot;
    }


    // Constant Functions(T)
    template <typename T, size_t N>
    T vecn<T,N>::norm(void) const{

        T t=static_cast<T>(0);
        for(size_t a=0; a<N; ++a) t+=cmp[a]*cmp[a];

        return std::pow(t, static_cast<T>(0.5));
    }


    template <typename T, size_t N>
    T vecn<T,N>::norm(const T& s_ca) const{

        T t=static_cast<T>(0);
        for(size_t a=0; a<N; ++a) t+=cmp[a]*cmp[a];

        return std::pow(t, static_cast<T>(1.0)/s_ca);
    }

    template <typename T, size_t N>
    T vecn<T,N>::square(void) const{
     
        T t=static_cast<T>(0);
        for(size_t a=0; a<N; ++a) t+=cmp[a]*cmp[a];

        return t;
    }



    // Constant Functions(void)
    template <typename T, size_t N>
    void vecn<T,N>::autoPrint(void) const{

        for(size_t a=0; a<N; ++a) std::cerr<<"["<<a<<"]: "<<cmp[a]<<std::endl;
        std::cerr<<"dim : "<<N<<std::endl;
        std::cerr<<"Type: "<<typeid(cmp[0]).name()<<std::endl;
        std::cerr<<"Size: "<<sizeof(*this)<<std::endl;
        std::cerr<<std::endl;

        return;
    }


    // Constant Operators(vecn<T,N>)
    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator+(const vecn<T,N>& vn_) const{

        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]+vn_[a];

        return ot;
    }
    
    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator-(const vecn<T,N>& vn_) const{
        
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]-vn_[a];

        return ot;
    }

    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator*(const vecn<T,N>& vn_) const{
        
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]*vn_[a];

        return ot;
    }
    
    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator/(const vecn<T,N>& vn_) const{
     
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]/vn_[a];

        return ot;
    }

    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator%(const vecn<T,N>& vn_) const{
        
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]%vn_[a];

        return ot;
    }


    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator+(const T& s_) const{
        
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]+s_;

        return ot;
    }


    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator-(const T& s_) const{
        
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]-s_;

        return ot;
    }

    
    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator*(const T& s_) const{
        
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]*s_;

        return ot;
    }


    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator/(const T& s_) const{
        
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=cmp[a]/s_;

        return ot;
    }


    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator+(void) const{
        
        return *(this);
    }
    

    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator-(void) const{
       
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=-cmp[a];

        return ot;
    }


    template <typename T, size_t N>
    vecn<T,N> vecn<T,N>::operator~(void) const{
       
        vecn<T,N> ot;
        for(size_t a=0; a<N; ++a) ot[a]=static_cast<T>(1.0)/cmp[a];

        return ot;
    }



    // Constant Operators(T)
    template <typename T, size_t N>
    T vecn<T,N>::operator!(void) const{

        T t=cmp[0];
        for(size_t a=1; a<N; ++a) t*=cmp[a];

        return t;
    }
    
    template <typename T, size_t N>
    T vecn<T,N>::operator--(int) const{
        
        T t=cmp[0];
        for(size_t a=1; a<N; ++a) t+=cmp[a];

        return t;
    }

    template <typename T, size_t N>
    T vecn<T,N>::operator||(const vecn<T,N>& vn_) const{

        T t=cmp[0]*vn_[0];
        for(size_t a=1; a<N; ++a) t+=cmp[a]*vn_[a];
        
        return t;
    }



    // Constant Operators(bool)
    template <typename T, size_t N>
    bool vecn<T,N>::operator==(const vecn<T,N>& vn_) const{
        
        for(size_t a=0; a<N; ++a) if(cmp[a]!=vn_[a]) return false;

        return true;
    }


    template <typename T, size_t N>
    bool vecn<T,N>::operator!=(const vecn<T,N>& vn_) const{
     
        for(size_t a=0; a<N; ++a) if(cmp[a]!=vn_[a]) return true;

        return false;
    }



    // Altering Functions
    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::zero(void){

        return (*this)={(static_cast<T>(0.0))};
    }
    

    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::ident(void){

        return (*this)={(static_cast<T>(1.0))};
    }
    

    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::normalize(void){
        
        return (*this).operator/=(this->norm());
    }
        
        
    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::map(T(& _func)(T)){
        
        return (*this)=this->image(_func);
    }


    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::map(T(& _func)(const T&)){
        
        return (*this)=this->image(_func);
    }


    template <typename T, size_t N> template <typename... A>
    vecn<T,N>& vecn<T,N>::map(T(& _func)(T, A...), A... args_){
    
        return (*this)=this->image<A...>(_func, args_...);
    }


    template <typename T, size_t N> template <typename... A>
    vecn<T,N>& vecn<T,N>::map(T(& _func)(const T&, A...), A... args_){
    
        return (*this)=this->image<A...>(_func, args_...);
    }


    
    // Altering Operators
    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator+=(const vecn<T,N>& vn_){

        for(size_t a=0; a<N; ++a) cmp[a]+=vn_[a];

        return *this;
    }


    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator-=(const vecn<T,N>& vn_){

        for(size_t a=0; a<N; ++a) cmp[a]-=vn_[a];

        return *this;
    }


    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator*=(const vecn<T,N>& vn_){

        for(size_t a=0; a<N; ++a) cmp[a]*=vn_[a];

        return *this;
    }


    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator/=(const vecn<T,N>& vn_){

        for(size_t a=0; a<N; ++a) cmp[a]/=vn_[a];

        return *this;
    }


    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator%=(const vecn<T,N>& vn_){

        for(size_t a=0; a<N; ++a) cmp[a]%=vn_[a];

        return *this;
    }


    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator+=(const T& s_){

        for(size_t a=0; a<N; ++a) cmp[a]+=s_;

        return *this;
    }


    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator-=(const T& s_){

        for(size_t a=0; a<N; ++a) cmp[a]-=s_;

        return *this;
    }


    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator*=(const T& s_){

        for(size_t a=0; a<N; ++a) cmp[a]*=s_;

        return *this;
    }

    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator/=(const T& s_){

        for(size_t a=0; a<N; ++a) cmp[a]/=s_;

        return *this;
    }

    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator%=(const T& s_){

        for(size_t a=0; a<N; ++a) cmp[a]%=s_;

        return *this;
    }

    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator++(){

        for(size_t a=0; a<N; ++a) cmp[a]++;

        return *this;
    }
    
    template <typename T, size_t N>
    vecn<T,N>& vecn<T,N>::operator--(){

        for(size_t a=0; a<N; ++a) cmp[a]--;

        return *this;
    }
}


// General Functions
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& _os, const mv::vecn<T,N>& vn_){
    
    _os<<vn_[0];
    for(size_t a=1; a<N; ++a) _os<<" "<<vn_[a];
    
    return _os;
}
#endif
