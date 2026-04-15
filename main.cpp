#include "../build/app.h"
#include "include/static/drawTable.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <private/slint_models.h>
#include <private/slint_string.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc == 1) {

    // ------------ variable defination -----------
    vector<alias_struct> table;
    table = getTableAlias();
    vector<string> entries = getAliases(table);
    vector<string> meanings = getMeaning(table);
    vector<string> filterEntries = entries;
    vector<Alias> tableSlintForm;
    string command;
    for (int i = 0; i < table.size(); i++) {
      tableSlintForm.push_back(Alias{slint::SharedString(table[i].name),
                                     slint::SharedString(table[i].meaning)});
    }
    auto table_model =
        std::make_shared<slint::VectorModel<Alias>>(tableSlintForm);

    auto app = AppWindow::create();
    app->on_close_app([&]() {
      app->window().hide();
      slint::quit_event_loop();
    });
    app->on_send_a_alias_name([&](slint::SharedString aliasName) {
      app->window().hide();
      command = string(aliasName);
      slint::quit_event_loop();
      system("clear");
      cout << command << endl;
    });
    app->set_aliases_table(table_model);
    app->set_row_count(table.size());
    app->set_page_count(ceil(table.size() / 9.0));
    app->run();

    return 0;

  } else if (argc == 2) {
    if (strcmp(argv[1], "-s") == 0) {
      drawTable();
    }
  }
  return EXIT_SUCCESS;
}
