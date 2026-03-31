cmake_minimum_required(VERSION 4.2)
project(aliscut)
find_package(ftxui REQUIRED)
add_executable(
	main 
)
target_sources(
	main
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
target_link_libraries(main
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

