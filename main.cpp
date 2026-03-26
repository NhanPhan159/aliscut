#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/deprecated.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
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
                   element);
  return element;
}
Component Text(const string t) {
  return Renderer([t] { return text(t); });
}
int main() {
  string value = "";
  Component innerSearchWindow = Container::Horizontal(
      {Text("🔎"), Input(value, {.transform = [](InputState state) {
                           return state.element;
                         }})});
  int terminalWidth = Dimension::Full().dimx;
  Component searchWindow = Window({.inner = innerSearchWindow,
                                   .title = "Search Keyword",
                                   .left = 3,
                                   .width = terminalWidth,
                                   .height = 3,
                                   .render = render});

  Component layout = Container::Vertical({searchWindow});

  auto screen = App::Fullscreen();
  screen.Loop(layout);

  return EXIT_SUCCESS;
}
