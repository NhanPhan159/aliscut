#include "../build/app-window.h"
#include "include/static/drawTable.hpp"
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc == 1) {

    // ------------ variable defination -----------
    int selected = 0;
    string searchStr = "";
    vector<alias_struct> table;
    table = getTableAlias();
    vector<string> entries = getAliases(table);
    vector<string> meanings = getMeaning(table);
    vector<string> filterEntries = entries;

    auto ui = AppWindow::create();
    ui->on_close_app([&]() {
      ui->window().hide();
      slint::quit_event_loop();
    });
    ui->run();
    return 0;

  } else if (argc == 2) {
    if (strcmp(argv[1], "-s") == 0) {
      drawTable();
    }
  }

  return EXIT_SUCCESS;
}
