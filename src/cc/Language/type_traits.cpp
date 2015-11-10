
#include "type_traits.hpp"

#include <cassert>
#include <iostream>

#include <boost/type_index.hpp>

using namespace study;

int main(int argc, char **argv) {

  // conditional
  static_assert(is_same<conditional<true, int, char>::type, int>::value, "");
  static_assert(!is_same<conditional<true, char, int>::type, int>::value, "");
  static_assert(is_same<conditional<false, char, int>::type, int>::value, "");
  static_assert(!is_same<conditional<false, int, char>::type, int>::value, "");
  static_assert(is_same<conditional_t<true, int, char>, int>::value, "");
  static_assert(!is_same<conditional_t<true, char, int>, int>::value, "");
  static_assert(is_same<conditional_t<false, char, int>, int>::value, "");
  static_assert(!is_same<conditional_t<false, int, char>, int>::value, "");

  // enable_if
  static_assert(is_same<enable_if<true, int>::type, int>::value, "");
  static_assert(is_same<enable_if_t<true, int>, int>::value, "");

  // integral_constant
  static_assert(integral_constant<int, 5>::value == 5, "");
  static_assert(!(integral_constant<int, 5>::value == 6), "");
  static_assert(is_same<integral_constant<int, 5>::value_type, int>::value, "");
  std::string ict(boost::typeindex::type_id_with_cvr<integral_constant<int, 5>::type>().pretty_name());
  assert(ict.compare("study::integral_constant<int, 5>") == 0);
  static_assert(integral_constant<int, 5>()() == 5, "");
  static_assert(!(integral_constant<int, 5>()() == 6), "");
  static_assert((int)integral_constant<int, 5>() == 5, "");
  static_assert((int)integral_constant<int, 5>() == 5, "");
  static_assert(!((int)integral_constant<int, 5>() == 6), "");
  
  // bool_constant
  static_assert(bool_constant<true>::value, "");
  static_assert(!bool_constant<false>::value, "");
  static_assert(is_same<bool_constant<true>::value_type, bool>::value, "");
  std::string bct(boost::typeindex::type_id_with_cvr<bool_constant<true>::type>().pretty_name());
  assert(bct.compare("study::integral_constant<bool, true>") == 0);
  static_assert(bool_constant<true>()(), "");
  static_assert(!bool_constant<false>()(), "");
  static_assert(bool_constant<true>(), "");
  static_assert(!bool_constant<false>(), "");

  // true_type
  static_assert(true_type::value, "");

  // false_type
  static_assert(!false_type::value, "");
  
  // is_const
  static_assert(is_const<const int>::value, "");
  static_assert(!is_const<int>::value, "");

  // is_volatile
  static_assert(is_volatile<volatile int>::value, "");
  static_assert(!is_volatile<int>::value, "");

  // remove_const
  static_assert(is_same<remove_const<int>::type, int>::value, "");
  static_assert(is_same<remove_const<const int>::type, int>::value, "");
  static_assert(is_same<remove_const_t<const int>, int>::value, "");

  // remove_volatile
  static_assert(is_same<remove_volatile<int>::type, int>::value, "");
  static_assert(is_same<remove_volatile<volatile int>::type, int>::value, "");
  static_assert(is_same<remove_volatile_t<volatile int>, int>::value, "");

  // remove_cv
  static_assert(is_same<remove_cv<const int>::type, int>::value, "");
  static_assert(is_same<remove_cv<volatile int>::type, int>::value, "");
  static_assert(is_same<remove_cv<const volatile int>::type, int>::value, "");
  static_assert(is_same<remove_cv<volatile const int>::type, int>::value, "");
  static_assert(is_same<remove_cv_t<const int>, int>::value, "");
  static_assert(is_same<remove_cv_t<volatile int>, int>::value, "");
  static_assert(is_same<remove_cv_t<const volatile int>, int>::value, "");
  static_assert(is_same<remove_cv_t<volatile const int>, int>::value, "");

  // is_void
  static_assert(is_void<void>::value, "");

  // is_integral
  static_assert(is_integral<bool>::value, "");
  static_assert(is_integral<char>::value, "");
  static_assert(is_integral<signed char>::value, "");
  static_assert(is_integral<unsigned char>::value, "");
  static_assert(is_integral<wchar_t>::value, "");
  static_assert(is_integral<int>::value, "");
  static_assert(is_integral<unsigned int>::value, "");
  static_assert(is_integral<long>::value, "");
  static_assert(is_integral<unsigned long>::value, "");
  static_assert(is_integral<long long>::value, "");
  static_assert(is_integral<unsigned long long>::value, "");
  static_assert(is_integral<const bool>::value, "");
  static_assert(is_integral<volatile bool>::value, "");
  static_assert(!is_integral<char *>::value, "");
  static_assert(!is_integral<int &>::value, "");
  static_assert(!is_integral<float>::value, "");
  static_assert(!is_integral<double>::value, "");

  // is_floating_point
  static_assert(is_floating_point<float>::value, "");
  static_assert(is_floating_point<double>::value, "");
  static_assert(is_floating_point<long double>::value, "");
  static_assert(!is_floating_point<char>::value, "");
  static_assert(!is_floating_point<int>::value, "");
  static_assert(is_floating_point<const float>::value, "");
  static_assert(is_floating_point<volatile float>::value, "");

  // is_array
  static_assert(is_array<int[]>::value, "");
  static_assert(is_array<int[8]>::value, "");
  static_assert(!is_array<int>::value, ""); 
  static_assert(!is_array<int *>::value, ""); 
}
