#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

using namespace ftxui;

Component DummyWindowContent() {
  class Impl : public ComponentBase {
  private:
    bool checked[3] = {false, false, false};
    float slider = 50;

  public:
    Impl() {
      Add(Container::Vertical({
          Checkbox("Check me", &checked[0]),
          Checkbox("Check me", &checked[1]),
          Checkbox("Check me", &checked[2]),
          Slider("Slider", &slider, 0.f, 100.f),
      }));
    }
  };
  return Make<Impl>();
}
int main() {
  int terminalWidth = Dimension::Full().dimx;
  auto window_1 = Window({.inner = DummyWindowContent(),
                          .title = "First window",
                          .width = terminalWidth});

  auto layout = Container::Vertical({window_1});

  auto screen = App::Fullscreen();
  screen.Loop(layout);

  return EXIT_SUCCESS;
}
