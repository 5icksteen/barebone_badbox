#include "BSP_BadBox.h"
#include "SystemTick.h"
#include "mode.h"

int main()
{
  static_event.call([] { Button[BtnLabel::M].scan(); });
  static_event.call([] { Button[BtnLabel::N].scan(); });
  static_event.call([] { Button[BtnLabel::X].scan(); });
  static_event.call([] { Button[BtnLabel::Y].scan(); });
  static_event.call([] { Button[BtnLabel::Z].scan(); });
  static_event.call([] { led.scan(); });
  static_event.call([] { modes.dispatch(); });
  static_event.call([] { events.dispatch(); });

  for (;;) {}
}