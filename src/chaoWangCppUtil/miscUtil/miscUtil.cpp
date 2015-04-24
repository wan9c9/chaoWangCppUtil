#include "miscUtil.hpp"

void notImplementedError(const std::string &f)
{
	std::stringstream ss;
	ss << "Method " << f << " is not implemeted.";
	throw std::runtime_error(ss.str());   
}
