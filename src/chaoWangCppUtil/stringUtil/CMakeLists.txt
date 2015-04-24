set(SOURCES
	stringUtil.hpp
	stringUtil.cpp
	)

# add directory name to sources
set(DIR_SRCS)
foreach(file ${SOURCES})
  set(DIR_SRCS ${DIR_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
endforeach()


set(CHAO_WANG_CPP_UTIL_SRCS ${CHAO_WANG_CPP_UTIL_SRCS} ${DIR_SRCS} PARENT_SCOPE)

