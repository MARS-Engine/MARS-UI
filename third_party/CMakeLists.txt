add_library(pugixml STATIC)
set_property(TARGET pugixml PROPERTY POSITION_INDEPENDENT_CODE ON)
target_sources(pugixml PRIVATE pugixml/pugixml.hpp pugixml/pugixml.cpp pugixml/pugiconfig.hpp)
target_include_directories(pugixml PUBLIC pugixml)