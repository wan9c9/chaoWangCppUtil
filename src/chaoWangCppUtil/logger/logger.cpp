#include"logger.hpp"
#include<chaoWangCppUtil/chaoWangCppUtil.hpp>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/utility/empty_deleter.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;


BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", LoggingLevel)
BOOST_LOG_ATTRIBUTE_KEYWORD(scope, "Scope", attrs::named_scope::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(timeline, "Timeline", attrs::timer::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", attrs::local_clock::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)

LoggingLevel getLoggingLevel(unsigned i){
	switch(i){
		case 0: return LoggingLevel::trace;
		case 1: return LoggingLevel::debug;
		case 2: return LoggingLevel::info;
		case 3: return LoggingLevel::warning;
		case 4: return LoggingLevel::error;
		case 5: return LoggingLevel::critical;
		default: return LoggingLevel::info;
	}
}




// The operator puts a human-friendly representation of the severity level to the stream
std::ostream& operator<< (std::ostream& strm, const LoggingLevel &level) {
    static const char* strings[] = {"trace", "debug", "info", "warning", "error", "critical"};

    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << '<' << strings[static_cast<int>(level)] << '>';
    else
        strm << static_cast< int >(level);

    return strm;
}

void initLogger(const std::string &fileName, const LoggingLevel &level){
  std::cout << "logger level: " << level << std::endl;
	std::cout << " log file will be stored in " << fileName << std::endl;

	typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
	boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();
	sink->locked_backend()->add_stream(boost::make_shared< std::ofstream >(fileName));
    
	boost::shared_ptr< std::ostream > stream(&std::clog, boost::empty_deleter());
	sink->locked_backend()->add_stream(stream);
    
	sink->set_formatter
    (
        expr::stream
            << std::hex << std::setw(8) << std::setfill('0') << line_id << std::dec << std::setfill(' ')
	    << expr::if_(expr::has_attr(timestamp))
               [
                    expr::stream << " [" << timestamp << "] "
               ]
            << expr::if_(expr::has_attr(timeline))
               [
                    expr::stream << " [" << timeline << "] "
               ]
            << std::right << severity << "\t"
            //<< std::right << ": <"  << severity << ">\t"
            //<< "(" << scope << ") "
            << expr::if_(expr::has_attr(tag_attr))
               [
                    expr::stream << "[" << tag_attr << "] "
               ]
            << expr::smessage
    );

    logging::core::get()->add_sink(sink);
	logging::core::get()->set_filter(severity >= level);
    // Add attributes
    logging::add_common_attributes();
    logging::core::get()->add_global_attribute("Scope", attrs::named_scope());
        sink->flush();
    LOGGER_INFO << "logger initialized";
}

void addToLogger(const LoggingLevel &level, const std::string &tag, const std::string &msg) {
    //BOOST_LOG_NAMED_SCOPE(__func__);
    BOOST_LOG_SCOPED_THREAD_ATTR("TimeStamp", attrs::local_clock());
    BOOST_LOG_SCOPED_THREAD_ATTR("Timeline", attrs::timer());
	auto & mlgr = my_logger::get();
    mlgr.add_attribute("Tag", attrs::constant< std::string >(tag));
    BOOST_LOG_SEV(mlgr, level) << msg;
}

void addToLogger( const std::string &msg, const std::string &tag, const LoggingLevel &level) {
	std::cout << " calling version 2" << std::endl;
	addToLogger(level,tag, msg);
}
