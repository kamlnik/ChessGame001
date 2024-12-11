#ifndef MY_LIB_STRINGHELPERS_HPP
#define MY_LIB_STRINGHELPERS_HPP

#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

#include <My_lib/StringHelpers.inl>
#endif 