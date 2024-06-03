#ifndef MATVEC_MV_MV_HPP
#define MATVEC_MV_MV_HPP

#include <typeinfo>
#include <iostream>
#include <cmath>

namespace mv{

    typedef float       scaf;
    typedef double      sca;
    typedef long double scal;

	template <typename Type=sca> struct vec2;
	template <typename Type=sca> struct vec3;
    template <typename Type=sca> struct vec4;
	template <typename Type=sca> struct mat22;
	template <typename Type=sca> struct mat33;
	template <typename Type=sca> struct mat44;
	template <typename Type=sca> class  vec;
	template <typename Type=sca> class  mat;
	template <typename Type=sca> class  tensor;

    namespace temp{
        template <typename Type=sca> class vec;
        template <typename Type=sca> class mat;
        template <typename Type=sca> class tensor;
    }
}

#endif
