#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

#ifndef MATVEC_HPP
#define MATVEC_HPP
//#define MATVEC_UNSAFETY
//#define OLD_GPP

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;
typedef double mvsca;
typedef float mvscaf;

namespace matvec{
	template <typename type=float> class flag;
	template <typename type=float> struct vec3;
	template <typename type=float> struct mat33;
	template <typename type=float> struct vec2;
	template <typename type=float> class mat;

	/* CPYFLAG CLASS */
	template <typename type> class cpyflag{
		bool flag;
	
		public:
		cpyflag();
		bool turn();
		bool out() const;
		cpyflag operator +() const;
		cpyflag operator -() const;
	};

	/* VEC3 STRUCT */
	template <typename type> struct vec3{
		type x;
		type y;
		type z;
	
		//Constructor
		vec3();
		vec3(const type);
		vec3(const type, const type, const type);
		vec3(const matvec::vec3<type>&);
		//Destructor
		~vec3();
		//Modification
		vec3<type>& in(const type, const type, const type);
		vec3<type>& func(type (*)(const type));
		vec3<type>& func(type (*)(const type, const type), const type);
		vec3<type>& zero();
		vec3<type>& normalize();
		//Substitution	
		vec3<type>& operator =(const vec3<type>&);
		vec3<type>& operator +=(const vec3<type>&);
		vec3<type>& operator -=(const vec3<type>&);
		vec3<type>& operator *=(const vec3<type>&);				//Hadamard Product
		vec3<type>& operator &=(const vec3<type>&);				//Outer Product
		vec3<type>& operator /=(const vec3<type>&);				//Hadamard Division
		vec3<type>& operator =(const type);
		vec3<type>& operator +=(const type);
		vec3<type>& operator -=(const type);
		vec3<type>& operator *=(const type);
		vec3<type>& operator /=(const type);
		//Calculation
		vec3<type> operator +(const vec3<type>&) const;
		vec3<type> operator -(const vec3<type>&) const;
		vec3<type> operator *(const vec3<type>&) const;			//Hadamard Product
		vec3<type> operator &(const vec3<type>&) const;			//Outer Product
		vec3<type> operator /(const vec3<type>&) const;			//Hadamard Division
		vec3<type> operator +(const type) const;
		vec3<type> operator -(const type) const;
		vec3<type> operator *(const type) const;
		vec3<type> operator /(const type) const;
		vec3<type> operator -() const;
		bool operator !() const;
		type operator ||(const vec3<type>&) const;				//Inner Product
		mat33<type> operator &&(const vec3<type>&) const;		//Tensor Product
		//Logical
		vec3<type> operator ==(const vec3<type>&) const;
		//Function
		type size() const;
		type sizep2() const;
		type volume() const;
		vec3<type> normal() const;
		void print() const;
		void print(const std::string) const;
		void print(const std::string, const std::string) const;
		//Friend Function
	};

	/* MAT33 STRUCT */
	template <typename type> struct mat33{
		type xx;
		type xy;
		type xz;
		type yx;
		type yy;
		type yz;
		type zx;
		type zy;
		type zz;
	
		//Constructor
		mat33();
		mat33(const vec3<type>&, const vec3<type>&, const vec3<type>&);
		mat33(const type, const type, const type,
		      const type, const type, const type,
		      const type, const type, const type);
		//Destructor
		~mat33();
		//Modification
		mat33<type>& in(const type, const type, const type,
		                const type, const type, const type,
		                const type, const type, const type);
		mat33<type>& func(type (*)(const type));
		mat33<type>& func(type (*)(const type, const type), const type);
		mat33<type>& zero();
		mat33<type>& ident();
		//Substitution	
		mat33<type>& operator =(const mat33<type>&);
		mat33<type>& operator +=(const mat33<type>&);
		mat33<type>& operator -=(const mat33<type>&);
		mat33<type>& operator *=(const mat33<type>&);		//Hadamard Product
		mat33<type>& operator /=(const mat33<type>&);		//Hadamard Division
		mat33<type>& operator |=(const mat33<type>&);		//Matrix Product
		mat33<type>& operator =(const type);
		mat33<type>& operator +=(const type);
		mat33<type>& operator -=(const type);
		mat33<type>& operator *=(const type);
		mat33<type>& operator /=(const type);
		//Calculation
		mat33<type> operator +(const mat33<type>&) const;
		mat33<type> operator -(const mat33<type>&) const;
		mat33<type> operator *(const mat33<type>&) const;	//Hadamard Product
		mat33<type> operator /(const mat33<type>&) const;	//Hadamard Division
		mat33<type> operator |(const mat33<type>&) const;	//Matrix Product
		vec3<type> operator |(const vec3<type>&) const;     //Matrix Product
		mat33<type> operator +(const type) const;
		mat33<type> operator -(const type) const;
		mat33<type> operator *(const type) const;
		mat33<type> operator /(const type) const;
		mat33<type> operator -() const;
		mat33<type> operator ~() const;						//Inverse
		mat33<type> operator !() const;						//Transpose
		type operator ||(const mat33<type>&) const;			//Inner Product
		//Function
		type trace() const;
		type det() const;
		void print() const;
		void print(const std::string) const;
		void print(const std::string, const std::string) const;
		//Friend Function
	};
    
    /* VEC2 STRUCT */
    template <typename type> struct vec2{
		type x;
		type y;
    };

	/* MAT CLASS */
	template <typename type> class mat{
		uint row_;
		uint col_;
		uint total_;
		type* elem_;

		static uint _row_;
		static uint _col_;
		static uint _total_;
		public:
		static type* _elem_;

		public:
		//Constructor
		mat();
		mat(const uint, const uint);
		mat(const uint, const uint, const type);
		template <typename... arg>
		mat(const uint, const uint, const type, const arg...);
		//Destructor
		~mat();
		//Modification
		mat<type>& matrix(const uint, const uint);
		mat<type>& matrix(const uint, const uint, const type);
		template <typename... arg>
		mat<type>& matrix(const uint, const uint, const type, const arg...);
		mat<type>& vector(const uint);
		mat<type>& vector(const uint, const type);
		template <typename... arg>
		mat<type>& vector(const uint, const type, const arg...);
		mat<type>& func(type (*)(const type));
		mat<type>& func(type (*)(const type, const type), const type);
		mat<type>& zero();
		mat<type>& ident();
		
		//Substitution	
		mat<type>& operator =(const mat<type>&);
		mat<type>& operator +=(const mat<type>&);
		mat<type>& operator -=(const mat<type>&);
		mat<type>& operator *=(const mat<type>&);		//Hadamard Product
		mat<type>& operator /=(const mat<type>&);		//Hadamard Division
		mat<type>& operator |=(const mat<type>&);		//Matrix Product
		mat<type>& operator =(const cpyflag<type>);
		mat<type>& operator +=(const cpyflag<type>);
		mat<type>& operator -=(const cpyflag<type>);
		mat<type>& operator *=(const cpyflag<type>);	//Hadamard Product	
		mat<type>& operator /=(const cpyflag<type>);	//Hadamard Division
		mat<type>& operator =(const type);
		mat<type>& operator +=(const type);
		mat<type>& operator -=(const type);
		mat<type>& operator *=(const type);			//Hadamard Product
		mat<type>& operator /=(const type);			//Hadamard Division
	
		//Calculation
		cpyflag<type> operator +(const mat<type>&) const;
		cpyflag<type> operator -(const mat<type>&) const;
		cpyflag<type> operator *(const mat<type>&) const;	//Hadamard Product
		cpyflag<type> operator /(const mat<type>&) const;	//Hadamard Division
		cpyflag<type> operator |(const mat<type>&) const; //Matrix Product
		cpyflag<type> operator +(const type) const;
		cpyflag<type> operator -(const type) const;
		cpyflag<type> operator *(const type) const;
		cpyflag<type> operator /(const type) const;
		cpyflag<type> operator -() const;
	
		//Function
		const uint row() const;
		const uint column() const;
		const uint total() const;
		const type* elements() const;
		type& operator [](const uint) const;
		const uint buffer_row() const;
		const uint buffer_column() const;
		const uint buffer_total() const;
		const type* buffer_elements() const;
		void buffer_print() const;

		private:
		//Private Function
		template<typename... arg>
		void input(const uint, const type, const arg...);
		void input(const uint);
/*		mat33<type> operator -() const;
		mat33<type> operator ~() const;						//Inverse
		mat33<type> operator !() const;						//Transpose
		type operator ||(const mat33<type>&) const;			//Inner Product
		//Function
		type trace() const;
		type det() const;
		void print() const;
		void print(const std::string) const;
		void print(const std::string, const std::string) const;
*/

		friend class cpyflag<type>;
	};
	template <typename type> uint mat<type>::_row_=0;
	template <typename type> uint mat<type>::_col_=0;
	template <typename type> uint mat<type>::_total_=0;
	template <typename type> type* mat<type>::_elem_=NULL;



/*******************************/
/*          Functions          */
/*******************************/
	/* Class CPYFLAG */
	template<typename type>
	cpyflag<type>::cpyflag(){
		flag=true;
	}
	template<typename type>
	bool cpyflag<type>::turn(){
		flag=false;
		return flag;
	}
	template<typename type>
	bool cpyflag<type>::out() const{
		return flag;
	}
	template<typename type>
	cpyflag<type> cpyflag<type>::operator -() const{
		uint total=mat<type>::_total_;
		type* elem=mat<type>::_elem_;
		for(uint a=0; a<total; ++a) elem[a]=-elem[a];

		return *this;
	}
	template<typename type>
	cpyflag<type> cpyflag<type>::operator +() const{

		return *this;
	}

	
	/* STRUCT VEC3 */
	//Constructor
	template <typename type>
	vec3<type>::vec3(){
		std::memset(this, 0, sizeof(vec3<type>));
	}
	template<typename type>
	vec3<type>::vec3(const type i_sca){
		x=i_sca;
		y=i_sca;
		z=i_sca;
	}
	template<typename type>
	vec3<type>::vec3(const type i_x, const type i_y, const type i_z){
		x=i_x;
		y=i_y;
		z=i_z;
	}
	template<typename type>
	vec3<type>::vec3(const matvec::vec3<type>& i_vec){
		x=i_vec.x;
		y=i_vec.y;
		z=i_vec.z;
	}

	//Destructor
	template<typename type>
	vec3<type>::~vec3(){}

