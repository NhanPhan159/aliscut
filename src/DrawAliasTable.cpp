#include "../include/static/drawTable.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <pwd.h>
#include <regex>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

void printByColor(string content = "", string color = COLOR_CODE_DEFAULT) {
  cout << color << content << RESET_CODE;
}

void setTable(int width_col_1, int width_col_2, vector<alias_struct> table) {
  string row = "─", col = "│", cornerL = "│", cornerR = "│", midd = "┼",
         middD = "┴", cornerLU = "└", middU = "┬";
  string cornerRU = "┘", cornerRR = "┐", cornerLL = "┌", middleSingle = "│";

  /* draw the top bar*/
  for (int f = 0; f < width_col_1 + width_col_2; f++) {
    if (f == 0) {
      printByColor(cornerLL);
    } else if (f == width_col_1 + width_col_2 - 1) {
      printByColor(cornerRR);
    } else if (f == width_col_1) {
      printByColor(middU);
    } else {
      printByColor(row);
    }
  }

  /* draw the middle content*/
  int strLen = 0;
  for (int i = 0; i < table.size(); i++) {
    cout << "\n";
    printByColor(col);
    for (int j = 0; j < 2; j++) {
      if (i == 0) {
        if (j == 0)
          printByColor(table[i].name, "\e[0;33m");
        else
          printByColor(table[i].meaning, "\e[0;33m");
      } else {
        if (j == 0)
          printByColor(table[i].name, "\e[1;34m");
        else
          printByColor(table[i].meaning, "\e[1;34m");
      }
      if (j == 0) {
        strLen = width_col_1 - table[i].name.size() - 1;
      }
      if (j == 1) {
        strLen = width_col_2 - table[i].meaning.size() - 2;
      }
      for (int x = 0; x < strLen; x++) {
        cout << " ";
      }
      printByColor(col);
    }
    cout << "\n";
    if (i < table.size() - 1) {
      for (int rd = 0; rd < width_col_1 + width_col_2; rd++) {
        if (rd == 0)
          printByColor(cornerL);
        else if (rd == width_col_2 + width_col_1 - 1) {
          printByColor(cornerR);
        } else if (rd == width_col_1)
          printByColor(midd);
        else {
          printByColor(row);
        }
      }
    }
  }
  /* draw the last bar*/
  for (int rd = 0; rd < width_col_1 + width_col_2; rd++) {
    if (rd == 0)
      printByColor(cornerLU);
    else if (rd == width_col_2 + width_col_1 - 1) {
      printByColor(cornerRU);
    } else if (rd == width_col_1)
      printByColor(middD);
    else {
      printByColor(row);
    }
  }
}
alias_struct split(string s, string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<alias_struct> res;
  vector<string> split_string;
  alias_struct alias_item = {"", ""};

  if ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    split_string.push_back(token);
  }
  split_string.push_back(s.substr(pos_start));
  if (split_string.size() != 2)
    return alias_item;
  else {
    return {split_string[0], split_string[1]};
    ;
  }
}
void printVectorAliasStruct(vector<alias_struct> vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i].name << "\t";
    cout << vec[i].meaning << endl;
  }
}
string preprocessString(string value) {
  regex pattern(R"(['"])");
  string result = regex_replace(value, pattern, "");
  return result;
}

void drawTable() {
  vector<alias_struct> table = {{"ALIAS", "MEANING"}};
  const char *homedir;
  struct stat sb;
  int maxLenAlias = 1;
  int maxLenMeaning = 1;
  string support_shell[] = {"/.bashrc", "/.zshrc"};
  string shell_config_path;
  char *shell_config_path_char;

  // get shell config path
  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }
  for (string shell : support_shell) {
    shell_config_path = (string)homedir + shell;
    shell_config_path_char = shell_config_path.data();
    if (stat(shell_config_path_char, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
      break;
    }
  }

  // get table alias
  ifstream file(shell_config_path);
  string str;
  string file_content;
  while (getline(file, str)) {
    if (regex_match(str, ALIAS_PATTERN)) {
      str = str.substr(5);
      alias_struct aliasItem = split(str, "=");
      aliasItem.name = preprocessString(aliasItem.name);
      aliasItem.meaning = preprocessString(aliasItem.meaning);
      maxLenAlias = max<int>(max<int>(aliasItem.name.length(), maxLenAlias),
                             MAX_ALIAS_COL);
      maxLenMeaning = max<int>(
          max<int>(aliasItem.meaning.length(), maxLenMeaning), MAX_MEANING_COL);
      table.push_back(aliasItem);
    }
  }
  if (table.size() > 1) {
    setTable(maxLenAlias + 2, maxLenMeaning + 4, table);
  } else {
    printByColor(WARNING_MESSAGE, RED_COLOR);
  }
  cout << endl;
}
vector<alias_struct> getTableAlias() {
  vector<alias_struct> table;
  const char *homedir;
  struct stat sb;
  int maxLenAlias = 1;
  int maxLenMeaning = 1;
  string support_shell[] = {"/.bashrc", "/.zshrc"};
  string shell_config_path;
  char *shell_config_path_char;

  // get shell config path
  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }
  for (string shell : support_shell) {
    shell_config_path = (string)homedir + shell;
    shell_config_path_char = shell_config_path.data();
    if (stat(shell_config_path_char, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
      break;
    }
  }

  // get table alias
  ifstream file(shell_config_path);
  string str;
  string file_content;
  while (getline(file, str)) {
    if (regex_match(str, ALIAS_PATTERN)) {
      str = str.substr(5);
      alias_struct aliasItem = split(str, "=");
      aliasItem.name = preprocessString(aliasItem.name);
      aliasItem.meaning = preprocessString(aliasItem.name);
      maxLenAlias = max<int>(max<int>(aliasItem.name.length(), maxLenAlias),
                             MAX_ALIAS_COL);
      maxLenMeaning = max<int>(
          max<int>(aliasItem.meaning.length(), maxLenMeaning), MAX_MEANING_COL);
      table.push_back(aliasItem);
    }
  }
  return table;
}

vector<string> getAliases(vector<alias_struct> table) {
  vector<string> aliases = {};
  for (int idx = 0; idx < table.size(); idx++) {
    aliases.push_back(table[idx].name);
  }
  return aliases;
}
vector<string> getMeaning(vector<alias_struct> table) {
  vector<string> meanings = {};
  for (int idx = 0; idx < table.size(); idx++) {
    meanings.push_back(table[idx].meaning);
  }
  return meanings;
}
