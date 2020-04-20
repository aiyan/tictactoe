#ifndef RANDOMAGENT_H
#define RANDOMAGENT_H

#include "Agent.h"

class RandomAgent : public Agent {
public:
  Position::position_t play(Position &P) override;

private:
  template<typename Iter>
  Iter select_rand_move(Iter start, Iter end);
};

#endif //RANDOMAGENT_H
