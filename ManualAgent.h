#ifndef MANUALAGENT_H
#define MANUALAGENT_H

#include "Agent.h"

class ManualAgent : public Agent {
public:
  Position::position_t play(Position &P) override;
};

#endif //MANUALAGENT_H