	//Modification
	template<typename type>
	vec3<type>& vec3<type>::in(const type i_x, const type i_y, const type i_z){
		x=i_x;
		y=i_y;
		z=i_z;
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::func(type (*i_func)(const type)){
		x=i_func(x);
		y=i_func(y);
		z=i_func(z);
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::func(type (*i_func)(const type, const type), const type i_sca){
		x=i_func(x, i_sca);
		y=i_func(y, i_sca);
		z=i_func(z, i_sca);
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::zero(){
		std::memset(this, 0, sizeof(vec3<type>));
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::normalize(){
		type sca=std::sqrt(x*x+y*y+z*z);
		x/=sca;
		y/=sca;
		z/=sca;
		return *this;
	}

	//Substitution	
	template<typename type> 
	vec3<type>& vec3<type>::operator =(const vec3<type>& i_vec){
		x=i_vec.x;
		y=i_vec.y;
		z=i_vec.z;
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::operator +=(const vec3<type>& i_vec){
		x+=i_vec.x;
		y+=i_vec.y;
		z+=i_vec.z;
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::operator -=(const vec3<type>& i_vec){
		x-=i_vec.x;
		y-=i_vec.y;
		z-=i_vec.z;
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::operator *=(const vec3<type>& i_vec){
		x*=i_vec.x;
		y*=i_vec.y;
		z*=i_vec.z;
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::operator &=(const vec3<type>& i_vec){
		vec3<type> temp;
		temp.x=y*i_vec.z-z*i_vec.y;
		temp.y=z*i_vec.x-x*i_vec.z;
		temp.z=x*i_vec.y-y*i_vec.x;
		*this=temp;
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::operator /=(const vec3<type>& i_vec){
		x/=i_vec.x;
		y/=i_vec.y;
		z/=i_vec.z;
		return *this;
	}
	template<typename type> 
	vec3<type>& vec3<type>::operator =(const type i_sca){
		x=i_sca;
		y=i_sca;
		z=i_sca;
		return *this;
	};
	template<typename type> 
	vec3<type>& vec3<type>::operator +=(const type i_sca){
		x+=i_sca;
		y+=i_sca;
		z+=i_sca;
		return *this;
	};
	template<typename type> 
	vec3<type>& vec3<type>::operator -=(const type i_sca){
		x-=i_sca;
		y-=i_sca;
		z-=i_sca;
		return *this;
	};
	template<typename type> 
	vec3<type>& vec3<type>::operator *=(const type i_sca){
		x*=i_sca;
		y*=i_sca;
		z*=i_sca;
		return *this;
	};
	template<typename type> 
	vec3<type>& vec3<type>::operator /=(const type i_sca){
		x/=i_sca;
		y/=i_sca;
		z/=i_sca;
		return *this;
	};
	
	//Calculation
	template<typename type> 
	vec3<type> vec3<type>::operator +(const vec3<type>& i_vec) const{
		vec3<type> ot;
		ot.x=x+i_vec.x;
		ot.y=y+i_vec.y;
		ot.z=z+i_vec.z;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator -(const vec3<type>& i_vec) const{
		vec3<type> ot;
		ot.x=x-i_vec.x;
		ot.y=y-i_vec.y;
		ot.z=z-i_vec.z;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator *(const vec3<type>& i_vec) const{
		vec3<type> ot;
		ot.x=x*i_vec.x;
		ot.y=y*i_vec.y;
		ot.z=z*i_vec.z;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator &(const vec3<type>& i_vec) const{
		vec3<type> ot;
		ot.x=y*i_vec.z-z*i_vec.y;
		ot.y=z*i_vec.x-x*i_vec.z;
		ot.z=x*i_vec.y-y*i_vec.x;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator /(const vec3<type>& i_vec) const{
		vec3<type> ot;
		ot.x=x/i_vec.x;
		ot.y=y/i_vec.y;
		ot.z=z/i_vec.z;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator +(const type i_sca) const{
		vec3<type> ot;
		ot.x=x+i_sca;
		ot.y=y+i_sca;
		ot.z=z+i_sca;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator -(const type i_sca) const{
		vec3<type> ot;
		ot.x=x-i_sca;
		ot.y=y-i_sca;
		ot.z=z-i_sca;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator *(const type i_sca) const{
		vec3<type> ot;
		ot.x=x*i_sca;
		ot.y=y*i_sca;
		ot.z=z*i_sca;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator /(const type i_sca) const{
		vec3<type> ot;
		ot.x=x/i_sca;
		ot.y=y/i_sca;
		ot.z=z/i_sca;
		return ot;
	}
	template<typename type> 
	vec3<type> vec3<type>::operator -() const{
		vec3<type> ot;
		ot.x=-x;
		ot.y=-y;
		ot.z=-z;
		return ot;
	}
	template<typename type> 
	bool vec3<type>::operator !() const{
        if(x==0.0f && y==0.0f && z==0.0f) return true;
        else                              return false;      
    }
	template<typename type> 
	type vec3<type>::operator ||(const vec3<type>& i_vec) const{
		return x*i_vec.x+y*i_vec.y+z*i_vec.z;
	}
	template<typename type> 
	mat33<type> vec3<type>::operator &&(const vec3<type>& i_vec) const{
		mat33<type> ot(x*i_vec.x, y*i_vec.x, z*i_vec.x,
		               x*i_vec.y, y*i_vec.y, z*i_vec.y,
		               x*i_vec.z, y*i_vec.z, z*i_vec.z);
		return ot;
	}
	
	//Function
	template<typename type> 
	type vec3<type>::size() const{
		return std::sqrt(x*x+y*y+z*z);
	}
	template<typename type> 
	type vec3<type>::sizep2() const{
		return x*x+y*y+z*z;
	}
	template<typename type> 
	type vec3<type>::volume() const{
		return x*y*z;
	}
    template<typename type> 
	vec3<type> vec3<type>::normal() const{
		vec3<type> ot=*this;
		ot/=std::sqrt(x*x+y*y+z*z);

        return ot;
	}
	template<typename type> 
	void vec3<type>::print() const{
		std::cout<<std::scientific<<std::setprecision(2);
		std::cout<<x<<" "<<y<<" "<<z<<std::endl;
#ifndef OLD_GPP
		std::cout<<std::defaultfloat;
#endif
		return;
	}
	template<typename type> 
	void vec3<type>::print(const std::string i_str) const{
		std::string str=i_str+" "+i_str+" "+i_str+"\n";
		std::printf(str.c_str(), x, y, z);	
		return;
	}
	template<typename type> 
	void vec3<type>::print(const std::string i_str1, const std::string i_str2) const{
		std::string str=i_str1+"\n"+i_str2+" "+i_str2+" "+i_str2+"\n";
		std::printf(str.c_str(), x, y, z);	
		return;
	}


	/* MAT33 STRUCT */
	//Constructor
	template<typename type> 
	mat33<type>::mat33(){}
	template<typename type> 
	mat33<type>::mat33(const vec3<type>& i_vec1, const vec3<type>& i_vec2, const vec3<type>& i_vec3){
		xx=i_vec1.x;    xy=i_vec1.y;    xz=i_vec1.z;
		yx=i_vec2.x;    yy=i_vec2.y;    yz=i_vec2.z;
		zx=i_vec3.x;    zy=i_vec3.y;    zz=i_vec3.z;
	}
	template<typename type> 
	mat33<type>::mat33(const type i_xx, const type i_xy, const type i_xz,
		               const type i_yx, const type i_yy, const type i_yz,
		               const type i_zx, const type i_zy, const type i_zz){
		xx=i_xx;    xy=i_xy;    xz=i_xz;  
		yx=i_yx;    yy=i_yy;    yz=i_yz;  
		zx=i_zx;    zy=i_zy;    zz=i_zz;  
	}
	//Destructor
	template<typename type> 
	mat33<type>::~mat33(){}

	//Modification
	template<typename type> 
	mat33<type>& mat33<type>::in(const type i_xx, const type i_xy, const type i_xz,
		                         const type i_yx, const type i_yy, const type i_yz,
		                         const type i_zx, const type i_zy, const type i_zz){
		xx=i_xx;    xy=i_xy;    xz=i_xz;  
		yx=i_yx;    yy=i_yy;    yz=i_yz;  
		zx=i_zx;    zy=i_zy;    zz=i_zz;  
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::func(type (*i_func)(const type)){
		xx=i_func(xx);    xy=i_func(xy);    xz=i_func(xz);
		yx=i_func(yx);    yy=i_func(yy);    yz=i_func(yz);
		zx=i_func(zx);    zy=i_func(zy);    zz=i_func(zz);
		return *this;
	}	
	template<typename type> 
	mat33<type>& mat33<type>::func(type (*i_func)(const type, const type), const type i_sca){
		xx=i_func(xx, i_sca);    xy=i_func(xy, i_sca);    xz=i_func(xz, i_sca);
		yx=i_func(yx, i_sca);    yy=i_func(yy, i_sca);    yz=i_func(yz, i_sca);
		zx=i_func(zx, i_sca);    zy=i_func(zy, i_sca);    zz=i_func(zz, i_sca);
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::zero(){
		std::memset(this, 0, sizeof(mat33<type>));
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::ident(){
		xx=1;    xy=0;    xz=0;
		yx=0;    yy=1;    yz=0;
		zx=0;    zy=0;    zz=1;
		return *this;
	}

	//Substitution	
	template<typename type> 
	mat33<type>& mat33<type>::operator =(const mat33<type>& i_mat){
		xx=i_mat.xx;    xy=i_mat.xy;    xz=i_mat.xz;  
		yx=i_mat.yx;    yy=i_mat.yy;    yz=i_mat.yz;  
		zx=i_mat.zx;    zy=i_mat.zy;    zz=i_mat.zz;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator +=(const mat33<type>& i_mat){
		xx+=i_mat.xx;    xy+=i_mat.xy;    xz+=i_mat.xz;  
		yx+=i_mat.yx;    yy+=i_mat.yy;    yz+=i_mat.yz;  
		zx+=i_mat.zx;    zy+=i_mat.zy;    zz+=i_mat.zz;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator -=(const mat33<type>& i_mat){
		xx-=i_mat.xx;    xy-=i_mat.xy;    xz-=i_mat.xz;  
		yx-=i_mat.yx;    yy-=i_mat.yy;    yz-=i_mat.yz;  
		zx-=i_mat.zx;    zy-=i_mat.zy;    zz-=i_mat.zz;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator *=(const mat33<type>& i_mat){
		xx*=i_mat.xx;    xy*=i_mat.xy;    xz*=i_mat.xz;  
		yx*=i_mat.yx;    yy*=i_mat.yy;    yz*=i_mat.yz;  
		zx*=i_mat.zx;    zy*=i_mat.zy;    zz*=i_mat.zz;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator /=(const mat33<type>& i_mat){
		xx/=i_mat.xx;    xy/=i_mat.xy;    xz/=i_mat.xz;  
		yx/=i_mat.yx;    yy/=i_mat.yy;    yz/=i_mat.yz;  
		zx/=i_mat.zx;    zy/=i_mat.zy;    zz/=i_mat.zz;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator |=(const mat33<type>& i_mat){
			mat33<type> ot;
			type sx[9]={xx,yx,zx, xy,yy,zy, xz,yz,zz};
	
			ot.xx=sx[0]*i_mat.xx+sx[1]*i_mat.xy+sx[2]*i_mat.xz;
			ot.xy=sx[3]*i_mat.xx+sx[4]*i_mat.xy+sx[5]*i_mat.xz;
			ot.xz=sx[6]*i_mat.xx+sx[7]*i_mat.xy+sx[8]*i_mat.xz;
		
			ot.yx=sx[0]*i_mat.yx+sx[1]*i_mat.yy+sx[2]*i_mat.yz;
			ot.yy=sx[3]*i_mat.yx+sx[4]*i_mat.yy+sx[5]*i_mat.yz;
			ot.yz=sx[6]*i_mat.yx+sx[7]*i_mat.yy+sx[8]*i_mat.yz;

			ot.zx=sx[0]*i_mat.zx+sx[1]*i_mat.zy+sx[2]*i_mat.zz;
			ot.zy=sx[3]*i_mat.zx+sx[4]*i_mat.zy+sx[5]*i_mat.zz;
			ot.zz=sx[6]*i_mat.zx+sx[7]*i_mat.zy+sx[8]*i_mat.zz;

			*this=ot;
		
			return *this;	
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator =(const type i_sca){
		xx=i_sca;    xy=i_sca;    xz=i_sca;  
		yx=i_sca;    yy=i_sca;    yz=i_sca;  
		zx=i_sca;    zy=i_sca;    zz=i_sca;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator +=(const type i_sca){
		xx+=i_sca;    xy+=i_sca;    xz+=i_sca;  
		yx+=i_sca;    yy+=i_sca;    yz+=i_sca;  
		zx+=i_sca;    zy+=i_sca;    zz+=i_sca;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator -=(const type i_sca){
		xx-=i_sca;    xy-=i_sca;    xz-=i_sca;  
		yx-=i_sca;    yy-=i_sca;    yz-=i_sca;  
		zx-=i_sca;    zy-=i_sca;    zz-=i_sca;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator *=(const type i_sca){
		xx*=i_sca;    xy*=i_sca;    xz*=i_sca;  
		yx*=i_sca;    yy*=i_sca;    yz*=i_sca;  
		zx*=i_sca;    zy*=i_sca;    zz*=i_sca;
		return *this;
	}
	template<typename type> 
	mat33<type>& mat33<type>::operator /=(const type i_sca){
		xx/=i_sca;    xy/=i_sca;    xz/=i_sca;  
		yx/=i_sca;    yy/=i_sca;    yz/=i_sca;  
		zx/=i_sca;    zy/=i_sca;    zz/=i_sca;
		return *this;
	}
	
	//Calculation
	template<typename type> 
	mat33<type> mat33<type>::operator +(const mat33<type>& i_mat) const{
		mat33<type> ot;
		ot.xx=xx+i_mat.xx;    ot.xy=xy+i_mat.xy;    ot.xz=xz+i_mat.xz;
		ot.yx=yx+i_mat.yx;    ot.yy=yy+i_mat.yy;    ot.yz=yz+i_mat.yz;
		ot.zx=zx+i_mat.zx;    ot.zy=zy+i_mat.zy;    ot.zz=zz+i_mat.zz;
		return ot;
	}
	template<typename type> 
	mat33<type> mat33<type>::operator -(const mat33<type>& i_mat) const{
		mat33<type> ot;
		ot.xx=xx-i_mat.xx;    ot.xy=xy-i_mat.xy;    ot.xz=xz-i_mat.xz;
		ot.yx=yx-i_mat.yx;    ot.yy=yy-i_mat.yy;    ot.yz=yz-i_mat.yz;
		ot.zx=zx-i_mat.zx;    ot.zy=zy-i_mat.zy;    ot.zz=zz-i_mat.zz;
		return ot;
	}
	template<typename type> 
	mat33<type> mat33<type>::operator *(const mat33<type>& i_mat) const{
		mat33<type> ot;
		ot.xx=xx*i_mat.xx;    ot.xy=xy*i_mat.xy;    ot.xz=xz*i_mat.xz;
		ot.yx=yx*i_mat.yx;    ot.yy=yy*i_mat.yy;    ot.yz=yz*i_mat.yz;
		ot.zx=zx*i_mat.zx;    ot.zy=zy*i_mat.zy;    ot.zz=zz*i_mat.zz;
		return ot;
	}
	template<typename type> 
	mat33<type> mat33<type>::operator /(const mat33<type>& i_mat) const{
		mat33<type> ot;
		ot.xx=xx/i_mat.xx;    ot.xy=xy/i_mat.xy;    ot.xz=xz/i_mat.xz;
		ot.yx=yx/i_mat.yx;    ot.yy=yy/i_mat.yy;    ot.yz=yz/i_mat.yz;
		ot.zx=zx/i_mat.zx;    ot.zy=zy/i_mat.zy;    ot.zz=zz/i_mat.zz;
		return ot;
	}
	template<typename type> 
	mat33<type> mat33<type>::operator |(const mat33<type>& i_mat) const{
			mat33<type> ot;
			type sx[9]={xx,yx,zx, xy,yy,zy, xz,yz,zz};
	
			ot.xx=sx[0]*i_mat.xx+sx[1]*i_mat.xy+sx[2]*i_mat.xz;
			ot.xy=sx[3]*i_mat.xx+sx[4]*i_mat.xy+sx[5]*i_mat.xz;
			ot.xz=sx[6]*i_mat.xx+sx[7]*i_mat.xy+sx[8]*i_mat.xz;
		
			ot.yx=sx[0]*i_mat.yx+sx[1]*i_mat.yy+sx[2]*i_mat.yz;
			ot.yy=sx[3]*i_mat.yx+sx[4]*i_mat.yy+sx[5]*i_mat.yz;
			ot.yz=sx[6]*i_mat.yx+sx[7]*i_mat.yy+sx[8]*i_mat.yz;

			ot.zx=sx[0]*i_mat.zx+sx[1]*i_mat.zy+sx[2]*i_mat.zz;
			ot.zy=sx[3]*i_mat.zx+sx[4]*i_mat.zy+sx[5]*i_mat.zz;
			ot.zz=sx[6]*i_mat.zx+sx[7]*i_mat.zy+sx[8]*i_mat.zz;
		
			return ot;	
	}
    template<typename type>
    vec3<type> mat33<type>::operator |(const vec3<type>& i_vec) const{
       vec3<type> ot;
       ot.x=xx*i_vec.x+yx*i_vec.y+zx*i_vec.z;
       ot.y=xy*i_vec.x+yy*i_vec.y+zy*i_vec.z;
       ot.z=xz*i_vec.x+yz*i_vec.y+zz*i_vec.z;

       return ot;
    }
	template<typename type> 
	mat33<type> mat33<type>::operator +(const type i_sca) const{
		mat33<type> ot;
		ot.xx=xx+i_sca;    ot.xy=xy+i_sca;    ot.xz=xz+i_sca;
		ot.yx=yx+i_sca;    ot.yy=yy+i_sca;    ot.yz=yz+i_sca;
		ot.zx=zx+i_sca;    ot.zy=zy+i_sca;    ot.zz=zz+i_sca;
		return ot;
	}
	template<typename type> 
	mat33<type> mat33<type>::operator -(const type i_sca) const{
		mat33<type> ot;
		ot.xx=xx-i_sca;    ot.xy=xy-i_sca;    ot.xz=xz-i_sca;
		ot.yx=yx-i_sca;    ot.yy=yy-i_sca;    ot.yz=yz-i_sca;
		ot.zx=zx-i_sca;    ot.zy=zy-i_sca;    ot.zz=zz-i_sca;
		return ot;
	}
	template<typename type> 
	mat33<type> mat33<type>::operator *(const type i_sca) const{
		mat33<type> ot;
		ot.xx=xx*i_sca;    ot.xy=xy*i_sca;    ot.xz=xz*i_sca;
		ot.yx=yx*i_sca;    ot.yy=yy*i_sca;    ot.yz=yz*i_sca;
		ot.zx=zx*i_sca;    ot.zy=zy*i_sca;    ot.zz=zz*i_sca;
		return ot;
	}
	template<typename type> 
	mat33<type> mat33<type>::operator /(const type i_sca) const{
		mat33<type> ot;
		ot.xx=xx/i_sca;    ot.xy=xy/i_sca;    ot.xz=xz/i_sca;
		ot.yx=yx/i_sca;    ot.yy=yy/i_sca;    ot.yz=yz/i_sca;
		ot.zx=zx/i_sca;    ot.zy=zy/i_sca;    ot.zz=zz/i_sca;
		return ot;
	}
	template<typename type> 
	mat33<type> mat33<type>::operator -() const{
		mat33<type> ot;
		ot.xx=-xx;    ot.xy=-xy;    ot.xz=-xz;
		ot.yx=-yx;    ot.yy=-yy;    ot.yz=-yz;
		ot.zx=-zx;    ot.zy=-zy;    ot.zz=-zz;
		return ot;		
	}
	template<typename type> 
	mat33<type> mat33<type>::operator ~() const{
		mat33<type> pp=*(this);
		type buf[9];
		buf[0]=1.0/pp.xx; 
		pp.yx*=buf[0];
		pp.zx*=buf[0];
		buf[1]=pp.xy;
		pp.yy-=pp.yx*buf[1];
		pp.zy-=pp.zx*buf[1];
		buf[2]=pp.xz;
		pp.yz-=pp.yx*buf[2];
		pp.zz-=pp.zx*buf[2];
		buf[3]=1.0/pp.yy;
		pp.zy*=buf[3];
		buf[4]=pp.yx;
		pp.zx-=pp.zy*buf[4];
		buf[5]=pp.yz;
		pp.zz-=pp.zy*buf[5];
		buf[6]=1.0/pp.zz;
		buf[7]=pp.zx;
		buf[8]=pp.zy;

		mat33<type> ot;
		ot.ident();
		ot.xx/=buf[0];
		ot.xy-=ot.xx*buf[1];
		ot.xz-=ot.xx*buf[2];
		ot.xy*=buf[3];
		ot.yy*=buf[3];
		ot.xx-=ot.xy*buf[4];
		ot.yx-=ot.yy*buf[4];
		ot.xz-=ot.xy*buf[5];
		ot.yz-=ot.yy*buf[5];
		ot.xz*=buf[6];
		ot.yz*=buf[6];
		ot.zz*=buf[6];
		ot.xx-=ot.xz*buf[7];
		ot.yx-=ot.yz*buf[7];
		ot.zx-=ot.zz*buf[7];
		ot.xy-=ot.xz*buf[8];
		ot.yy-=ot.yz*buf[8];
		ot.zy-=ot.zz*buf[8];
			
		return ot;
	}							
	template<typename type> 
	mat33<type> mat33<type>::operator !() const{
		mat33<type> ot;		
		ot.xx=xx;
		ot.yx=xy;
		ot.zx=xz;
		ot.xy=yx;
		ot.yy=yy;
		ot.zy=yz;
		ot.xz=zx;
		ot.yz=zy;
		ot.zz=zz;

		return ot;
	}
	template<typename type> 
	type mat33<type>::operator ||(const mat33<type>& i_mat) const{
		type ot=xx*i_mat.xx+xy*i_mat.xy+xz*i_mat.xz
		       +yx*i_mat.yx+yy*i_mat.yy+yz*i_mat.yz
		       +zx*i_mat.zx+zy*i_mat.zy+zz*i_mat.zz;
		
		return ot;
	}

	//Function
	template<typename type> 
	type mat33<type>::trace() const{
		type ot=xx+yy+zz;
		return ot;
	}
	template<typename type> 
	type mat33<type>::det() const{
		type ot=xx*(yy*zz-yz*zy)+xy*(yz*zx-zz*yx)+xz*(yx*zy-zx*yy);
		return ot;
	}
	template<typename type> 
	void mat33<type>::print() const{
		std::cout<<std::scientific<<std::setprecision(2);
		std::cout<<xx<<" "<<yx<<" "<<zx<<std::endl;
		std::cout<<xy<<" "<<yy<<" "<<zy<<std::endl;
		std::cout<<xz<<" "<<yz<<" "<<zz<<std::endl;
#ifndef OLD_GPP
		std::cout<<std::defaultfloat;
#endif
		return;
	}
	template<typename type> 
	void mat33<type>::print(const std::string i_str) const{
		std::string str1=i_str+" "+i_str+" "+i_str+"\n";
		str1+=str1+str1;
		std::printf(str1.c_str(), xx, yx, zx, xy, yy, zy, xz, yz, zz);
		return;
	}
	template<typename type> 
	void mat33<type>::print(const std::string i_str1, const std::string i_str2) const{
		std::string str1=i_str1+"\n";
		std::string str2=i_str2+" "+i_str2+" "+i_str2+"\n";
		str1+=str2+str2+str2;
		std::printf(str1.c_str(), xx, yx, zx, xy, yy, zy, xz, yz, zz);
		return;
	}

    //Friend Function
    
	/* MAT CLASS */
	//Constructor
	template<typename type> 
	mat<type>::mat(){
		row_=0;
		col_=0;
		total_=0;
		elem_=reinterpret_cast<type*>(std::malloc(0));
		_elem_=reinterpret_cast<type*>(std::malloc(0));
	}
	template<typename type> 
	mat<type>::mat(const uint i_row, const uint i_col){
		uint row=i_row;
		uint col=i_col;
		uint total=row*col;
		type* elem=elem_;
		elem=reinterpret_cast<type*>(std::malloc(total*sizeof(type)));
		if(!elem){
			throw std::bad_alloc();
		}
		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
	}
	template<typename type> 
	mat<type>::mat(const uint i_row, const uint i_col, const type i_sca){
		uint row=i_row;
		uint col=i_col;
		uint total=row*col;
		type* elem=elem_;
		elem=reinterpret_cast<type*>(std::malloc(total*sizeof(type)));
		if(!elem){
			throw std::bad_alloc();
		}
		for(uint a=0; a<total; ++a){
			elem[a]=i_sca;
		}
		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
	}
	template<typename type> template<typename... arg>
	mat<type>::mat(const uint i_row, const uint i_col, const type i_sca, const arg... args){
		uint row=i_row;
		uint col=i_col;
		uint total=i_row*i_col;
		type* elem=elem_;
		elem=reinterpret_cast<type*>(std::malloc(total*sizeof(type)));
	
		if(!elem){
			throw std::bad_alloc();
		}
		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
#ifndef MATVEC_UNSAFETY
		if(total>0) elem[0]=i_sca;
#else
		elem[0]=i_sca;
#endif
		input(1, args...);
	}


	//Destructor
	template<typename type>
	mat<type>::~mat(){
		std::free(elem_);
	}

	//Modification
	template<typename type>
	mat<type>& mat<type>::matrix(const uint i_row, const uint i_col){
		uint row=i_row;
		uint col=i_col;
		uint total=row*col;
		type* elem=elem_;
		if(total>total_){
			if(void* vptr=std::realloc(elem, total*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
		return *this;
	}
	template<typename type>
	mat<type>& mat<type>::matrix(const uint i_row, const uint i_col, const type i_sca){
		uint row=i_row;
		uint col=i_col;
		uint total=i_row*i_col;
		type* elem=elem_;
		if(total>total_){
			if(void* vptr=std::realloc(elem, total*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) elem[a]=i_sca;

		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
		return *this;
	}
	template<typename type> template<typename... arg>
	mat<type>& mat<type>::matrix(const uint i_row, const uint i_col, const type i_sca, const arg... args){
		uint row=i_row;
		uint col=i_col;
		uint total=i_row*i_col;
		type* elem=elem_;
		if(total>total_){
			if(void* vptr=std::realloc(elem, total*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
#ifndef MATVEC_UNSAFETY
		if(total>0) elem[0]=i_sca;
#else
		elem[0]=i_sca;
#endif
		input(1, args...);
		return *this;
	}
	template<typename type>
	mat<type>& mat<type>::vector(const uint i_dim){
		uint row=i_dim;
		uint col=1;
		uint total=row;
		type* elem=elem_;
		if(total>total_){
			if(void* vptr=std::realloc(elem, total*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
		return *this;
	}
	template<typename type>
	mat<type>& mat<type>::vector(const uint i_dim, const type i_sca){
		uint row=i_dim;
		uint col=1;
		uint total=row;
		type* elem=elem_;
		if(total>total_){
			if(void* vptr=std::realloc(elem, total*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) elem[a]=i_sca;
		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
		return *this;
	}
	template<typename type> template<typename... arg>
	mat<type>& mat<type>::vector(const uint i_dim, const type i_sca, const arg... args){
		uint row=i_dim;
		uint col=1;
		uint total=row;
		type* elem=elem_;
		if(total>total_){
			if(void* vptr=std::realloc(elem, total*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		row_=row;
		col_=col;
		total_=total;
		elem_=elem;
#ifndef MATVEC_UNSAFETY
		if(total>0) elem[0]=i_sca;
#else
		elem[0]=i_sca;
#endif
		input(1, args...);
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::func(type (*i_func)(const type)){
		uint total=total_;
		type* elem=elem_;
		for(uint a=0; a<total; ++a) elem[a]=i_func(elem[a]);
		return *this;
	}	
	template<typename type> 
	mat<type>& mat<type>::func(type (*i_func)(const type, const type), const type i_sca){
		uint total=total_;
		type* elem=elem_;
		for(uint a=0; a<total; ++a) elem[a]=i_func(elem[a], i_sca);
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::zero(){
		uint total=total_;
		type* elem=elem_;
		std::memset(elem_, 0, sizeof(type)*total);
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::ident(){
		uint row=row_;
#ifndef MATVEC_UNSAFETY
		uint col=col_;
		if(row_!=col_) std::cerr<<"W. Matrix row and column are not same to identify!!"<<std::endl;
#endif
		uint total=total_;
		type* elem=elem_;
		for(uint a=0, b=0, c=row+1; a<total; ++a){
			if(b==a){
				elem[a]=1;
				b+=c;
			}else{
				elem[a]=0;
			}
		}
		return *this;
	}

	//Substitution
	template<typename type> 
	mat<type>& mat<type>::operator =(const mat<type>& i_mat){
		uint total=total_;
		type* elem=elem_;	

		if(total<i_mat.total_){
			if(void* vptr=std::realloc(elem, i_mat.total_*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		total=i_mat.total_;
		std::memcpy(elem, i_mat.elem_, total*sizeof(type));
		row_=i_mat.row_;
		col_=i_mat.col_;
		total_=total;
		elem_=elem;

		return *this;
	}

	template<typename type> 
	mat<type>& mat<type>::operator+=(const mat<type>& i_mat){
		uint total=total_;
		type* elem=elem_;

#ifndef MATVEC_UNSAFETY
		if(row_!=i_mat.row_ || col_!=i_mat.col_){
			std::cerr<<"W. Matrix row or column are not same!!"<<std::endl;
			if(total>i_mat.total_) total=i_mat.total_;
		}
#endif
		for(uint a=0; a<total; ++a) elem[a]+=i_mat.elem_[a];
	
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator-=(const mat<type>& i_mat){
		uint total=total_;
		type* elem=elem_;

#ifndef MATVEC_UNSAFETY
		if(row_!=i_mat.row_ || col_!=i_mat.col_){
			std::cerr<<"W. Matrix row or column are not same!!"<<std::endl;
			if(total>i_mat.total_) total=i_mat.total_;
		}
#endif
		for(uint a=0; a<total; ++a) elem[a]-=i_mat.elem_[a];
	
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator*=(const mat<type>& i_mat){
		uint total=total_;
		type* elem=elem_;

#ifndef MATVEC_UNSAFETY
		if(row_!=i_mat.row_ || col_!=i_mat.col_){
			std::cerr<<"W. Matrix row or column are not same!!"<<std::endl;
			if(total>i_mat.total_) total=i_mat.total_;
		}
#endif
		for(uint a=0; a<total; ++a) elem[a]*=i_mat.elem_[a];
	
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator/=(const mat<type>& i_mat){
		uint total=total_;
		type* elem=elem_;

#ifndef MATVEC_UNSAFETY
		if(row_!=i_mat.row_ || col_!=i_mat.col_){
			std::cerr<<"W. Matrix row or column are not same!!"<<std::endl;
			if(total>i_mat.total_) total=i_mat.total_;
		}
#endif
		for(uint a=0; a<total; ++a) elem[a]/=i_mat.elem_[a];
	
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator|=(const mat<type>& i_mat){
		uint row=row_;
		uint col=col_;
		uint total=total_;
		type* elem=elem_;

#ifndef MATVEC_UNSAFETY
		if(col!=i_mat.row_){
			std::cerr<<"E. Matrix product is not defined!!"<<std::endl;
			std::exit(EXIT_FAILURE);
		}
#endif
		uint new_total=row*i_mat.col_;
		if(_total_<new_total){
			if(void* vptr=std::realloc(_elem_, new_total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0, b=0; a<i_mat.total_; a+=i_mat.row_){
			for(uint c=0; c<row; ++c, ++b){
				_elem_[b]=0;
				for(uint d=0, e=0; e<i_mat.row_; d+=row, ++e){
					_elem_[b]+=elem[d+c]*i_mat.elem_[e+a];
				}
			}
		}
		if(total<new_total){
			if(void* vptr=std::realloc(elem, new_total*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		_total_=new_total;
		col_=i_mat.col_;
		total_=new_total;
		std::memcpy(elem, _elem_, new_total*sizeof(type));
		elem_=elem;	
		return *this;
	}

	template<typename type> 
	mat<type>& mat<type>::operator =(const cpyflag<type> i_flag){
		if(i_flag.out()) std::cerr<<"W. Buffer copy failure!!"<<std::endl;

		uint total=total_;
		type* elem=elem_;	

		if(total<_total_){
			if(void* vptr=std::realloc(elem, _total_*sizeof(type))){
				elem=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		total=_total_;
		std::memcpy(elem, _elem_, total*sizeof(type));
		row_=_row_;
		col_=_col_;
		total_=total;
		elem_=elem;

		return *this;
	}

	template<typename type> 
	mat<type>& mat<type>::operator +=(const cpyflag<type> i_flag){
		if(i_flag.out()) std::cerr<<"W. Buffer copy failure!!"<<std::endl;
		
		uint total=total_;
		type* elem=elem_;
		type* elem_orig=_elem_;

#ifndef MATVEC_UNSAFETY
		if(row_!=_row_ || col_!=_col_){
			std::cerr<<"W. Matrix row or column are not same!!"<<std::endl;
			if(total>_total_) total=_total_;
		}
#endif
		for(uint a=0; a<total; ++a) elem[a]+=elem_orig[a];
	
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator -=(const cpyflag<type> i_flag){
		if(i_flag.out()) std::cerr<<"W. Buffer copy failure!!"<<std::endl;
		
		uint total=total_;
		type* elem=elem_;
		type* elem_orig=_elem_;

#ifndef MATVEC_UNSAFETY
		if(row_!=_row_ || col_!=_col_){
			std::cerr<<"W. Matrix row or column are not same!!"<<std::endl;
			if(total>_total_) total=_total_;
		}
#endif
		for(uint a=0; a<total; ++a) elem[a]-=elem_orig[a];
	
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator *=(const cpyflag<type> i_flag){
		if(i_flag.out()) std::cerr<<"W. Buffer copy failure!!"<<std::endl;
		
		uint total=total_;
		type* elem=elem_;
		type* elem_orig=_elem_;

#ifndef MATVEC_UNSAFETY
		if(row_!=_row_ || col_!=_col_){
			std::cerr<<"W. Matrix row or column are not same!!"<<std::endl;
			if(total>_total_) total=_total_;
		}
#endif
		for(uint a=0; a<total; ++a) elem[a]*=elem_orig[a];
	
		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator /=(const cpyflag<type> i_flag){
		if(i_flag.out()) std::cerr<<"W. Buffer copy failure!!"<<std::endl;
		
		uint total=total_;
		type* elem=elem_;
		type* elem_orig=_elem_;

#ifndef MATVEC_UNSAFETY
		if(row_!=_row_ || col_!=_col_){
			std::cerr<<"W. Matrix row or column are not same!!"<<std::endl;
			if(total>_total_) total=_total_;
		}
#endif
		for(uint a=0; a<total; ++a) elem[a]/=elem_orig[a];
	
		return *this;
	}

	template<typename type> 
	mat<type>& mat<type>::operator =(const type i_sca){
		uint total=total_;
		type* elem=elem_;
		for(uint a=0; a<total; ++a) elem[a]=i_sca;

		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator +=(const type i_sca){
		uint total=total_;
		type* elem=elem_;
		for(uint a=0; a<total; ++a) elem[a]+=i_sca;

		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator -=(const type i_sca){
		uint total=total_;
		type* elem=elem_;
		for(uint a=0; a<total; ++a) elem[a]-=i_sca;

		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator *=(const type i_sca){
		uint total=total_;
		type* elem=elem_;
		for(uint a=0; a<total; ++a) elem[a]*=i_sca;

		return *this;
	}
	template<typename type> 
	mat<type>& mat<type>::operator /=(const type i_sca){
		uint total=total_;
		type* elem=elem_;
		for(uint a=0; a<total; ++a) elem[a]/=i_sca;

		return *this;
	}
	
	//Calculation
	template<typename type> 
	cpyflag<type> mat<type>::operator +(const mat<type>& i_mat) const{
		cpyflag<type> flag;
	
		uint row=row_;
		uint col=col_;
		uint total=total_;
		type* elem=elem_;
#ifndef MATVEC_UNSAFETY
		if(row!=i_mat.row_ || col!=i_mat.col_) return flag;
#endif
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=elem[a]+i_mat.elem_[a];
		_row_=row;
		_col_=col;
		_total_=total;

		flag.turn();	
		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator -(const mat<type>& i_mat) const{
		cpyflag<type> flag;
	
		uint row=row_;
		uint col=col_;
		uint total=total_;
		type* elem=elem_;
#ifndef MATVEC_UNSAFETY
		if(row!=i_mat.row_ || col!=i_mat.col_) return flag;
#endif
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=elem[a]-i_mat.elem_[a];
		_row_=row;
		_col_=col;
		_total_=total;

		flag.turn();	
		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator *(const mat<type>& i_mat) const{
		cpyflag<type> flag;
	
		uint row=row_;
		uint col=col_;
		uint total=total_;
		type* elem=elem_;
#ifndef MATVEC_UNSAFETY
		if(row!=i_mat.row_ || col!=i_mat.col_) return flag;
#endif
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=elem[a]*i_mat.elem_[a];
		_row_=row;
		_col_=col;
		_total_=total;

		flag.turn();	
		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator /(const mat<type>& i_mat) const{
		cpyflag<type> flag;
	
		uint row=row_;
		uint col=col_;
		uint total=total_;
		type* elem=elem_;
#ifndef MATVEC_UNSAFETY
		if(row!=i_mat.row_ || col!=i_mat.col_) return flag;
#endif
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=elem[a]/i_mat.elem_[a];
		_row_=row;
		_col_=col;
		_total_=total;

		flag.turn();	
		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator|(const mat<type>& i_mat) const{
		cpyflag<type> flag;

		uint row=row_;
		uint col=col_;
		uint total=total_;
		type* elem=elem_;

#ifndef MATVEC_UNSAFETY
		if(col!=i_mat.row_){
			std::cerr<<"E. Matrix product is not defined!!"<<std::endl;
			std::exit(EXIT_FAILURE);
		}
#endif
		uint new_total=row*i_mat.col_;
		if(_total_<new_total){
			if(void* vptr=std::realloc(_elem_, new_total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0, b=0; a<i_mat.total_; a+=i_mat.row_){
			for(uint c=0; c<row; ++c, ++b){
				_elem_[b]=0;
				for(uint d=0, e=0; e<i_mat.row_; d+=row, ++e){
					_elem_[b]+=elem[d+c]*i_mat.elem_[e+a];
				}
			}
		}
		_row_=row;
		_col_=i_mat.col_;
		_total_=new_total;

		flag.turn();

		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator +(const type i_sca) const{
		cpyflag<type> flag;
	
		uint total=total_;
		type* elem=elem_;
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=elem[a]+i_sca;
		_row_=row_;
		_col_=col_;
		_total_=total;

		flag.turn();	
		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator -(const type i_sca) const{
		cpyflag<type> flag;
	
		uint total=total_;
		type* elem=elem_;
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=elem[a]-i_sca;
		_row_=row_;
		_col_=col_;
		_total_=total;

		flag.turn();	
		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator *(const type i_sca) const{
		cpyflag<type> flag;
	
		uint total=total_;
		type* elem=elem_;
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=elem[a]*i_sca;
		_row_=row_;
		_col_=col_;
		_total_=total;

		flag.turn();	
		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator /(const type i_sca) const{
		cpyflag<type> flag;
	
		uint total=total_;
		type* elem=elem_;
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=elem[a]/i_sca;
		_row_=row_;
		_col_=col_;
		_total_=total;

		flag.turn();	
		return flag;
	}
	template<typename type> 
	cpyflag<type> mat<type>::operator -() const{
		cpyflag<type> flag;
	
		uint total=total_;
		type* elem=elem_;
		if(_total_<total){
			if(void* vptr=std::realloc(_elem_, total*sizeof(type))){
				_elem_=reinterpret_cast<type*>(vptr);
			}else{
				throw std::bad_alloc();
			}
		}
		for(uint a=0; a<total; ++a) _elem_[a]=-elem[a];
		_row_=row_;
		_col_=col_;
		_total_=total;

		flag.turn();	
		return flag;
	}

	
	//Functions
	template<typename type> 
	const uint mat<type>::row() const{
		return row_;
	}
	template<typename type> 
	const uint mat<type>::column() const{
		return col_;
	}
	template<typename type> 
	const uint mat<type>::total() const{
		return total_;
	}
	template<typename type> 
	const type* mat<type>::elements() const{
		return elem_;
	}
	template<typename type> 
	type& mat<type>::operator[](const uint i_resid) const{
#ifndef MATVEC_UNSAFETY
		if(total_<=i_resid) throw std::bad_alloc();
#endif
		return elem_[i_resid];
	}
	template<typename type> 
	const uint mat<type>::buffer_row() const{
		return _row_;
	}
	template<typename type> 
	const uint mat<type>::buffer_column() const{
		return _col_;
	}
	template<typename type> 
	const uint mat<type>::buffer_total() const{
		return _total_;
	}
	template<typename type> 
	const type* mat<type>::buffer_elements() const{
		return _elem_;
	}
	template<typename type> 
	void mat<type>::buffer_print() const{
		std::cerr<<_row_<<" "<<_col_<<" "<<_total_<<std::endl;
		for(uint a=0; a<_total_; ++a) std::cerr<<_elem_[a]<<std::endl;
	}

	//Private Functions
	template<typename type> template<typename... arg>
	void mat<type>::input(uint count, const type i_sca, const arg... args){
		if(count<total_) elem_[count]=i_sca;
		++count;
		input(count, args...);
	}
	template<typename type>
	void mat<type>::input(const uint count){
#ifndef MATVEC_UNSAFETY
		if(total_<count) std::cerr<<"W:One or more than arguments were not reflected!!"<<std::endl; 
		else if(count<total_) std::cerr<<"W:Few Argument!!"<<std::endl;
#endif
	}
	

/*	template <typename type = double> class mat{
		usint row;
		usint col;
		usint toel;
		type* ele;

		protected:
		static usint s_row;
		static usint s_col;
		static usint s_toel;
		static type* s_ele;

		public:
		mat(){
			row = 0;
			col = 0;
			toel = 0;
			ele = NULL;
		}
		mat(usint i_row){
			row = i_row;
			col = 1;
			toel = i_row;
			ele = (type*)malloc(sizeof(type)*toel);
		}
		mat(usint i_row, usint i_col){
			row = i_row;
			col = i_col;
			toel = i_row*i_col;
			ele = (type*)malloc(sizeof(type)*toel);
		}
		mat(usint i_row, usint i_col, type i_sca){
			row = i_row;
			col = i_col;
			toel = i_row*i_col;
			ele = (type*)malloc(sizeof(type)*toel);
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = i_sca;
			}
		}

		void matrix(usint i_row, usint i_col, type i_sca){
			row = i_row;
			col = i_col;
			usint p_toel = i_row*i_col;
			if(toel < p_toel){
				type* p_ele = (type*)realloc(ele, sizeof(type)*p_toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return;
				}else if(p_ele != ele){
					ele = p_ele;
				}
				toel = p_toel;
			}
			for(usint a = 0; a < p_toel; ++a){
				ele[a] = i_sca;
			}
		}
		template <typename... arg>
		void matrix(usint i_row, usint i_col, arg... args){
			row = i_row;
			col = i_col;
			usint p_toel = i_row*i_col;
			if(toel < p_toel){
				type* p_ele = (type*)realloc(ele, sizeof(type)*p_toel);
				if(p_ele == NULL){
					return;
				}else if(p_ele != ele){
					ele = p_ele;
				}
				toel = p_toel;
			} 
			input(0, args...);
		}
		void vector(usint i_row, type i_sca){
			row = i_row;
			col = 1;
			usint p_toel = i_row;
			if(toel < p_toel){
				type* p_ele = (type*)realloc(ele, sizeof(type)*p_toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return;
				}else if(p_ele != ele){
					ele = p_ele;
				}
				toel = p_toel;
			}
			for(usint a = 0; a < p_toel; ++a){
				ele[a] = i_sca;
			}
		}
		template <typename... arg>
		void vector(usint i_row, arg... args){
			row = i_row;
			col = 1;
			usint p_toel = i_row;
			if(toel < p_toel){
				type* p_ele = (type*)realloc(ele, sizeof(type)*p_toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return;
				}else if(p_ele != ele){
					ele = p_ele;
				}
				toel = p_toel;
			} 
			input(0, args...);
		}
		void operator =(const mat& i_mat){
			usint p_toel = toel;
			type* p_ele;
			if(p_toel < i_mat.toel){
				p_ele = (type*)realloc(ele, sizeof(type)*i_mat.toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return;
				}else if(p_ele != ele){
					ele = p_ele;
				}
			}else{
				p_ele = ele;
			}
			p_toel = i_mat.toel;
			row = i_mat.row;
			col = i_mat.col;
			toel = p_toel;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = i_mat.ele[a];
			}
		}
		void operator =(const flag swc){
			if(!swc.flag){
				return;
			}
			usint p_toel = toel;
			type* p_ele;
			if(p_toel < s_toel){
				p_ele = (type*)realloc(ele, sizeof(type)*s_toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return;
				}else if(p_ele != ele){
					ele = p_ele;
				}
			}else{
				p_ele = ele;
			}
			p_toel = s_toel;
			row = s_row;
			col = s_col;
			toel = p_toel;
			type* sp_ele = s_ele;
			for(usint a = 0; a < p_toel; ++a){
			p_ele[a] = sp_ele[a];
			}
		}
		void operator =(const type i_sca){
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = i_sca;
			}
		}
		flag operator +(const type i_sca){
			flag out = {false};
			usint p_toel = s_toel;
			usint t_toel = toel;
			type* p_ele;
			type* t_ele = s_ele;
			if(p_toel < t_toel){
				p_ele = (type*)realloc(t_ele, sizeof(type)*t_toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return out;
				}else if(p_ele != s_ele){
					s_ele = p_ele;
				}
			}else{
				p_ele = s_ele;
			}
			p_toel = t_toel;
			s_row = row;
			s_col = col;
			s_toel = p_toel;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = ele[a] + i_sca;
			}
			out.flag = true;
			return out;
		}
		flag operator +(const mat& i_mat){
			flag out = {false};
			if(row != i_mat.row || col != i_mat.col){
				std::cerr << "W:Cannot define additon" << std::endl;
					return out;
			}
			usint p_toel = s_toel;
			type* p_ele;
			if(p_toel < i_mat.toel){
				p_ele = (type*)realloc(s_ele, sizeof(type)*i_mat.toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return out;
				}else if(p_ele != s_ele){
					s_ele = p_ele;
				}
			}else{
				p_ele = s_ele;
			}
			p_toel = i_mat.toel;
			s_row = i_mat.row;
			s_col = i_mat.col;
			s_toel = p_toel;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = 0;
				p_ele[a] = ele[a] + i_mat.ele[a];
			}
			out.flag = true;
			return out;
		}
		void operator ++(){
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] += (type)1;
			}
		}
		void operator += (const type i_sca){
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] += (type)i_sca;
			}
		}
		void operator += (const mat& i_mat){
			if(row != i_mat.row || col != i_mat.col){
				std::cerr << "W:Cannot define additon" << std::endl;
				return;
			}
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] += (type)i_mat.ele[a];
			}
		}
		void operator += (const flag swc){
			if(!swc.flag) return;
			if(row != s_row || col != s_col){
				std::cerr << "W:Cannot define additon" << std::endl;
				return;
			}
			//Now
			usint n_toel = toel;
			type* n_ele = ele;

			//S Now
			usint sn_toel=s_toel;
			type* sn_ele=s_ele;
			for(usint a = 0; a < sn_toel; ++a){
				n_ele[a]+=sn_ele[a];
			}
		}

		flag operator -(const type i_sca){
			flag out = {false};
			usint p_toel = s_toel;
			usint t_toel = toel;
			type* p_ele;
			type* t_ele = s_ele;
			if(p_toel < t_toel){
				p_ele = (type*)realloc(t_ele, sizeof(type)*t_toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return out;
				}else if(p_ele != s_ele){
					s_ele = p_ele;
				}
			}else{
				p_ele = s_ele;
			}
			p_toel = t_toel;
			s_row = row;
			s_col = col;
			s_toel = p_toel;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = 0;
				p_ele[a] = ele[a] - i_sca;
			}
			out.flag = true;
			return out;
		}
		flag operator -(const mat& i_mat){
			flag out = {false};
			if(row != i_mat.row || col != i_mat.col){
				std::cerr << "W:Cannot define additon" << std::endl;
				return out;
			}
			usint p_toel = s_toel;
			type* p_ele;
			if(p_toel < i_mat.toel){
				p_ele = (type*)realloc(s_ele, sizeof(type)*i_mat.toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return out;
				}else if(p_ele != s_ele){
					s_ele = p_ele;
				}
			}else{
				p_ele = s_ele;
			}
			p_toel = i_mat.toel;
			s_row = i_mat.row;
			s_col = i_mat.col;
			s_toel = p_toel;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = 0;
				p_ele[a] = ele[a] - i_mat.ele[a];
			}
			out.flag = true;
			return out;
		}
		void operator --(){
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] -= (type)1;
			}
		}
		void operator -= (const type i_sca){
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] -= (type)i_sca;
			}
		}
		void operator -= (const mat& i_mat){
			if(row != i_mat.row || col != i_mat.col){
				std::cerr << "W:Cannot define additon" << std::endl;
				return;
			}
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] -= (type)i_mat.ele[a];
			}
		}
		flag operator *(const type i_sca){
			flag out = {false};
			usint p_toel = s_toel;
			usint t_toel = toel;
			type* p_ele;
			if(p_toel < t_toel){
				p_ele = (type*)realloc(s_ele, sizeof(type)*t_toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return out;
				}else if(p_ele != s_ele){
					s_ele = p_ele;
				}
			}else{
				p_ele = s_ele;
			}
			p_toel = t_toel;
			s_row = row;
			s_col = col;
			s_toel = p_toel;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = 0;
				p_ele[a] = ele[a] * i_sca;
			}
			out.flag = true;
			return out;
		}
		flag operator *(const mat& i_mat){
			flag out = {false};
			usint p_row = row;
			usint p_col = col;
			type* p_ele = ele;
			if(p_col != i_mat.row){
				std::cerr << "W:Cannot define product" << std::endl;
				return out;
			}
			usint st_toel = s_toel;
			usint sp_toel = p_row*i_mat.col;
			type* sp_ele;
			if(s_toel < sp_toel){
				sp_ele = (type*)realloc(s_ele, sizeof(type)*sp_toel);
				if(sp_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return out;
				}else if(sp_ele != s_ele){
					s_ele = sp_ele;
				}
			}else{
				sp_ele = s_ele;
			}
			st_toel = sp_toel;
			s_row = p_row;
			s_col = i_mat.col;
			s_toel = st_toel;
			for(usint d = 0, e = 0; d < i_mat.toel; d += i_mat.row){
				for(usint c = 0; c < p_row; ++c, ++e){
					sp_ele[e] = (type)0;
					for(usint a = 0, b = 0; b < i_mat.row; a += p_row, ++b){
						sp_ele[e] += p_ele[a+c]*i_mat.ele[b+d];
					}
				}
			}
			out.flag = true;
			return out;
		}
		void operator *= (const type i_sca){
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] *= (type)i_sca;
			}
		}
		void operator /= (const type i_sca){
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] /= (type)i_sca;
			}
		}

		void in(const usint i_row, const type i_sca){
			if(i_row > toel){
				return;
			}
			ele[i_row] = i_sca;
		}
		void in(const usint i_row, const usint i_col, const type i_sca){
			if(i_row > row || i_col > col){
				return;
			}
			ele[i_col*row + i_row] = i_sca;
		}
		type ot(const usint i_row){
			if(i_row > toel){
				return (type)0;
			}
			return ele[i_row];
		}
		type ot(const usint i_row, const usint i_col){
			if(i_row > row || i_col > col){
				return (type)0;
			}
			return ele[i_col*row + i_row];
		}
		template <typename... arg>
		void input(usint count, type i_sca, arg... args){
			if(count < toel){
				ele[count] = (type)i_sca;
			}
			++count;
			input(count, args...);
		}
		void input(usint count){
			if(count < toel-1){
				std::cerr << "W:Few arguments" << std::endl;
			}
		}
		type sum(){
			type out = (type)0;
			usint p_toel = toel;
			type* p_ele = ele;
				for(usint a = 0; a < p_toel; ++a){
					out += p_ele[a];
				}	
			return out;
		}
		type sz(){
			type ot=0;
			usint p_toel=toel;
			type* p_ele=ele;
			for(usint a=0; a<p_toel; ++a){
				ot+=p_ele[a]*p_ele[a];
			}
			return sqrt(ot);
		}

		void unif(type i_sca){
			usint p_toel=toel;
			type* p_ele=ele;
			for(usint a=0; a<p_toel; ++a){
				p_ele[a]=i_sca;
			}
		}

		flag trans(){
			flag ot={false};
			
			//Now
			usint n_row=row;
			usint n_col=col;
			type* n_ele=ele;

			//Expected
			usint ex_toel=toel;
			usint ex_row=col;
			usint ex_col=row;

			//S Now
			usint sn_toel=s_toel;
			usint sn_row=s_row;
			usint sn_col=s_col;
			type* sn_ele=s_ele;
			type* p_ele;

			//Resize
			if(sn_toel<ex_toel){
				p_ele=reinterpret_cast<type*>(std::realloc(sn_ele, sizeof(type)*ex_toel));
				if(p_ele==NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return ot;
				}else if(p_ele!=sn_ele){
					s_ele=p_ele;
					sn_ele=p_ele;
				}
			}
			s_toel=ex_toel;
			sn_toel=ex_toel;
			
			//Write
			s_row=ex_row;
			sn_row=ex_row;
			s_col=ex_col;
			sn_col=ex_col;
			for(usint a=0, c=0; a<n_col; ++a, c+=n_row){
				for(usint b=0, d=0; b<n_row; ++b, d+=n_col){
					sn_ele[a+d]=n_ele[c+b];
				}
			}
			ot.flag=true;
			return ot;
		}

		//Inner Products
		type operator ||(const mat& i_mat){
			type ot=0.0;
			usint p_row=row;
			usint p_col=col;
			if(i_mat.row!=p_row || i_mat.col!=p_col){
				std::cerr<<"W:Bat Matrix!!(matvec::mat::dot)"<<std::endl;
				return 0.0;
			}
			type* p_ele=ele;

			for(usint a=0; a<i_mat.toel; ++a){
				ot+=p_ele[a]*i_mat.ele[a];
			}
			return ot;
		}

		//Tensor Products
		flag operator &(const mat& i_mat){
			flag ot={false};
			usint t_row=row;
			usint t_col=col;
			if(t_row!=i_mat.row || t_col!=1 || i_mat.col!=1){
				std::cerr<<"W:Can't Ocross by Non-1D Vectors(matvec::mat::operator &&)"<<std::endl;
			}

			usint t_toel=t_row*t_row;
			usint p_toel=s_toel;
			type* p_ele;
			type* t_ele=s_ele;
			if(p_toel<t_toel){
				p_ele=reinterpret_cast<type*>(std::realloc(t_ele, sizeof(type)*t_toel));
				if(p_ele==NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return ot;
				}else if(p_ele!=s_ele){
					s_ele=p_ele;
				}
			}else{
				p_ele=t_ele;
			}
			p_toel=t_toel;

			//Write
			s_row=t_row;
			s_col=t_row;
			s_toel=p_toel;
			for(usint a=0; a<t_row; ++a){
				for(usint b=0, c=0; b<t_row; ++b, c+=t_row){
					p_ele[a+c]=ele[a]*i_mat.ele[b];
				}
			}
			ot.flag=true;

			return ot;
		}
	
		void func(type (*func)(type)){
			usint p_toel = toel;
			type* p_ele = ele;
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = func(p_ele[a]);
			}
		}
		void func(const mat& i_mat, type (*func)(type)){
			usint p_toel = toel;
			type* p_ele;
			if(p_toel < i_mat.toel){
				p_ele = (type*)realloc(p_ele, sizeof(type)*i_mat.toel);
				if(p_ele == NULL){
					std::cerr << "W:Cannot assure memory" << std::endl;
					return;
				}else if(p_ele != ele){
				ele = p_ele;
				}
			}else{
				p_ele = ele;
			}
			p_toel = i_mat.toel;
			row = i_mat.row;
			col = i_mat.col;
			toel = p_toel;
		
			for(usint a = 0; a < p_toel; ++a){
				p_ele[a] = func(i_mat.ele[a]);
			}
		}

		void print(){
			usint t_row = row;
			usint t_col = col;
			type* t_ele = ele;
			std::cout << "ROW:" << t_row << " " << "COL:" << t_col;
			if(t_ele == NULL){
				std::cout << std::endl << "NULL" << std::endl;
				return;
			}
			for(usint a = 0; a < t_row; ++a){
				std::cout << std::endl;
				for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
					printf("%.2e ", (double)t_ele[a+b]);
				}
			}
			std::cout << std::endl;
		}
		void print(std::string str){
			usint t_row = row;
			usint t_col = col;
			type* t_ele = ele;
			std::cout << "ROW:" << t_row << " COL:" << t_col << " " << str;
			if(t_ele == NULL){
				std::cout << std::endl << "NULL" << std::endl;
				return;
			}
			for(usint a = 0; a < t_row; ++a){
				std::cout << std::endl;
				for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
					printf("%.2e ", (double)t_ele[a+b]);
				}
			}
			std::cout << std::endl;
		}
	
		void print(char mode){
			usint t_row = row;
			usint t_col = col;
			type* t_ele = ele;
			std::cout << "ROW:" << t_row << " " << "COL:" << t_col;
			if(t_ele == NULL){
				std::cout << std::endl << NULL << std::endl;
				return;
			}
			switch(mode){
				case MV_PRINT_DOT2:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%.2f ", (double)t_ele[a+b]);
					}
				}
				break;
	
				case MV_PRINT_EXP6:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%.6e ", (double)t_ele[a+b]);
					}
				}
				break;
	
				case MV_PRINT_EXP2:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%.2e ", (double)t_ele[a+b]);
					}
				}
				break;
	
				case MV_PRINT_INT:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%ld ", (long)t_ele[a+b]);
					}
				}
				break;
	
				default:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%f ", (double)t_ele[a+b]);
					}
				}
				break;
			}
			std::cout << std::endl;
		}
		void print(char mode, std::string str){
			usint t_row = row;
			usint t_col = col;
			type* t_ele = ele;
			std::cout << "ROW:" << t_row << " COL:" << t_col << " " << str;
			if(t_ele == NULL){
				std::cout << std::endl << "NULL" << std::endl;
				return;
			}
			switch(mode){
				case MV_PRINT_DOT2:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%.2f ", (double)t_ele[a+b]);
					}
				}
				break;
	
				case MV_PRINT_EXP6:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%.6e ", (double)t_ele[a+b]);
					}
				}
				break;
	
				case MV_PRINT_EXP2:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%.2e ", (double)t_ele[a+b]);
					}
				}
				break;
	
				case MV_PRINT_INT:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%ld ", (long)t_ele[a+b]);
					}
				}
				break;
	
				default:
				for(usint a = 0; a < t_row; ++a){
					std::cout << std::endl;
					for(usint b = 0, c = 0; c < t_col; b += t_row, ++c){
						printf("%f ", (double)t_ele[a+b]);
					}
				}
				break;
			}
			std::cout << std::endl;
		}
	};

	template <typename type> usint mat<type>::s_row = 0;
	template <typename type> usint mat<type>::s_col = 0;
	template <typename type> usint mat<type>::s_toel = 0;
	template <typename type> type* mat<type>::s_ele = NULL;


	template <typename type=double> struct mat33{
		type xx;
		type xy;
		type xz;
		type yx;
		type yy;
		type yz;
		type zx;
		type zy;
		type zz;
		mat33(){
			xx=0;
			xy=0;
			xz=0;
			yx=0;
			yy=0;
			yz=0;
			zx=0;
			zy=0;
			zz=0;
		
			return;
		}
		//Initializers
		mat33(	type i_xx, type i_xy, type i_xz,
			type i_yx, type i_yy, type i_yz,
			type i_zx, type i_zy, type i_zz){
			
			xx=i_xx;
			xy=i_xy;
			xz=i_xz;
			yx=i_yx;
			yy=i_yy;
			yz=i_yz;
			zx=i_zx;
			zy=i_zy;
			zz=i_zz;

			return;
		}
		mat33<type>& in(type i_xx, type i_xy, type i_xz,
				type i_yx, type i_yy, type i_yz,
				type i_zx, type i_zy, type i_zz){
			xx=i_xx;
			xy=i_xy;
			xz=i_xz;
			yx=i_yx;
			yy=i_yy;
			yz=i_yz;
			zx=i_zx;
			zy=i_zy;
			zz=i_zz;

			return *(this);
		}
		mat33<type>& in(const vec3<type>& i_vec, const int col){
			if(col==0){
				xx=i_vec.x;
				xy=i_vec.y;
				xz=i_vec.z;
			}else if(col==1){
				yx=i_vec.x;
				yy=i_vec.y;
				yz=i_vec.z;
			}else if(col==2){
				zx=i_vec.x;
				zy=i_vec.y;
				zz=i_vec.z;
			}

			return *(this);
		}
		mat33<type>& in(
			const vec3<type>& i_vec1,
			const vec3<type>& i_vec2,
			const vec3<type>& i_vec3){
			
			xx=i_vec1.x;
			xy=i_vec1.y;
			xz=i_vec1.z;
			yx=i_vec2.x;
			yy=i_vec2.y;
			yz=i_vec2.z;
			zx=i_vec3.x;
			zy=i_vec3.y;
			zz=i_vec3.z;
			
			return *(this);
		}
		mat33<type>& zero(){
			xx=0;
			xy=0;
			xz=0;
			yx=0;
			yy=0;
			yz=0;
			zx=0;
			zy=0;
			zz=0;
		
			return *(this);
		}
		mat33<type>& ident(){
			xx=1;
			xy=0;
			xz=0;
			yx=0;
			yy=1;
			yz=0;
			zx=0;
			zy=0;
			zz=1;
		
			return *(this);
		}

		//Operator Something
		mat33<type> operator +(mat33<type>& i_mat){
			mat33<type> ot;
			ot.xx=xx+i_mat.xx;
			ot.xy=xy+i_mat.xy;
			ot.xz=xz+i_mat.xz;
			ot.yx=yx+i_mat.yx;
			ot.yy=yy+i_mat.yy;
			ot.yz=yz+i_mat.yz;
			ot.zx=zx+i_mat.zx;
			ot.zy=zy+i_mat.zy;
			ot.zz=zz+i_mat.zz;
		
			return ot;	
		}
		mat33<type> operator -(mat33<type>& i_mat){
			mat33<type> ot;
			ot.xx=xx-i_mat.xx;
			ot.xy=xy-i_mat.xy;
			ot.xz=xz-i_mat.xz;
			ot.yx=yx-i_mat.yx;
			ot.yy=yy-i_mat.yy;
			ot.yz=yz-i_mat.yz;
			ot.zx=zx-i_mat.zx;
			ot.zy=zy-i_mat.zy;
			ot.zz=zz-i_mat.zz;
		
			return ot;	
		}
		mat33<type> operator *(mat33<type>& i_mat){
			mat33<type> ot;
			type sx[9]={xx,yx,zx, xy,yy,zy, xz,yz,zz};
	
			ot.xx=sx[0]*i_mat.xx+sx[1]*i_mat.xy+sx[2]*i_mat.xz;
			ot.xy=sx[3]*i_mat.xx+sx[4]*i_mat.xy+sx[5]*i_mat.xz;
			ot.xz=sx[6]*i_mat.xx+sx[7]*i_mat.xy+sx[8]*i_mat.xz;
		
			ot.yx=sx[0]*i_mat.yx+sx[1]*i_mat.yy+sx[2]*i_mat.yz;
			ot.yy=sx[3]*i_mat.yx+sx[4]*i_mat.yy+sx[5]*i_mat.yz;
			ot.yz=sx[6]*i_mat.yx+sx[7]*i_mat.yy+sx[8]*i_mat.yz;

			ot.zx=sx[0]*i_mat.zx+sx[1]*i_mat.zy+sx[2]*i_mat.zz;
			ot.zy=sx[3]*i_mat.zx+sx[4]*i_mat.zy+sx[5]*i_mat.zz;
			ot.zz=sx[6]*i_mat.zx+sx[7]*i_mat.zy+sx[8]*i_mat.zz;
		
			return ot;	
		}
		//Hadamard Product
		mat33<type> operator |(mat33<type>& i_mat){
			mat33<type> ot;
			ot.xx=xx*i_mat.xx;
			ot.xy=xy*i_mat.xy;
			ot.xz=xz*i_mat.xz;
			ot.yx=yx*i_mat.yx;
			ot.yy=yy*i_mat.yy;
			ot.yz=yz*i_mat.yz;
			ot.zx=zx*i_mat.zx;
			ot.zy=zy*i_mat.zy;
			ot.zz=zz*i_mat.zz;
		
			return ot;	
		}
		mat33<type> operator /(mat33<type>& i_mat){
			mat33<type> ot;
			ot.xx=xx/i_mat.xx;
			ot.xy=xy/i_mat.xy;
			ot.xz=xz/i_mat.xz;
			ot.yx=yx/i_mat.yx;
			ot.yy=yy/i_mat.yy;
			ot.yz=yz/i_mat.yz;
			ot.zx=zx/i_mat.zx;
			ot.zy=zy/i_mat.zy;
			ot.zz=zz/i_mat.zz;
		
			return ot;	
		}
		//Inner Products
		type operator ||(mat33<type>& i_mat){
			return 	 xx*i_mat.xx+xy*i_mat.xy+xz*i_mat.xz
				+yx*i_mat.yx+yy*i_mat.yy+yz*i_mat.yz
				+zx*i_mat.zx+zy*i_mat.yz+zz*i_mat.zz;
		}
		//Inverse
		mat33<type> operator ~(){
			mat33<type> pp=*(this);
			mat33<type> ot;
			ot.ident();

			double buf[9];
			//Pre.Calc.
			buf[0]=1.0/pp.xx; 
			pp.yx*=buf[0];
			pp.zx*=buf[0];
			buf[1]=pp.xy;
			pp.yy-=pp.yx*buf[1];
			pp.zy-=pp.zx*buf[1];
			buf[2]=pp.xz;
			pp.yz-=pp.yx*buf[2];
			pp.zz-=pp.zx*buf[2];
			buf[3]=1.0/pp.yy;
			pp.zy*=buf[3];
			buf[4]=pp.yx;
			pp.zx-=pp.zy*buf[4];
			buf[5]=pp.yz;
			pp.zz-=pp.zy*buf[5];
			buf[6]=1.0/pp.zz;
			buf[7]=pp.zx;
			buf[8]=pp.zy;

			//Out
			ot.xx/=buf[0];
			ot.xy-=ot.xx*buf[1];
			ot.xz-=ot.xx*buf[2];
			ot.xy*=buf[3];
			ot.yy*=buf[3];
			ot.xx-=ot.xy*buf[4];
			ot.yx-=ot.yy*buf[4];
			ot.xz-=ot.xy*buf[5];
			ot.yz-=ot.yy*buf[5];
			ot.xz*=buf[6];
			ot.yz*=buf[6];
		       	ot.zz*=buf[6];
			ot.xx-=ot.xz*buf[7];
			ot.yx-=ot.yz*buf[7];
			ot.zx-=ot.zz*buf[7];
			ot.xy-=ot.xz*buf[8];
			ot.yy-=ot.yz*buf[8];
			ot.zy-=ot.zz*buf[8];
			
			return ot;
		}
		//Trans
		mat33<type> operator !(){
			mat33<type> ot;
			
			ot.xx=xx;
			ot.yx=xy;
			ot.zx=xz;
			ot.xy=yx;
			ot.yy=yy;
			ot.zy=yz;
			ot.xz=zx;
			ot.yz=zy;
			ot.zz=zz;
			
			return ot;
		}

		//Operator Something=
		mat33<type>& operator +=(mat33<type>& i_mat){
			xx+=i_mat.xx;
			xy+=i_mat.xy;
			xz+=i_mat.xz;
			yx+=i_mat.yx;
			yy+=i_mat.yy;
			yz+=i_mat.yz;
			zx+=i_mat.zx;
			zy+=i_mat.zy;
			zz+=i_mat.zz;
		
			return *(this);	
		}
		mat33<type>& operator +=(type i_val){
			xx+=i_val;
			xy+=i_val;
			xz+=i_val;
			yx+=i_val;
			yy+=i_val;
			yz+=i_val;
			zx+=i_val;
			zy+=i_val;
			zz+=i_val;
		
			return *(this);	
		}
		mat33<type>& operator -=(mat33<type>& i_mat){
			xx-=i_mat.xx;
			xy-=i_mat.xy;
			xz-=i_mat.xz;
			yx-=i_mat.yx;
			yy-=i_mat.yy;
			yz-=i_mat.yz;
			zx-=i_mat.zx;
			zy-=i_mat.zy;
			zz-=i_mat.zz;
		
			return *(this);	
		}
		mat33<type>& operator -=(type i_val){
			xx-=i_val;
			xy-=i_val;
			xz-=i_val;
			yx-=i_val;
			yy-=i_val;
			yz-=i_val;
			zx-=i_val;
			zy-=i_val;
			zz-=i_val;
		
			return *(this);	
		}
		//Hadamard Product
		mat33<type>& operator |=(mat33<type>& i_mat){
			xx*=i_mat.xx;
			xy*=i_mat.xy;
			xz*=i_mat.xz;
			yx*=i_mat.yx;
			yy*=i_mat.yy;
			yz*=i_mat.yz;
			zx*=i_mat.zx;
			zy*=i_mat.zy;
			zz*=i_mat.zz;
		
			return *(this);	
		}
		mat33<type>& operator *=(type i_val){
			xx*=i_val;
			xy*=i_val;
			xz*=i_val;
			yx*=i_val;
			yy*=i_val;
			yz*=i_val;
			zx*=i_val;
			zy*=i_val;
			zz*=i_val;
		
			return *(this);	
		}
		mat33<type>& operator /=(mat33<type>& i_mat){
			xx/=i_mat.xx;
			xy/=i_mat.xy;
			xz/=i_mat.xz;
			yx/=i_mat.yx;
			yy/=i_mat.yy;
			yz/=i_mat.yz;
			zx/=i_mat.zx;
			zy/=i_mat.zy;
			zz/=i_mat.zz;
		
			return *(this);	
		}
		mat33<type>& operator /=(type i_val){
			xx/=i_val;
			xy/=i_val;
			xz/=i_val;
			yx/=i_val;
			yy/=i_val;
			yz/=i_val;
			zx/=i_val;
			zy/=i_val;
			zz/=i_val;
		
			return *(this);	
		}
		//Trace
		type tr(){
			return xx+yy+zz;
		}
		//Print
		void print(const std::string i_str=""){
			std::cout<<i_str<<std::endl;
			std::cout<<std::fixed<<std::scientific<<std::setprecision(2);
			std::cout<<xx<<" "<<yx<<" "<<zx<<std::endl;
			std::cout<<xy<<" "<<yy<<" "<<zy<<std::endl;
			std::cout<<xz<<" "<<yz<<" "<<zz<<std::endl;
#ifndef BAN_DEFAULTFLOAT
			std::cout<<std::defaultfloat;
#endif		
			return;
		}
	};

	template <typename type> struct vec3{
		type x;
		type y;
		type z;
	
		//Constructor
		vec3();
		vec3(const type, const type, const type);
		//Destructor
		~vec3();
		//Modification
		vec3<type>& in(const type, const type, const type);
		vec3<type>& unif(const type);
		vec3<type>& func(type (*)(const type));
		vec3<type>& func(type (*)(const type, const type), const type);
		vec3<type>& zero();
		vec3<type>& std();
		vec3<type>& operator -();
		//Substitution	
		vec3<type>& operator =(const vec3<type>&);
		vec3<type>& operator +=(const vec3<type>&);
		vec3<type>& operator -=(const vec3<type>&);
		vec3<type>& operator |=(const vec3<type>&);
		vec3<type>& operator +=(const type);
		vec3<type>& operator -=(const type);
		vec3<type>& operator *=(const type);
		vec3<type>& operator /=(const type);
		//Calculation
		vec3<type> operator +(const vec3<type>&) const;
		vec3<type> operator -(const vec3<type>&) const;
		vec3<type> operator |(const vec3<type>&) const;
		vec3<type> operator *(const vec3<type>&) const;
		vec3<type> operator *(const type) const;
		vec3<type> operator /(const type) const;
		type operator ||(const vec3<type>&) const;
		mat33<type> operator &(const vec3<type>&) const;
		
		//Function
		void print() const;
		void print(const std::string) const;
		type sz() const;
		type szp2() const;
	};


	template <typename type>
	vec3<type>::vec3(){
		x=0.0;
		y=0.0;
		z=0.0;
	}
	template <typename type>
	vec3<type>::vec3(const type i_x, const type i_y, const type i_z){
		x=i_x;
		y=i_y;
		z=i_z;
	}
	template <typename type>
	vec3<type>::~vec3(){
	}
	template <typename type>
	vec3<type>& vec3<type>::func(type (*i_func)(const type)){
		x=i_func(x);
		y=i_func(y);
		z=i_func(z);
		return *(this);
	}
	template <typename type>
	vec3<type>& vec3<type>::func(type (*i_func)(const type, const type),const type i_sca){
		x=i_func(x,i_sca);
		y=i_func(y,i_sca);
		z=i_func(z,i_sca);
		return *(this);
	}
	template <typename type>
	void vec3<type>::print() const{
		std::cout<<x<<" "<<y<<" "<<z<<std::endl;
	}
	template <typename type>
	void vec3<type>::print(std::string i_str) const{
		std::cout<<i_str<<std::endl;
		std::cout<<x<<" "<<y<<" "<<z<<std::endl;
	}
	template <typename type>
	vec3<type>& vec3<type>::in(const type i_x, const type i_y, const type i_z){
		x=i_x;
		y=i_y;
		z=i_z;
		return *(this); 
	}
	template <typename type>
	vec3<type>& vec3<type>::zero(){
		x=0.0;
		y=0.0;
		z=0.0;
		return *(this);
	}
	template <typename type>
	type vec3<type>::sz() const{
		return static_cast<type>(std::sqrt(x*x+y*y+z*z));
	}
	template <typename type>
	type vec3<type>::szp2() const{
		return static_cast<type>(x*x+y*y+z*z);
	}
	template <typename type>
	vec3<type>& vec3<type>::std(){
		type sz=static_cast<type>(std::sqrt(x*x+y*y+z*z));
		x/=sz;
		y/=sz;
		z/=sz;
		return *(this);
	}
	template <typename type>
	vec3<type>& vec3<type>::unif(const type i_sca){
		x=i_sca;
		y=i_sca;
		z=i_sca;
		return *(this);
	}
	template <typename type>
	vec3<type>& vec3<type>::operator =(const vec3<type>& i_vec){
		x=i_vec.x;
		y=i_vec.y;
		z=i_vec.z;
		return *(this);
	}
	template <typename type>
	vec3<type> vec3<type>::operator +(const vec3<type>& i_vec) const{
		vec3 ot(x+i_vec.x,y+i_vec.y,z+i_vec.z);
		return ot; 
	}
	template <typename type>
	vec3<type> vec3<type>::operator -(const vec3<type>& i_vec) const{
		vec3 ot(x-i_vec.x,y-i_vec.y,z-i_vec.z);
		return ot; 
	}
	template <typename type>
	vec3<type>& vec3<type>::operator -(){
		x=-x;
		y=-y;
		z=-z;
		return *(this);
	}
	template <typename type>
	vec3<type> vec3<type>::operator |(const vec3<type>& i_vec) const{
		vec3<type> ot(x*i_vec.x,y*i_vec.y,z*i_vec.z);
		return ot;
	}		
	template <typename type>
	vec3<type> vec3<type>::operator *(const type i_sca) const{
		vec3<type> ot(x*i_sca,y*i_sca,z*i_sca);
		return ot; 
	}	
	template <typename type>
	vec3<type> vec3<type>::operator /(const type i_sca) const{
		vec3<type> ot(x/i_sca,y/i_sca,z/i_sca);
		return ot; 
	}
	template <typename type>
	vec3<type>& vec3<type>::operator +=(const vec3<type>& i_vec){
		x+=i_vec.x;
		y+=i_vec.y;
		z+=i_vec.z;
		return *(this); 
	}
	template <typename type>
	vec3<type>& vec3<type>::operator +=(const type i_sca){
		x+=i_sca;
		y+=i_sca;
		z+=i_sca;
		return *(this); 
	}
	template <typename type>
	vec3<type>& vec3<type>::operator -=(const vec3<type>& i_vec){
		x-=i_vec.x;
		y-=i_vec.y;
		z-=i_vec.z;
		return *(this); 
	}
	template <typename type>
	vec3<type>& vec3<type>::operator -=(const type i_sca){
		x-=i_sca;
		y-=i_sca;
		z-=i_sca;
		return *(this); 
	}
	template <typename type>
	vec3<type>& vec3<type>::operator |=(const vec3<type>& i_vec){
		x*=i_vec.x;
		y*=i_vec.y;
		z*=i_vec.z;
		return *(this);
	}
	template <typename type>
	vec3<type>& vec3<type>::operator *=(const type i_sca){
		x*=i_sca;
		y*=i_sca;
		z*=i_sca;
		return *(this); 
	}
	template <typename type>
	vec3<type>& vec3<type>::operator /=(const type i_sca){
		x/=i_sca;
		y/=i_sca;
		z/=i_sca;
		return *(this); 
	}
	//Inner Products
	template <typename type>
	type vec3<type>::operator ||(const vec3<type>& i_vec) const{
		return x*i_vec.x+y*i_vec.y+z*i_vec.z;
	}

	//Tensor Products
	template <typename type>
	mat33<type> vec3<type>::operator &(const vec3<type>& i_vec) const{
		mat33<type> ot;
		type x=vec3<type>::x;
		type y=vec3<type>::y;
		type z=vec3<type>::z;
		ot.xx=x*i_vec.x;
		ot.xy=y*i_vec.x;
		ot.xz=z*i_vec.x;
		ot.yx=x*i_vec.y;
		ot.yy=y*i_vec.y;
		ot.yz=z*i_vec.y;
		ot.zx=x*i_vec.z;
		ot.zy=y*i_vec.z;
		ot.zz=z*i_vec.z;
		return ot;
	}
	//Cast
*/	

}
/*
template <typename cast> matvec::vec3<cast> matvec_cast(matvec::vec3<auto> i_vec3){
	matvec::vec3<cast> ot;
	ot.x=static_cast<cast>(i_vec3.x);
	ot.y=static_cast<cast>(i_vec3.y);
	ot.z=static_cast<cast>(i_vec3.z);
	return ot;
}
*/
#ifndef OLD_GPP
std::ostream& operator<<(std::ostream& os, const matvec::vec3<auto>& i_vec3){
	os<<i_vec3.x<<" "<<i_vec3.y<<" "<<i_vec3.z;
	return os;
}
std::ostream& operator<<(std::ostream& os, const matvec::mat33<auto>& i_mat33){
	os<<i_mat33.xx<<" "<<i_mat33.yx<<" "<<i_mat33.zx<<std::endl
	  <<i_mat33.xy<<" "<<i_mat33.yy<<" "<<i_mat33.zy<<std::endl
	  <<i_mat33.xz<<" "<<i_mat33.yz<<" "<<i_mat33.zz;
	return os;
}
std::ostream& operator<<(std::ostream& os,const matvec::mat<auto>& i_mat){
	uint row=i_mat.row();
	uint col=i_mat.column();
	auto* elem=i_mat.elements();
	for(uint a=0; a<row; ++a){
		if(a!=0) os<<std::endl;
		for(uint b=0, c=0; c<col; b+=row, ++c){
				os<<elem[a+b]<<" ";
		}
	}
	return os;
}
#endif

#endif
