#include "MultiLedPattern.h"

MultiLedPattern::MultiLedPattern() :
  Pattern()
{
  // this is a multi led pattern
  m_patternFlags |= PATTERN_FLAG_MULTI;
}

MultiLedPattern::~MultiLedPattern()
{
}

// init the pattern to initial state
void MultiLedPattern::init(Colorset *colorset, LedPos pos)
{
  Pattern::init(colorset, pos);
}
