#ifndef BASIC_STATISTICS_HPP
#define BASIC_STATISTICS_HPP

#include"basicStatistics.hpp"
#include<chaoWangCppUtil/chaoWangCppUtil.hpp>


//arma::vec acf(const arma::vec &x, const unsigned &lag) {
//	return acf(x.begin(),x.end(),lag);
//}

template<typename T>
inline std::vector<T> seq(const T& from, const T&to, const T &by)
{
	if( (to - from )*by <= 0)
		throw std::runtime_error("seq error");
	std::vector<T> ret;
	auto v=from;
	while(v < to)
	{
		ret.push_back(v);
		v += by;
	}
	return ret;
}



double sampleQuantile(const arma::vec &x, const double &q)
{
	double v[x.n_elem];
	for(unsigned i=0; i<x.n_elem;++i) 
		v[i] = x[i];
	return sampleQuantile(v,x.n_elem,q);
}

arma::vec sampleQuantile(const arma::vec &x, const arma::vec &qs)
{
  double v[x.n_elem];
	for(unsigned i=0; i<x.n_elem;++i)
		v[i] = x[i];
	arma::vec ret(qs.size());
	for(unsigned i=0; i<qs.size(); ++i)
		ret[i] = sampleQuantile(v,x.n_elem,qs[i]);
	return ret;
}


//calculate the linear regression of y~x
void linearRegression(const arma::mat &x,const arma::vec &y, arma::vec &coeffs){
	try{
		arma::mat xtx=x.t()*x;
		arma::vec xty=x.t()*y;
		coeffs = solve(xtx,xty);
	}
	catch(std::exception& e){
		std::cerr << "error in Linear Regression: " << e.what() << std::endl;
	}
}

void linearRegression(const arma::vec &y, const arma::mat &x, arma::vec &coeffs) {
	linearRegression(x,y,coeffs);
}

arma::vec linearRegression(const arma::vec &y, const arma::mat &x) {
	arma::vec coeffs;
	linearRegression(x,y,coeffs);
	return coeffs;
}


void autoRegression(const arma::vec &y, unsigned const &order, arma::vec &coeffs, bool addIntercept){
	try{
		unsigned ai=0;
		if(addIntercept)
			ai=1;
		arma::vec yReg=y.subvec(order,y.n_elem-1);
		arma::mat x(y.n_elem-order,order+ai);
		if(addIntercept)
			x.col(0).fill(1.0);
		for(unsigned i=ai;i<ai+order;++i)
			x.col(i) = y.subvec(order-(i-ai+1),y.n_elem -1 -(i-ai+1));
		linearRegression(x,yReg,coeffs);
	}
	catch (std::exception& e)
	{
		std::cerr << "error in Autoregression: " << e.what() << std::endl;
	}
}

#endif
