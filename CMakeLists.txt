cmake_minimum_required(VERSION 3.8)

project("Bin to Hex Converter")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## target binary file
set(TARGET_FILE
	"bin2hex"
)

## header files
set(INC_FILES
	
)

## source files
set(SRC_FILES
	"src/main.cpp"
)

## add source and header files to this project's executable
add_executable(${TARGET_FILE} ${SRC_FILES} ${INC_FILES})

## add include directories
target_include_directories(${TARGET_FILE} PRIVATE "include")

## add libraries
# <lib>
#find_package(<lib> CONFIG REQUIRED)
#target_link_libraries(${TARGET_FILE} PRIVATE <lib>)

## copy resource files to build directory
#add_custom_target(copy_resources ALL
#	COMMAND ${CMAKE_COMMAND} -E remove_directory
#	${CMAKE_CURRENT_BINARY_DIR}/resources
#
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#	${CMAKE_CURRENT_SOURCE_DIR}/resources
#	${CMAKE_CURRENT_BINARY_DIR}/resources
#)
#add_dependencies(${TARGET_FILE} copy_resources)

## copy dynamic library and resource files from build to install directory
install(TARGETS ${TARGET_FILE} DESTINATION ${CMAKE_INSTALL_PREFIX})
#install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resources DESTINATION ${CMAKE_INSTALL_PREFIX})
