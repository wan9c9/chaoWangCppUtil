#ifndef LOGGING_HPP
#define LOGGING_HPP
#include<string>
#include<ostream>

#include <boost/log/sources/global_logger_storage.hpp>
#include<boost/log/attributes/scoped_attribute.hpp>
#include<boost/log/attributes/named_scope.hpp>
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



enum class LoggingLevel
{
	trace,
    debug,
    info,
    warning,
    error,
    critical
};

LoggingLevel getLoggingLevel(unsigned i);

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, boost::log::sources::severity_logger_mt<LoggingLevel>)

void initLogger(const std::string &fileName="loggerFile.dat", const LoggingLevel &level=LoggingLevel::trace);
void addToLogger(const LoggingLevel &level, const std::string &tag, const std::string &msg);
void addToLogger(const std::string &msg, const std::string &tag, const LoggingLevel &level = LoggingLevel::info);

//#define LOGGER_FUNC BOOST_LOG_FUNCTION()
#define LOGGER_FUNC BOOST_LOG_NAMED_SCOPE(__func__)

#define LOGGER_SCOPE(s) BOOST_LOG_NAMED_SCOPE(s)

#define LOGGER_ADD_TIMER \
    BOOST_LOG_SCOPED_THREAD_ATTR("Timeline", boost::log::attributes::timer());

#define LOGGER_TRACE \
    BOOST_LOG_SEV(my_logger::get(), LoggingLevel::trace) << "(" << __FILE__ << ", " << __LINE__ << ") "


#define LOGGER_DEBUG \
    BOOST_LOG_SEV(my_logger::get(), LoggingLevel::debug) << "(" << __FILE__ << ", " << __LINE__ << ") "

#define LOGGER_INFO \
    BOOST_LOG_SEV(my_logger::get(), LoggingLevel::info) << "(" << __FILE__ << ", " << __LINE__ << ") "

#define LOGGER_WARNING \
    BOOST_LOG_SEV(my_logger::get(), LoggingLevel::warning) << "(" << __FILE__ << ", " << __LINE__ << ") "


#define LOGGER_ERROR \
    BOOST_LOG_SEV(my_logger::get(), LoggingLevel::error) << "(" << __FILE__ << ", " << __LINE__ << ") "


#define LOGGER_CRITICAL \
    BOOST_LOG_SEV(my_logger::get(), LoggingLevel::critical) << "(" << __FILE__ << ", " << __LINE__ << ") "



#endif
