cmake_minimum_required(VERSION 4.2)
project(aliscut)

include(GNUInstallDirs)
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(Slint QUIET)
if(NOT Slint_FOUND)
	message("Slint library not founded, starting buildslint ...")
	include(FetchContent)
	FetchContent_Declare(
	 	Slint
	 	GIT_REPOSITORY https://github.com/slint-ui/slint.git
	 	GIT_TAG release/1
	 	SOURCE_SUBDIR api/cpp
	)
	FetchContent_MakeAvailable(Slint)
endif()

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
  # PRIVATE ftxui::screen
  # PRIVATE ftxui::dom
  # PRIVATE ftxui::component
	PRIVATE Slint::Slint
)
slint_target_sources(aliscut ui/app.slint)

