/*
 * defines the miscs functions.
*/


#ifndef MISC_UTIL_HPP
#define MISC_UTIL_HPP

#include<chaoWangCppUtil/prereqs.hpp>



template <typename T>
std::string to_string(const T &a_value, const int n = 3)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(n) << a_value;
    return out.str();
}

template <typename iterT>
std::string join(iterT ibeg, iterT iend, const std::string & del=" ")
{
    std::ostringstream out;
    auto i = ibeg;
    out << *i;
    while(++i !=iend)
      out << del << *i;
    return out.str();
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, " "));
	return os;
}



void notImplementedError(const std::string &f);



#endif
