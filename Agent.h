#ifndef AGENT_H
#define AGENT_H

#include "Position.h"

class Agent {
public:
  Agent() : nodes_visited(0) {};

  /**
   * Evaluates the score of a position.
   * Scores are relative to the player whose turn is next.
   *
   * @param position The position of the board.
   * @return a score where positive is win, zero is draw, and negative is loss.
   */
  int evaluate(Position &position);

  int num_visited() {
    return nodes_visited;
  }

private:
  int negamax(Position &P, int alpha, int beta);

  int nodes_visited;
//  static constexpr int move_order[9]{4, 0, 2, 6, 8, 1, 3, 5, 7};
  static constexpr int move_order[9]{0, 1, 2, 3, 4, 5, 6, 7, 8};
};

#endif //AGENT_H
