CXX:=g++
CXXSTD=c++17

aliscut: DrawAliasTable.cpp
	$(CXX) -std=$(CXXSTD) DrawAliasTable.cpp -o aliscut	
