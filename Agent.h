#ifndef AGENT_H
#define AGENT_H

#include "Position.h"

/**
 * A parent class that wraps different agent types.
 */
class Agent {
public:
  virtual ~Agent() = default;

  virtual Position::position_t play(Position &P) { return 0; };

  virtual int num_visited() const { return 0; };

  virtual void reset() {}
};

#endif //AGENT_H
