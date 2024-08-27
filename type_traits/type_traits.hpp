#include <iostream>

namespace TypeTraits {

template <typename T, T val>
struct integral_constant {
    static constexpr T value = val;
    using type = T;
    using value_type = integral_constant;
    constexpr operator value_type() const noexcept { 
        return value; 
    }
    constexpr value_type operator()() const noexcept { 
        return value; 
    }
};  

template <bool val>
struct bool_constant : integral_constant<bool, val>
{};

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

template <typename T, typename U>
struct is_same : false_type
{};

template <typename T>
struct is_same<T, T> : true_type
{};

template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

template <typename T> 
struct remove_const
{
    using type = T;
};

template <typename T>
struct remove_const<const T> 
{
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename T>
struct remove_volatile 
{
    using type = T;
};

template <typename T>
struct remove_volatile<volatile T> 
{
    using type = T;
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
struct remove_cv
{
    using type = remove_volatile_t<remove_const_t<T>>; 
};

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

 
template <typename T>
struct add_const 
{ 
    typedef const T type; 
};
 
template <typename T>
using add_const_t = typename add_const<T>::type;

template <typename T>
struct add_volatile 
{ 
    typedef volatile T type; 
};

template <typename T>
using add_volatile_t = typename add_volatile<T>::type;

template <typename T>
struct add_cv 
{ 
    typedef const volatile T type; 
};

template <typename T>
using add_cv_t = typename add_cv<T>::type;

template <typename T>
struct is_const : false_type
{};

template <typename T>
struct is_const<const T> : true_type
{};

template <typename T>
inline constexpr bool is_const_v = is_const<T>::value;

template <typename T>
struct is_volatile : false_type
{};

template <typename T>
struct is_volatile<volatile T> : true_type
{};

template <typename T>
inline constexpr bool is_volatile_v = is_volatile<T>::value;

template <typename T>
struct is_void : is_same<remove_cv<T>, void>
{};

template <typename T>
using is_void_v = typename is_void<T>::value;

template <typename T>
struct is_null_pointer : is_same<std::nullptr_t, remove_cv<T>>
{};

template <typename T>
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

template< class T >
struct is_integral : bool_constant<
    requires (T t, T* ptr, void (*f)(T)) {
        reinterpret_cast<T>(t);
        ptr + t;
        f(0);
    }
> {};

template <typename T>
inline constexpr bool is_integral_v = is_integral<T>::value;

template<typename T>
struct is_floating_point : integral_constant <bool, 
       is_same<float, typename remove_cv<T>::type>::value
    || is_same<double, typename remove_cv<T>::type>::value
    || is_same<long double, typename remove_cv<T>::type>::value
> {};

template <typename T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;


template <typename T>
struct is_array : false_type 
{};
 
template <typename T>
struct is_array<T[]> : true_type 
{};
 
template <typename T, std::size_t N>
struct is_array<T[N]> : true_type 
{};

template <typename T>
inline constexpr bool is_array_v = is_array<T>::value;

template <typename T>
struct is_pointer : std::false_type 
{};
 
template <typename T>
struct is_pointer<T*> : std::true_type 
{};
 
template <typename T>
struct is_pointer<T* const> : std::true_type 
{};
 
template <typename T>
struct is_pointer<T* volatile> : std::true_type 
{};
 
template <typename T>
struct is_pointer<T* const volatile> : std::true_type 
{};

template <typename T> 
struct remove_pointer 
{ 
    typedef T type; 
};

template <typename T> 
struct remove_pointer<T*> 
{ 
    typedef T type; 
};

template <typename T> 
struct remove_pointer<T* const> 
{ 
    typedef T type; 
};

template <typename T> 
struct remove_pointer<T* volatile>
{ 
    typedef T type; 
};

template <typename T> 
struct remove_pointer<T* const volatile>
{ 
    typedef T type; 
};

template <typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

template <typename T>
using is_void_v = typename is_void<T>::value;

template <typename T>
struct is_lvalue_reference : false_type
{};

template <typename T>
struct is_lvalue_reference<T&> : true_type
{};

template< class T >
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

template <typename T>
struct is_rvalue_reference : false_type
{};

template <typename T>
struct is_rvalue_reference<T&&> : true_type
{};

template <typename T>
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;


template <typename T>
struct is_reference : false_type
{};

template <typename T>
struct is_reference<T&> : true_type
{};

template <typename T>
struct is_reference<T&&> : true_type
{};

template <typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;

template <typename T>
struct remove_reference
{
    using type = T;
};

template <typename T>
struct remove_reference<T&>
{
    using type = T;
};

template <typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template <typename T>
struct is_member_function_pointer_helper : std::false_type 
{};
 
template <typename T, typename U>
struct is_member_function_pointer_helper<T U::*> : std::is_function<T> 
{};
 
template <typename T>
struct is_member_function_pointer : is_member_function_pointer_helper<typename std::remove_cv<T>::type> 
{};

template <typename T>
inline constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;


template <typename T>
struct is_member_object_pointer : std::integral_constant<bool, std::is_member_pointer<T>::value && !std::is_member_function_pointer<T>::value> {};

template <typename T>
inline constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

template <typename T>
struct is_arithmetic : integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value>
{};

template <typename T>
inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

template <typename T>
struct is_fundamental : integral_constant<bool, is_arithmetic<T>::value || 
                                                 is_void<T>::value ||
                                                 is_null_pointer<T>::value
>{};

template <typename T>
inline constexpr bool is_fundamental_v = is_fundamental<T>::value;


template <typename T>
struct is_member_pointer_helper : false_type {};
 
template <typename T, typename U>
struct is_member_pointer_helper<T U::*> : true_type {};
 
template <typename T>
struct is_member_pointer : is_member_pointer_helper<typename remove_cv<T>::type> {};

template <typename T>
struct remove_cvref
{
    using type = remove_reference<remove_cv_t<T>>::type;
};

template <typename T>
using remove_cvref_t = remove_cvref<T>::type;

template <typename T>
struct is_class : integral_constant<bool, __is_class(T)>
{};

template <typename T>
inline constexpr bool is_class_v = is_class<T>::value;

template <typename T>
struct is_union : integral_constant<bool, __is_union(T)>
{};

template <typename T>
inline constexpr bool is_union_v = is_union<T>::value;

template <typename T>
struct is_enum : integral_constant<bool, __is_enum(T)>
{};

template <typename T>
inline constexpr bool is_enum_v = is_enum<T>::value;

template <typename T>
struct is_compound : std::integral_constant<bool, !std::is_fundamental<T>::value> 
{};

template <typename T>
inline constexpr bool is_compound_v = is_compound<T>::value;

template <typename T>
struct is_scalar : integral_constant<bool, is_arithmetic<T>::value
        || is_enum<T>::value
        || is_pointer<T>::value
        || is_member_pointer<T>::value
        || is_null_pointer<T>::value>
{};

template <typename T>
inline constexpr bool is_scalar_v = is_scalar<T>::value;

template <typename T>
struct is_object : integral_constant<bool,
                                            is_scalar<T>::value ||
                                            is_array<T>::value ||
                                            is_union<T>::value ||
                                            is_class<T>::value> 
{};

template <typename T>
inline constexpr bool is_object_v = is_object<T>::value;


template<bool B, typename T = void>
struct enable_if 
{};
 
template <typename T>
struct enable_if<true, T> 
{   
    typedef T type; 
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B,T>::type;

template <bool B, typename T, typename F>
struct conditional 
{ 
    using type = T; 
};
 
template <typename T, typename F>
struct conditional<false, T, F> 
{ 
    using type = F; 
};

template <bool B, typename T, typename F >
using conditional_t = typename conditional<B,T,F>::type;

template <typename T>
struct add_lvalue_reference
{
    using type = T&;
};

template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template <typename T>
struct add_rvalue_reference
{
    using type = T&&;
};

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <typename T>
struct add_pointer
{
    using type = T;
};

template <typename T>
struct add_pointer<T*>
{
    using type = T;
};

template <typename T>
struct add_pointer<T* const>
{
    using type = T;
};

template <typename T>
struct add_pointer<T* volatile>
{
    using type = T;
};

template <typename T>
struct add_pointer<T* const volatile>
{
    using type = T;
};

template <typename T>
using add_pointer_t = add_pointer<T>::type;



}