#ifndef MV_FORWARD_HPP
#define MV_FORWARD_HPP

#include <cstdint>
#include <limits>
#include <type_traits>

//======================//
//    namespace : mv    //
//======================//
namespace mv{


    //+    Type Definition    +//
    //(    mv::null Void    )//
    union null{

    };



    //+    Constant Expression Function Definition    +//
//    template <typename T> constexpr auto is_valid (T) -> std::is_same_v<null>


    template <typename T> constexpr auto upgrade_signed (T) -> std::enable_if_t< std::numeric_limits<T>::is_signed, intmax_t>;
    template <typename T> constexpr auto upgrade_signed (T) -> std::enable_if_t<!std::numeric_limits<T>::is_signed, uintmax_t>;
    template <typename T> constexpr auto upgrade        (T) -> std::enable_if_t< std::numeric_limits<T>::is_integer, decltype(upgrade_signed(std::declval<T>()))>;
    template <typename T> constexpr auto upgrade        (T) -> std::enable_if_t<!std::numeric_limits<T>::is_integer, long double>;
    
    template <typename T> constexpr auto unary_operator_plus (T) -> std::enable_if_t< std::numeric_limits<T>::is_specialized, decltype(upgrade(std::declval<T>()))>;
    template <typename T> constexpr auto unary_operator_plus (T) -> std::enable_if_t<!std::numeric_limits<T>::is_specialized, decltype(+std::declval<T>())>;

};
#endif
