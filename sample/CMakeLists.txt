
add_executable(sampleparserlog sample_parse_log.cpp)

target_link_libraries(sampleparserlog
                      PRIVATE
                      canasc)
