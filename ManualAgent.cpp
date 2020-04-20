#include "ManualAgent.h"

Position::position_t ManualAgent::play(Position &P) {
  char move_char;
  std::cin >> move_char;
  int move = move_char - '1';

  return Position::cell_mask(move);
}
