#include "mathUtil.hpp"
#include<chaoWangCppUtil/chaoWangCppUtil.hpp>

double setNan()
{ 
	return std::numeric_limits<double>::quiet_NaN(); 
}

void setNan(arma::vec & v)
{
	auto i=v.begin();
	while( i != v.end())
		*(i++) = setNan();
}


arma::vec positivePart(const arma::vec &orig) {
    arma::vec val(orig);
    val.elem(arma::find(val < 0)).zeros();
    return val;
}

arma::vec negativePart(const arma::vec &orig) {
    return positivePart(-orig);
}

double backShift(const arma::vec & coeff, const arma::vec & series, const std::size_t & index) {
    double val = 0;
    for (std::size_t i = 0; i < coeff.n_elem; ++i)
        val += coeff[i] * series[index - 1 - i];
    return val;
}

arma::vec backShift(const arma::vec & coeff, const arma::mat & series, const std::size_t & index) {
    arma::rowvec val = arma::zeros<arma::rowvec>(series.n_cols);
    for (std::size_t i = 0; i < coeff.n_elem; ++i)
        val += coeff[i] * series.row(index - 1 - i);
    return val.t();
}

arma::vec isPositive(const arma::vec & orig) {
    arma::vec val = arma::zeros<arma::vec>(orig.n_elem);
    val.elem(arma::find(orig > 0)).ones();
    return val;
}

arma::vec isNegative(const arma::vec & orig) {
    arma::vec val = arma::zeros<arma::vec>(orig.n_elem);
    val.elem(arma::find(orig < 0)).ones();
    return val;
}

arma::vec reverseVec(const arma::vec &orig) {
    auto val = orig;
    for (std::size_t i = 0; i < orig.n_elem / 2; ++i) {
        std::swap(val[i], val[orig.n_elem - 1 - i]);
    }
    return val;
}

arma::mat sqrtMat(const arma::vec &m)
{
	arma::vec eigval;
	arma::mat eigvec;
	arma::eig_sym(eigval,eigvec,m);

	return eigvec*arma::diagmat(arma::sqrt(eigvec))*arma::trans(eigvec);
}



