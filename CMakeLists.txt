add_subdirectory(MVRE)

add_library(MVRE-GUI SHARED)

add_subdirectory(src)
add_subdirectory(third_party)

target_link_libraries(MVRE-GUI MVRE pugixml)

add_custom_command(TARGET MVRE-GUI PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ ${CMAKE_BINARY_DIR}/bin/Engine/Assets)