#ifndef COLOR_SELECT_H
#define COLOR_SELECT_H

#include "Menu.h"

class Colorset;

class ColorSelect : public Menu
{
  public:
    ColorSelect();

    bool init(Mode *curMode);

    bool run(const TimeControl *timeControl, const Button *button, LedControl *ledControl);

    // handlers for clicks
    void onShortClick();
    void onLongClick();

  private:
    // internal routines for the color select
    void blinkSelection(const TimeControl *timeControl, LedControl *ledControl);
    void showSlotSelection(const TimeControl *timeControl, const Button *button, LedControl *ledControl);
    void showQuadSelection(const TimeControl *timeControl, const Button *button, LedControl *ledControl);
    void showHueSelection(const TimeControl *timeControl, const Button *button, LedControl *ledControl);
    void showSatSelection(const TimeControl *timeControl, const Button *button, LedControl *ledControl);
    void showValSelection(const TimeControl *timeControl, const Button *button, LedControl *ledControl);

    // Generate hue/sat/val values based on selection rules
    uint32_t makeHue(uint32_t quad, uint32_t selection);
    uint32_t makeSat(uint32_t selection);
    uint32_t makeVal(uint32_t selection);

    // helper to get the current 'page' of color select
    uint32_t curPage();

    // private enumeration for internal state of color selection
    enum ColorSelectState : uint32_t
    {
      // currently picking the color slot to change
      STATE_PICK_SLOT,
      // currently picking the quadrant of color
      STATE_PICK_QUAD,
      // picking a hue within the quadrant
      STATE_PICK_HUE,
      // picking a saturation for the color
      STATE_PICK_SAT,
      // picking a value for the color
      STATE_PICK_VAL,
    };

    // the current state of the color selection menu
    ColorSelectState m_state;

    // pointer to the colorset of the current mode
    Colorset *m_pColorset;

    // the target color slot to change
    uint32_t m_slot;

    // the chosen quadrant
    uint32_t m_quadrant;

    // the new color to set
    HSVColor m_newColor;
};

#endif
