set(FILES
	main.cpp
	Util.h
	Util.cpp
	Sound.h
	Sound.cpp
	Spotify.h
	Spotify.cpp
	VLC.h
	VLC.cpp
	MPlayerX.h
	MPlayerX.cpp
)

if(MSVC)
else()
list(APPEND FILES
	UnixSerial.h
	UnixSerial.cpp
)
endif()

add_executable(irservice ${FILES})
target_include_directories(irservice PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/iniparser")
target_link_libraries(irservice iniparser)

# install target
install(TARGETS irservice RUNTIME DESTINATION ~/bin)
# install files
# ref: https://zh.wikibooks.org/zh-tw/CMake_%E5%85%A5%E9%96%80/%E8%BC%B8%E5%87%BA%E4%BD%8D%E7%BD%AE%E8%88%87%E5%AE%89%E8%A3%9D
#file(GLOB CONF_FILES setting.ini setting_toshiba.ini setting_sony.ini)
#install(FILES ${CONF_FILES} DESTINATION ~/bin)
install(FILES setting.ini DESTINATION ~/bin)
file(GLOB SOUND_FILES sound/button.wav sound/spotify.wav sound/vlc.wav)
install(FILES ${SOUND_FILES} DESTINATION ~/bin)
# install directory
#install(DIRECTORY dirs DESTINATION <dir>)
