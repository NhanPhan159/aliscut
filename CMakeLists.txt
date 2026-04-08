cmake_minimum_required(VERSION 4.2)
project(aliscut)
find_package(ftxui REQUIRED)
find_package(Slint QUIET)
if (NOT Slint_FOUND)
  message("Slint could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git
    # `release/1` will auto-upgrade to the latest Slint >= 1.0.0 and < 2.0.0
    # `release/1.0` will auto-upgrade to the latest Slint >= 1.0.0 and < 1.1.0
    GIT_TAG release/1
    SOURCE_SUBDIR api/cpp
  )
  FetchContent_MakeAvailable(Slint)
endif (NOT Slint_FOUND)

add_executable(
	 aliscut
)
target_sources(
	aliscut	
	PRIVATE
		main.cpp
		src/DrawAliasTable.cpp
	PUBLIC
		FILE_SET drawTable
		TYPE HEADERS 
		BASE_DIRS
			include
		FILES
			include/static/drawTable.hpp
)
target_link_libraries(aliscut
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
	PRIVATE Slint::Slint
)
slint_target_sources(aliscut ui/app.slint)

