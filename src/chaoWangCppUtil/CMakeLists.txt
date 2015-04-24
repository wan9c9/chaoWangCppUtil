include_directories(..)

# Add summary to list of sources.
set(CHAO_WANG_CPP_UTIL_SRCS ${CHAO_WANG_CPP_UTIL_SRCS}
	"${CMAKE_CURRENT_SOURCE_DIR}/chaoWangCppUtil.hpp")

##recurse into different utils
set(DIRS
	basicStatistics
	logger
	mathUtil
	rankerUtil
	stringUtil
	miscUtil
	)

foreach(dir ${DIRS})
    add_subdirectory(${dir})
endforeach()

	
add_library(chaoWangCppUtil SHARED ${CHAO_WANG_CPP_UTIL_SRCS})

target_link_libraries(chaoWangCppUtil 
	${ARMADILLO_LIBRARIES}
	${Boost_LIBRARIES}
	${SQLITE3_LIBRARIES}
        ${NLOPT_LIBRARIES}
	)

set_target_properties(chaoWangCppUtil
	PROPERTIES
	VERSION 1.0
	SOVERSION 1
	)

# Make sure the linker can find the needed library.
# rt: clock_gettime()
if(UNIX AND NOT APPLE)
    target_link_libraries(chaoWangCppUtil rt)
endif(UNIX AND NOT APPLE)




# Collect all header files in the library.
file(GLOB_RECURSE INCLUDE_H_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE INCLUDE_HPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)
set(INCLUDE_FILES ${INCLUDE_H_FILES} ${INCLUDE_HPP_FILES})

# Move all of these header files to <builddir>/include/chaoWangCppUtil/ after the library
# is built.  First we have to create that directory though.
add_custom_target(chaoWangCppUtil_headers)
add_custom_command(TARGET chaoWangCppUtil_headers POST_BUILD
	COMMENT "Moving header files to include/chaoWangCppUtil/"
  COMMAND ${CMAKE_COMMAND} ARGS -E
    make_directory ${CMAKE_BINARY_DIR}/include/chaoWangCppUtil/)


# Then copy each of the header files over to that directory.
foreach(incl_file ${INCLUDE_FILES})
  add_custom_command(TARGET chaoWangCppUtil_headers POST_BUILD
    COMMAND ${CMAKE_COMMAND} ARGS -E
      copy ${CMAKE_CURRENT_SOURCE_DIR}/${incl_file}
           ${CMAKE_BINARY_DIR}/include/chaoWangCppUtil/${incl_file})
endforeach()

# At install time, we simply install that directory of header files we
# collected to include/.
install(DIRECTORY ${CMAKE_BINARY_DIR}/include/chaoWangCppUtil DESTINATION
	include)

# Set generated executables to be installed.  Unfortunately they must manually
# be entered...
install(TARGETS chaoWangCppUtil 
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
	)

add_dependencies(chaoWangCppUtil chaoWangCppUtil_headers)

# For 'make test'.
#add_custom_target(test
#	${CMAKE_BINARY_DIR}/bin/chaoWangCppUtil_test "--log_level=test_suite" # Set UTF runtime param
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/ # This is where test files are put.
#	COMMENT "Running CHAO_WANG_CPP_UTIL test"
#	DEPENDS chaoWangCppUtil_test)

