#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP
#include<chaoWangCppUtil/prereqs.hpp>

template<typename T1, typename T2> inline
double relatDiff(const T1 &x, const T2 &y){ return fabs((x-y)/(x+y)/2.0); }

// NaN management
double setNan();

template<typename T> void setNan(T &v) { v=setNan(); }

void setNan(arma::vec & v);

template<typename T> bool checkNan(const T& v){ return isnan(v);}

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

// 
template<typename T>
std::vector<double> simpleReturn(const std::vector<T> & val, const unsigned &period=1)
{
    std::vector<double> ret;
    if(val.size() >= period)
    {
      for(auto i=val.cbegin();i!=val.cend()-period;++i)
          ret.push_back( *(i+period)/(*i)-1.0);
    }
    return ret;
}

arma::vec positivePart(const arma::vec &orig);
arma::vec negativePart(const arma::vec &orig);

double backShift(const arma::vec & coeff, const arma::vec & series, const std::size_t & index);
arma::vec backShift(const arma::vec & coeff, const arma::mat & series, const std::size_t & index);

arma::vec isPositive(const arma::vec & orig);
arma::vec isNegative(const arma::vec & orig);
arma::vec reverseVec(const arma::vec &orig);

arma::mat sqrtMat(const arma::vec &m);



#endif
