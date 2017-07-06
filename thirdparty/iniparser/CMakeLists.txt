set(FILES
    dictionary.cpp
	dictionary.h
	iniparser.cpp
	iniparser.h
)

add_library(iniparser STATIC ${FILES})
target_link_libraries(iniparser)

