aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} xmlreader_srcs)

add_executable(xmlreader ${xmlreader_srcs})
target_link_libraries(xmlreader PRIVATE pugixml-static)