#ifndef PERFECTAGENT_H
#define PERFECTAGENT_H

#include <utility>
#include "Agent.h"
#include "TranspositionTable.h"

class PerfectAgent : public Agent {
public:
  PerfectAgent() : nodes_visited(0) {};

  /**
   * Selects the best move at a position.
   *
   * @param P The position to play on.
   * @return a bitmap where a single "on" bit denotes the desired cell.
   */
  Position::position_t play(Position &P) override;

  /**
   * Evaluates the score of a position.
   * Scores are relative to the player whose turn is next.
   *
   * @param P The position of the board.
   * @return a score where positive is win, zero is draw, and negative is loss.
   */
  int evaluate(Position &P);

  /**
   * Returns the number of visited nodes.
   *
   * @return the number of visited nodes.
   */
  [[nodiscard]] int num_visited() const override {
    return nodes_visited;
  }

  void reset() override {
    nodes_visited = 0;
    transTable.clear();
  }

private:
  /**
   * Runs a negamax search over the game tree.
   *
   * When searching from a root node, alpha and beta should be the
   * minimum and maximum score values, respectively.
   *
   * @param P The position to search.
   * @param alpha The initial alpha value.
   * @param beta The initial beta value.
   * @return the value of the position.
   */
  int negamax(Position &P, int alpha, int beta);

  int nodes_visited;

  /**
   * The move search order is hard-coded, starting from the center square,
   * then to the corners, and then to the edges.
   */
  static constexpr int move_order[9]{4, 0, 2, 6, 8, 1, 3, 5, 7};

  TranspositionTable<Position::position_t, uint8_t, uint8_t> transTable;
};

#endif //PERFECTAGENT_H
