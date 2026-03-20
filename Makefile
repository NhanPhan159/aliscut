CXX:=g++
CXXSTD=c++17

# aliscut: DrawAliasTable.cpp
# 	$(CXX) -std=$(CXXSTD) DrawAliasTable.cpp -o aliscut	
main: main.cpp	utils.cpp
	 g++ main.cpp utils.cpp -o main -lncurses
