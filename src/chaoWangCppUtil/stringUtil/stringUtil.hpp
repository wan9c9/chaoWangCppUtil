#ifndef STRINGUTIL_HPP
#define STRINGUTIL_HPP

#include <string>
#include <algorithm>

namespace stringUtil
{
	// trim functions from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring/217605#217605
	
	// trim from start
	std::string & trimLeft(std::string &s);
	
	// trim from end
	std::string & trimRight(std::string &s);
	
	// trim from both ends
	std::string & trim(std::string &s);
	
	// trim from start
	inline std::string & trimLeft(const std::string &s);
	
	// trim from end
	inline std::string & trimRight(const std::string &s);
	
	// trim from both ends
	inline std::string & trim(const std::string &s);
	
	inline bool ends_with(std::string const & value, std::string const & ending)
	{
			if (ending.size() > value.size()) return false;
			return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
	}
	//inline bool ends_with(std::string const & value, std::string const & ending);
}

#endif
