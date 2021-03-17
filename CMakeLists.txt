cmake_minimum_required(VERSION 3.7...3.18)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(CanAscParser VERSION 1.0
                     DESCRIPTION "A parser for can .asc for file"
                     LANGUAGES CXX)

add_library(canasc
            STATIC
            src/ascparser.cpp
            src/ascparser.h
            src/message.cpp
            src/message.h
            src/token.cpp
            src/token.h
            src/tokenizer.cpp
            src/tokenizer.h
            src/utils.cpp
            src/utils.h)

target_include_directories(canasc PUBLIC include)

set_target_properties(canasc
                      PROPERTIES
                      CXX_STANDARD 14)
					  
add_subdirectory(sample)
enable_testing()
add_subdirectory(tests)
install(TARGETS canasc EXPORT canasc  DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

