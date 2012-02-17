CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Basic Definitions 
PROJECT(libmessenger)

SET(BUILD_SHARED_LIBS ON)
SET(CMAKE_BUILD_TYPE DEBUG)

IF(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS_DEBUG  "-g3")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined -fPIC")

# Code Definitions
SET(include_files
			include/IMessenger.h
			include/IMessengerListener.h    
			include/MessengerFactory.h   
			include/Messenger.h)
			
SET(src_files     
			src/Messenger.cpp
			src/MessengerFactory.cpp)

SET(install_headers 
			include/IMessenger.h
			include/IMessengerListener.h    
			include/MessengerFactory.h)

INCLUDE_DIRECTORIES(
			${libmessenger_SOURCE_DIR}/include
			/usr/local/include/activemq-cpp-3.5.0
			/usr/local/apr/include/apr-1)

# Compile Options
ADD_LIBRARY(messenger ${src_files})
			
TARGET_LINK_LIBRARIES(messenger cpputil activemq-cpp)

# Install Options
INSTALL (TARGETS messenger LIBRARY DESTINATION lib)

# INSTALL (TARGETS messenger ARCHIVE DESTINATION lib)

INSTALL (FILES ${install_headers} DESTINATION include/libmessenger)

LINK_DIRECTORIES (${libmessenger_BINARY_DIR})

# TESTES

ADD_EXECUTABLE(amazontest test/amazontest.cpp)
TARGET_LINK_LIBRARIES (amazontest messenger)

ADD_EXECUTABLE(linceTest test/linceTest.cpp)
TARGET_LINK_LIBRARIES (linceTest messenger)