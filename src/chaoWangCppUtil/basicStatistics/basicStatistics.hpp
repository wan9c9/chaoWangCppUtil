#ifndef STATMODELS_BASIC_STATISTICS_HPP
#define STATMODELS_BASIC_STATISTICS_HPP

#include<chaoWangCppUtil/prereqs.hpp>

//template<typename T> double mean(const T&b, const T&e);
//template<typename T> double moment(const T&b, const T&e,const unsigned &order=2);
//template<typename T> double variance(const T&b, const T&e);
//template<typename T1,typename T2> double covariance(const T1&b1, const T1&e1, const T2&b2, const T2&e2);
//template<typename T1,typename T2> double correlation(const T1&b1, const T1&e1, const T2&b2, const T2&e2);
//template<typename T> arma::vec acf(const T&b, const T&e, const unsigned &lag);

template<typename T>
inline std::vector<T> seq(const T& from, const T&to, const T &by);

template<typename T>
double mean(const T&b, const T&e)
{
	double m=0;
	auto &i=b;
	while(i!=e){
		m += *i++;
	}
	m/=e-b;
	return m;
}

template<typename T>
double moment(const T&b, const T&e,const unsigned &order=2)
{
    double m=0;
	auto i=b;
	while(i!=e){
		m += std::pow(*i++,order);
	}
	m/=e-b;
	return m;
}

template<typename T> double variance(const T&b, const T&e)
{
	double m = mean(b,e);
	double m2 = moment(b,e,2);
	return m2-m*m;
}

template<typename T1,typename T2> double covariance(const T1&b1, const T1&e1, const T2&b2, const T2&e2)
{
	auto m1 = mean(b1,e1);
	auto m2 = mean(b2,e2);
	std::vector<double> cross;
	auto &i1=b1;
	auto &i2=b2;
	while(i1!=e1 && i2!=e2){
		cross.push_back((*i1++)*(*i2++));
	}
	auto m3 = mean(cross.begin(),cross.end());
	return m3-m1*m2;
}

template<typename T1,typename T2> double correlation(const T1&b1, const T1&e1, const T2&b2, const T2&e2)
{
	auto c = covariance(b1,e1,b2,e2);
	auto v1 = variance(b1,e1);
	auto v2 = variance(b2,e2);
	return c/(sqrt(v1*v2));
}

template<typename T> arma::vec acf(const T&b, const T&e, const unsigned &lag)
{
	arma::vec ret(lag);
	for(unsigned i=0;i<lag;++i)
	{
		ret[i] = correlation(b,e-i,b+i,e);
	}
	return ret;
}


//arma::vec acf(const arma::vec &x, const unsigned &lag);
double sampleQuantile(const arma::vec &x, const double &q);
arma::vec sampleQuantile(const arma::vec &x, const arma::vec &qs);

//calculate the linear regression of y~x
void linearRegression(const arma::mat &x,const arma::vec &y,arma::vec &coeffs);
void linearRegression(const arma::vec &y, const arma::mat &x,arma::vec &coeffs);
arma::vec linearRegression(const arma::vec &y, const arma::mat &x); 
void autoRegression(const arma::vec &y, unsigned const &order, arma::vec &coeffs, bool addIntercept=true);


#endif
