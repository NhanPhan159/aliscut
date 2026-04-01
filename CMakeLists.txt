cmake_minimum_required(VERSION 4.2)
project(aliscut)
find_package(ftxui REQUIRED)
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
)

