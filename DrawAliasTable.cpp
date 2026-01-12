#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

const string COLOR_CODE_DEFAULT = "\e[0;37m";
const string RESET_CODE = "\e[0m";
vector<vector<string>> table = {{"ALIAS", "MEANING"}};

void printByColor(string content = "", string color = COLOR_CODE_DEFAULT) {
  cout << color << content << RESET_CODE;
}

void setTable(int width_col_1, int width_col_2) {
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
        printByColor(table[i][j], "\e[0;33m");
      } else
        printByColor(table[i][j], "\e[1;34m");
      if (j == 0) {
        strLen = width_col_1 - table[i][j].size() - 1;
      }
      if (j == 1) {
        strLen = width_col_2 - table[i][j].size() - 2;
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
std::vector<std::string> split(std::string s, std::string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}
void printVector2D(vector<vector<string>> vec) {
  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      cout << vec[i][j] << endl;
    }
  }
}

const char *homedir;
int main() {
  struct stat sb;
  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }
  int maxLenCol1 = 1;
  int maxLenCol2 = 1;
  string support_shell[] = {"./bashrc", "/.zshrc"};
  string shell_config_path;
  char *shell_config_path_char;

  for (string shell : support_shell) {
    shell_config_path = (string)homedir + shell;
    shell_config_path_char = shell_config_path.data();
    if (stat(shell_config_path_char, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
      break;
    }
  }
  cout << "Shell path config: " << shell_config_path << endl;
  std::ifstream file(shell_config_path);
  std::string str;
  std::string file_content;
  while (std::getline(file, str)) {
    if (str.find("alias") != std::string::npos) {
      str = str.substr(5);
      vector<string> aliasItem = split(str, "=");
      maxLenCol1 = max<int>(aliasItem[0].length(), maxLenCol1);
      maxLenCol2 = max<int>(aliasItem[1].length(), maxLenCol2);
      table.push_back(split(str, "="));
    }
  }
  if (table.size() > 1) {
    setTable(maxLenCol1 + 1, maxLenCol2 + 3);
  } else {
    cout << R"(
__  __                   __                     __     __                                                   ___           
\ \/ /___  __  __   ____/ /___     ____  ____  / /_   / /_  ____ __   _____     ____ _____  __  __   ____ _/ (_)___ ______
 \  / __ \/ / / /  / __  / __ \   / __ \/ __ \/ __/  / __ \/ __ `/ | / / _ \   / __ `/ __ \/ / / /  / __ `/ / / __ `/ ___/
 / / /_/ / /_/ /  / /_/ / /_/ /  / / / / /_/ / /_   / / / / /_/ /| |/ /  __/  / /_/ / / / / /_/ /  / /_/ / / / /_/ (__  ) 
/_/\____/\__,_/   \__,_/\____/  /_/ /_/\____/\__/  /_/ /_/\__,_/ |___/\___/   \__,_/_/ /_/\__, /   \__,_/_/_/\__,_/____/  
 )";
  }

  return 0;
}
