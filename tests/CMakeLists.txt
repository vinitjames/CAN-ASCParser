cmake_minimum_required(VERSION 3.7...3.18)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "cmake in tests, project name ${PROJECT_NAME}" )

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
										 	   RESULT_VARIABLE result
											   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
				RESULT_VARIABLE result
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
				)

if(result)
	message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
				 EXCLUDE_FROM_ALL)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(test_message test_message.cpp)
target_link_libraries(test_message
					  canasc
					  gtest_main
					  )
add_test(NAME test_message COMMAND test_message)

add_executable(test_utils test_utils.cpp)
target_link_libraries(test_utils
					  canasc
					  gtest_main
					  )
add_test(NAME test_utils COMMAND test_utils)

add_executable(test_token test_token.cpp)
target_link_libraries(test_token
					  canasc
					  gtest_main
					  )
add_test(NAME test_token COMMAND test_token)

add_executable(test_tokenizer test_tokenizer.cpp)
target_link_libraries(test_tokenizer
					  canasc
					  gtest_main
					  )
add_test(NAME test_tokenizer COMMAND test_tokenizer)

add_executable(test_ascparser test_ascparser.cpp)
target_link_libraries(test_ascparser
					  canasc
					  gtest_main
					  )
add_test(NAME test_ascparser COMMAND test_ascparser)
