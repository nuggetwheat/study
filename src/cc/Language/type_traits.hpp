
#include <cstdlib>

namespace study {

  // conditional
  template <bool _Condition, class _If, class _Then>
  struct conditional { typedef _If type; };

  template <class _If, class _Then>
  struct conditional<false, _If, _Then> { typedef _Then type; };

  template <bool _Condition, class _If, class _Then> using conditional_t = typename conditional<_Condition, _If, _Then>::type;

  // enable_if
  template <bool, class _Tp = void>
  struct enable_if {};

  template <class _Tp>
  struct enable_if<true, _Tp> { typedef _Tp type; };

  template <bool _Condition, class _Tp = void> using enable_if_t = typename enable_if<_Condition, _Tp>::type;

  // integral_constant
  template <typename _Tp, _Tp __v>
  struct integral_constant {
    static constexpr const _Tp value = __v;
    typedef _Tp value_type;
    typedef integral_constant type;
    constexpr operator value_type() const { return value; }
    constexpr value_type operator ()() const { return value; }
  };

  // bool_constant
  template <bool _Bv> using bool_constant = integral_constant<bool, _Bv>;

  // true_type & false_type
  typedef bool_constant<true> true_type;
  typedef bool_constant<false> false_type;

  // is_same
  template <typename _Tp1, typename _Tp2> struct is_same : public false_type {};
  template <typename _Tp> struct is_same<_Tp, _Tp> : public true_type {};

  // is_const
  template <typename _Tp> struct is_const : false_type {};
  template <typename _Tp> struct is_const<const _Tp> : true_type {};

  // is_volatile
  template <typename _Tp> struct is_volatile : false_type {};
  template <typename _Tp> struct is_volatile<volatile _Tp> : true_type {};

  // remove_const
  template <typename _Tp> struct remove_const { typedef _Tp type; };
  template <typename _Tp> struct remove_const<const _Tp> { typedef _Tp type; };
  template <typename _Tp> using remove_const_t = typename remove_const<_Tp>:: type;

  // remove_volatile
  template <typename _Tp> struct remove_volatile { typedef _Tp type; };
  template <typename _Tp> struct remove_volatile<volatile _Tp> { typedef _Tp type; };
  template <typename _Tp> using remove_volatile_t = typename remove_volatile<_Tp>:: type;

  // remove_cv
  template <typename _Tp> struct remove_cv {
    typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;
  };
  template <typename _Tp> using remove_cv_t = typename remove_cv<_Tp>::type;

  // is_void
  template <typename _Tp> struct __is_void : false_type {};
  template <> struct __is_void<void> : true_type {};
  template <typename _Tp> struct is_void : public __is_void<typename remove_cv<_Tp>::type> {};

  // is_integral
  template <typename _Tp> struct __is_integral : public false_type {};
  template <> struct __is_integral<bool> : public true_type {};
  template <> struct __is_integral<char> : public true_type {};
  template <> struct __is_integral<signed char> : public true_type {};
  template <> struct __is_integral<unsigned char> : public true_type {};
  template <> struct __is_integral<wchar_t> : public true_type {};
  template <> struct __is_integral<int> : public true_type {};
  template <> struct __is_integral<unsigned int> : public true_type {};
  template <> struct __is_integral<long> : public true_type {};
  template <> struct __is_integral<unsigned long> : public true_type {};
  template <> struct __is_integral<long long> : public true_type {};
  template <> struct __is_integral<unsigned long long> : public true_type {};
  template <typename _Tp> struct is_integral : public __is_integral<typename remove_cv<_Tp>::type>::type {};

  // is_floating_point
  template <typename _Tp> struct __is_floating_point : public false_type {};
  template <> struct __is_floating_point<float> : public true_type {};
  template <> struct __is_floating_point<double> : public true_type {};
  template <> struct __is_floating_point<long double> : public true_type {};
  template <typename _Tp> struct is_floating_point : public __is_floating_point<typename remove_cv<_Tp>::type>::type {};

  // is_array
  template <typename _Tp> struct is_array : public false_type{};
  template <typename _Tp> struct is_array<_Tp[]> : public true_type{};
  template <typename _Tp, size_t _Np> struct is_array<_Tp[_Np]> : public true_type{};

}
