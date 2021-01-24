#include <cstdlib>
#include <functional>
#include <vector>

#include "Global.h"
#include "Ticker.h"
#include "mode.h"

auto all_events = [] {
  Button[Key1].scan();
  Button[Key2].scan();
  Button[Key3].scan();
  Button[Key4].scan();
  Button[Key5].scan();
  modes.dispatch();
  events.dispatch();
};

int main()
{
  for (;;)
    {
      led.scan();
      ticker.dispatch(all_events);
    }
  // static_assert(false, "Error Message");
  return 0;
}