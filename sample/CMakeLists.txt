
add_executable(sampleparselog sample_parse_log.cpp)

target_link_libraries(sampleparselog
                      PRIVATE
                      canasc_parser)

set_target_properties(sampleparselog
                      PROPERTIES
                      CXX_STANDARD 11)
