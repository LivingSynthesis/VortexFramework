#include "Button.h"

#include <Arduino.h>

#include "TimeControl.h"
#include "Timings.h"
#include "Log.h"

// Since there is only one button I am just going to expose a global pointer to 
// access it, instead of making the Button class static in case a second button 
// is added. This makes it easier to access the button from other places while 
// still allowing for a second instance to be added.  I wish there was a more 
// elegant way to make the button accessible but not global.  
// This will simply point at VortexGloveset::m_button. 
Button *g_pButton = nullptr;

Button::Button() :
  m_pinNum(0),
  m_buttonState(HIGH),
  m_pressTime(0),
  m_releaseTime(0),
  m_holdDuration(0),
  m_releaseDuration(0),
  m_newPress(false),
  m_newRelease(false),
  m_isPressed(false),
  m_shortClick(false),
  m_longClick(false)
{
}

Button::~Button()
{
}

bool Button::init(int pin)
{
  m_pinNum = pin;
  pinMode(m_pinNum, INPUT_PULLUP);
  return true;
}

void Button::check()
{
  // reset the new press/release members this tick
  m_newPress = false;
  m_newRelease = false;

  // read the new button state
  int newButtonState = digitalRead(m_pinNum);

  // did the button change (press/release occurred)
  if (newButtonState != m_buttonState) {
    // set the new state
    m_buttonState = newButtonState;
    // update the currently pressed member
    m_isPressed = (m_buttonState == LOW);

    // update the press/release times and newpress/newrelease members
    if (m_isPressed) {
      // the button was just pressed
      m_pressTime = Time::getCurtime();
      m_newPress = true;
    } else {
      // the button was just released
      m_releaseTime = Time::getCurtime();
      m_newRelease = true;
    }
  }

  // calculate new hold/release durations if currently held/released
  if (m_isPressed) {
    // update the hold duration as long as the button is pressed
    if (Time::getCurtime() >= m_pressTime) {
      m_holdDuration = (uint32_t)(Time::getCurtime() - m_pressTime);
    }
  } else {
    // update the release duration as long as the button is released
    if (Time::getCurtime() >= m_releaseTime) {
      m_releaseDuration = (uint32_t)(Time::getCurtime() - m_releaseTime);
    }
  }

  // whether a shortclick or long click just occurred
  m_shortClick = (m_newRelease && (m_holdDuration <= SHORT_CLICK_THRESHOLD));
  m_longClick = (m_newRelease && (m_holdDuration > SHORT_CLICK_THRESHOLD));

  if (m_shortClick) DEBUG("Short click");
  if (m_longClick) DEBUG("Long click");

#if 0
  // helpful for debugging
  DEBUG("Button Info:\n\tm_buttonState: %d\n\tm_pressTime: %d\n\tm_releaseTime: %d\n\t"
    "m_holdDuration: %d\n\tm_releaseDuration: %d\n\tm_newPress: %d\n\t"
    "m_newRelease: %d\n\t" "m_isPressed: %d\n\tm_shortClick: %d\n\t"
    "m_longClick: %d\n",
    m_buttonState,
    m_pressTime,
    m_releaseTime,
    m_holdDuration,
    m_releaseDuration,
    m_newPress,
    m_newRelease,
    m_isPressed,
    m_shortClick,
    m_longClick);
#endif
}
