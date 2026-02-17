include config.mk
aliscut: DrawAliasTable.cpp
	$(CXX) -std=c++17 DrawAliasTable.cpp -o aliscut	
