cmake_minimum_required(VERSION 3.7...3.18)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

add_executable(sampleparselog sample_parse_log.cpp)

target_link_libraries(sampleparselog
                      PRIVATE
                      canasc_parser)

set_target_properties(sampleparselog
                      PROPERTIES
                      CXX_STANDARD 11)
