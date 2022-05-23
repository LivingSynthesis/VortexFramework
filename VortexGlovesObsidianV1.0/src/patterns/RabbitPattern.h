#ifndef RABBIT_PATTERN_H
#define RABBIT_PATTERN_H

#include "HybridPattern.h"

// Rabbit is PATTERN_STROBIE on tops and PATTERN_STROBE on tips
class RabbitPattern : public HybridPattern
{
public:
  RabbitPattern();
  virtual ~RabbitPattern();

  // init the pattern to initial state
  virtual void init(Colorset *colorset, LedPos pos);

  // pure virtual must override the play function
  virtual void play();

  // must override the serialize routine to save the pattern
  virtual void serialize(SerialBuffer &buffer) const;
  virtual void unserialize(SerialBuffer &buffer);

private:
  // whether the sub patterns have been created already
  bool m_created;

};

#endif
