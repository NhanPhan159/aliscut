#pragma once
#include <regex>
#include <string>
using namespace std;

const string COLOR_CODE_DEFAULT = "\e[0;37m";
const string RESET_CODE = "\e[0m";
const string RED_COLOR = "\e[1;31m";
const string WARNING_MESSAGE = "You don't have any aliases";
const regex ALIAS_PATTERN("^alias\\s+[a-zA-Z0-9_\\-]+=[\"'].+[\"']$");
const int MAX_ALIAS_COL = 8;
const int MAX_MEANING_COL = 8;

void printByColor(string content, string color);
void setTable(int width_col_1, int width_col_2, vector<vector<string>> table);
vector<string> split(string s, string delimiter);
void printVector2D(vector<vector<string>> vec);
string preprocessString(string value);
void drawTable();
vector<vector<string>> getTableAlias();
vector<string> getAliases(vector<vector<string>> table);
vector<string> getMeaning(vector<vector<string>> table);
