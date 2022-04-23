#ifndef MENU_H
#define MENU_H

#include <inttypes.h>
#include <string>

#include "../ColorTypes.h"

class Mode;
class Button;
class LedControl;
class TimeControl;

class Menu
{
  public:
    Menu();
    virtual ~Menu();

    // optional init function can be overridden
    virtual bool init(Mode *curMode);

    // when the menu runs it will have access to time, the button and led control
    virtual bool run(const TimeControl *timeControl, const Button *button, LedControl *ledControl) = 0;

    // optional handlers for clicks
    virtual void onShortClick();
    virtual void onLongClick();

  protected:
    // close the current menu
    void leaveMenu() { m_shouldClose = true; }

    // the current mode that was selected
    Mode *m_pCurMode;

    // all menus have a 'current selection' counter which roughly correlates
    // to 1 index per finger but may have special cases like 'all fingers'.
    // It's up to the derived Menu class to decide how to increment/manage this
    uint32_t m_curSelection;

  private:
    // whether to close the menu
    bool m_shouldClose;
};

#endif
