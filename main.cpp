#include "include/static/drawTable.hpp"
#include <cstring>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/deprecated.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>
#include <variant>
#include <vector>
using namespace std;
using namespace ftxui;

Element render(const WindowRenderState &state) {
  Element element = state.inner;
  if (!state.active) {
    element |= dim;
  }

  int terminalWidth = Dimension::Full().dimx;
  element = window(text("  " + state.title + "  ") | hcenter | bold |
                       size(WIDTH, EQUAL, terminalWidth),
                   element | vscroll_indicator | frame);
  return element;
}
Element renderMeaningWindow(const WindowRenderState &state) {
  Element element = state.inner;
  element |= color(Color::White);
  int terminalWidth = Dimension::Full().dimx;
  element = window(text("  " + state.title + "  ") | hcenter | bold |
                       size(WIDTH, EQUAL, terminalWidth),
                   element);
  return element;
}
Component TextRef(string &t) {
  return Renderer([&t] { return text(t); });
}
Component SelectedRef(int &t, vector<string> entries) {
  return Renderer([&t, entries] { return text(entries[t]); });
}
Component Text(string t) {
  return Renderer([t] { return text(t); });
}

int main(int argc, char *argv[]) {
  if (argc == 1) {

    // ------------ variable defination -----------
    int terminalWidth = Dimension::Full().dimx;
    int terminalHeight = Dimension::Full().dimy;
    int selected = 0;
    string searchStr = "";
    vector<vector<string>> table;
    table = getTableAlias();
    vector<string> entries = getAliases(table);
    vector<string> meanings = getMeaning(table);
    vector<string> filterEntries = entries;
    MenuOption option;
    auto menu = Menu(&filterEntries, &selected, option);

    // --------------- inner component in window ---------------
    Component innerSearchWindow = Container::Horizontal(
        {Text("🔎"),
         Input(&searchStr,
               {.transform = [](InputState state) { return state.element; },
                .on_change =
                    [&filterEntries, entries, &searchStr] {
                      vector<string> result;
                      for (int idx = 0; idx < entries.size(); idx++) {
                        if (entries[idx].find(searchStr) != variant_npos) {
                          result.push_back(entries[idx]);
                        }
                      }
                      filterEntries = result;
                    }})});
    Component innnerResultLeftCompenent = Container::Vertical({menu});
    Component innnerResultRightCompenent =
        Container::Vertical({SelectedRef(selected, meanings)});

    // ----------- search windown --------------

    Component searchWindow = Window({.inner = innerSearchWindow,
                                     .title = "Search Keyword",
                                     .left = 3,
                                     .width = terminalWidth,
                                     .height = 3,
                                     .render = render});

    // ----------- result windown --------------

    Component resultLeftWindow = Window({.inner = innnerResultLeftCompenent,
                                         .title = "Alias Result",
                                         .left = 3,
                                         .width = terminalWidth / 2,
                                         .height = terminalHeight / 2,
                                         .render = render});
    Component resultRightWindow = Window({.inner = innnerResultRightCompenent,
                                          .title = "Meaning",
                                          .left = 3,
                                          .width = terminalWidth / 2,
                                          .height = terminalHeight / 2,
                                          .render = renderMeaningWindow});

    // --------- Layout -----------

    Component layout = Container::Vertical(
        {searchWindow,
         Container::Horizontal({resultLeftWindow, resultRightWindow})});

    auto screen = App::Fullscreen();
    option.on_enter = screen.ExitLoopClosure();
    screen.Loop(layout);
  } else if (argc == 2) {
    if (strcmp(argv[1], "-s") == 0) {
      drawTable();
    }
  }

  return EXIT_SUCCESS;
}
