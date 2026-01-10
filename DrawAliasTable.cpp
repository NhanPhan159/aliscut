#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string COLOR_CODE = "\e[0;32m";
const string RESET_CODE = "\e[0m";
vector<vector<string>> table = {{"ALIAS", "MEANING"}};

void printByColor(string content = "", string color = COLOR_CODE) {
  cout << COLOR_CODE << content << RESET_CODE;
}
void draw_rect(int width, int height) {
  printByColor("+");
  for (int i = 0; i < width - 2; i++) {
    printByColor("-");
  }
  printByColor("+\n");

  for (int i = 0; i < height - 2; i++) {
    printByColor("|");
    for (int j = 0; j < width - 2; j++) {
      cout << " ";
    }
    printByColor("|\n");
  }

  cout << "\e[0;32m+";
  for (int i = 0; i < width - 2; i++) {
    cout << "\e[0;32m-";
  }
  cout << "\e[0;32m+\n";
}
void setTable() {
  string row = "─", col = "│", cornerL = "│", cornerR = "│", midd = "┼",
         middD = "┴", cornerLU = "└", middU = "┬";
  string cornerRU = "┘", cornerRR = "┐", cornerLL = "┌",
         middleSingle = "│"; // ascii codes

  /* draw the top bar*/
  for (int f = 0; f < 17; f++) {
    if (f == 0) {
      printByColor(cornerLL);
    } else if (f == 16) {
      printByColor(cornerRR);
    } else if (f == 8) {
      printByColor(middU);
    } else {
      printByColor(row);
    }
  }

  /* draw the middle content*/
  for (int i = 0; i < table.size(); i++) {
    cout << "\n";
    printByColor(col);
    for (int j = 0; j < 2; j++) {
      cout << table[i][j] << "\t";
      printByColor(col);
    }
    cout << "\n";
    if (i < 9) {
      for (int rd = 0; rd < 17; rd++) {
        switch (rd) {
        case 0:
          printByColor(cornerL);
          continue;
        case 16:
          printByColor(cornerR);
          continue;
        case 8:
          printByColor(midd);
          continue;
        default:
          printByColor(row);
        }
      }
    }
  }
  /* draw the last bar*/
  for (int rd = 0; rd < 17; rd++) {
    switch (rd) {
    case 0:
      printByColor(cornerLU);
      continue;
    case 16:
      printByColor(cornerRU);
      continue;
    case 8:
      printByColor(middD);
      continue;
    default:
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
int main() {
  int maxLenCol1 = 17;
  int maxLenCol2 = 17;
  std::ifstream file("/Users/nhanphan159/.zshrc");
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
  table.push_back({"123", "123"});
  printVector2D(table);
  setTable();
  return 0;
}
